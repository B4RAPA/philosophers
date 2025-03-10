/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabel <lfabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:35:10 by lfabel            #+#    #+#             */
/*   Updated: 2025/01/17 10:51:05 by lfabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static int	eat2(t_philo *philos);

void	*routine(void *arg)
{
	t_philo	*philos;
	t_time	i;

	philos = (t_philo *)arg;
	pthread_mutex_lock(philos->status);
	philos->data->death = 0;
	pthread_mutex_unlock(philos->status);
	i = 0;
	if (philos->amount == 1)
	{
		ft_usleep(philos->time_to_die, philos);
		printf("%lld ms 1 has died\n", philos->time_to_die);
		return (0);
	}
	while (1)
	{
		think(philos);
		eat(philos);
		ft_sleep(philos);
		if (philos->times_to_eat && ++i >= philos->times_to_eat)
			break ;
	}
	return (0);
}

void	ft_sleep(t_philo *philos)
{
	if (check_death(philos) == 1)
		return ;
	ft_print(philos, "is sleeping", 1);
	if (ft_usleep(philos->time_to_sleep, philos) == 1)
		return ;
	if (check_death(philos) == 1)
		return ;
}

void	eat(t_philo *philos)
{
	if (check_death(philos) == 1)
		return ;
	if (eat2(philos) == 1)
	{
		pthread_mutex_unlock(philos->fork_left);
		pthread_mutex_unlock(philos->fork_right);
		return ;
	}
	ft_print(philos, "is eating", 1);
	pthread_mutex_lock(philos->status);
	philos->last_eaten = get_current_time();
	pthread_mutex_unlock(philos->status);
	if (ft_usleep(philos->time_to_eat, philos) == 1)
	{
		pthread_mutex_unlock(philos->fork_left);
		pthread_mutex_unlock(philos->fork_right);
		return ;
	}
	pthread_mutex_lock(philos->status);
	philos->times_eaten ++;
	pthread_mutex_unlock(philos->status);
	pthread_mutex_unlock(philos->fork_left);
	pthread_mutex_unlock(philos->fork_right);
	if (check_death(philos) == 1)
		return ;
}

static int	eat2(t_philo *philos)
{
	if (philos->nb % 2 == 0)
	{
		pthread_mutex_lock(philos->fork_left);
		ft_print(philos, "has taken a fork", 1);
		pthread_mutex_lock(philos->fork_right);
		ft_print(philos, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(philos->fork_right);
		ft_print(philos, "has taken a fork", 1);
		pthread_mutex_lock(philos->fork_left);
		ft_print(philos, "has taken a fork", 1);
	}
	if (check_death(philos) == 1)
		return (1);
	return (0);
}

void	think(t_philo *philos)
{
	if (check_death(philos) == 1)
		return ;
	ft_print(philos, "is thinking", 1);
	usleep(100);
	if (check_death(philos) == 1)
		return ;
}
