/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabel <lfabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:55:14 by lfabel            #+#    #+#             */
/*   Updated: 2025/01/02 14:36:13 by lfabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef unsigned long long	t_time;

typedef struct s_data
{
	int		death;
}			t_data;

typedef struct s_philo
{
	int				nb;
	t_time			time_to_eat;
	t_time			last_eaten;
	t_time			time_to_die;
	t_time			times_to_eat;
	t_time			time_to_sleep;
	int				amount;
	t_time			times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*status;
	int				death;
	t_data			*data;
	t_time			start;
}				t_philo;

int		check_death(t_philo *philos);
void	init_struct(t_philo *philosopher, char **argv, int argc);
void	think(t_philo *philos);
void	eat(t_philo *philos);
void	ft_sleep(t_philo *philos);
void	*routine(void *arg);
void	threads_create(t_philo *philosopher);
void	mutex_init(t_philo *philos, pthread_mutex_t *forks, \
			pthread_mutex_t *death, t_data *data);
size_t	ft_atoi(const char *str);
void	ft_print(t_philo *philos, char *str, int alive);
int		ft_args_check(int ac, char **av);
int		ft_usleep(size_t milliseconds, t_philo *philos);
t_time	get_current_time(void);

#endif