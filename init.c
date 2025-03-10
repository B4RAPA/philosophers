/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabel <lfabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:59:35 by lfabel            #+#    #+#             */
/*   Updated: 2025/01/02 14:13:07 by lfabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	init_struct(t_philo *philosopher, char **argv, int argc)
{
	size_t	i;
	t_time	time;

	time = get_current_time();
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philosopher[i].amount = ft_atoi(argv[1]);
		philosopher[i].time_to_die = ft_atoi(argv[2]);
		philosopher[i].nb = i + 1;
		philosopher[i].time_to_eat = ft_atoi(argv[3]);
		philosopher[i].time_to_sleep = ft_atoi(argv[4]);
		philosopher[i].start = time;
		philosopher[i].last_eaten = time;
		philosopher[i].times_eaten = 0;
		if (argc == 6)
			philosopher[i].times_to_eat = ft_atoi(argv[5]);
		else
			philosopher[i].times_to_eat = 1000;
		i++;
	}
}

void	mutex_init(t_philo *philos, pthread_mutex_t *forks, \
		pthread_mutex_t *death, t_data *data)
{
	int	i;

	i = 0;
	while (i < philos->amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&death[i], NULL);
		philos[i].fork_left = &forks[i];
		philos[i].fork_right = &forks[(i + 1) % philos->amount];
		philos[i].status = death;
		philos[i].data = data;
		i++;
	}
}

void	threads_create(t_philo *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->amount)
	{
		pthread_create(&philosopher[i].thread, NULL, routine, &philosopher[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < philosopher->amount)
	{
		pthread_join(philosopher[i].thread, NULL);
		i++;
	}
}

int	ft_args_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (av[++i])
		{
			j = 0;
			while (av[i][j])
			{
				if (!(av[i][j] >= '0' && av[i][j] <= '9'))
					return (0);
				if (av[1][0] == '0')
					return (0);
				j++;
			}
		}
	}
	else
	{
		printf("Error. Wrong amount of Arguments\n");
		return (0);
	}
	return (1);
}
