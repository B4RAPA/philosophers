/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabel <lfabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:58:17 by lfabel            #+#    #+#             */
/*   Updated: 2025/01/02 13:43:25 by lfabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philosopher;
	pthread_mutex_t	*death;
	pthread_mutex_t	*forks;

	if (ft_args_check(argc, argv) == 0)
		return (0);
	data = malloc (sizeof(t_data));
	philosopher = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
	death = malloc (sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	forks = malloc (sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!philosopher || !death || !forks)
		return (0);
	init_struct(philosopher, argv, argc);
	mutex_init(philosopher, forks, death, data);
	threads_create(philosopher);
	printf("%llu times eaten\n", philosopher->times_eaten);
	pthread_mutex_destroy(death);
	pthread_mutex_destroy(forks);
	free (death);
	free (forks);
	free (data);
	free (philosopher);
	return (0);
}

int	check_death(t_philo *philos)
{
	if (philos->times_to_eat == philos->times_eaten)
		return (1);
	pthread_mutex_lock(philos->status);
	if (philos->data->death == 1)
	{
		pthread_mutex_unlock(philos->status);
		return (1);
	}
	pthread_mutex_unlock(philos->status);
	if (get_current_time() - philos->last_eaten > philos->time_to_die)
	{
		ft_print (philos, "died", 0);
		return (1);
	}
	return (0);
}

size_t	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

void	ft_print(t_philo *philos, char *str, int alive)
{
	t_time	time;

	time = get_current_time() - philos->start;
	pthread_mutex_lock(philos->status);
	if (philos->data->death == 0)
	{
		printf("%llu ms %d %s\n", time, philos->nb, str);
		if (alive == 0)
			philos->data->death = 1;
	}
	pthread_mutex_unlock(philos->status);
}

//guess i will implement the detached mutex to check for death