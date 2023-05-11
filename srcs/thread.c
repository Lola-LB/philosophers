/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:10 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 14:18:31 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *log, char *color)
{
	struct timeval	tv;

	(void) color;
	if (!is_end(philo))
	{
		pthread_mutex_lock(philo->shared_mutex->printf_mutex);
		gettimeofday(&tv, NULL);
		printf("%09ld %d %s\n", time_ms(tv, &philo->param.start),
			philo->id, log);
		pthread_mutex_unlock(philo->shared_mutex->printf_mutex);
	}
}

void	eat_routine(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->shared_mutex->forks[fork_id(philo, 1)]);
	print_log(philo, FORK_LOG, YELLOW);
	pthread_mutex_lock(&philo->shared_mutex->forks[fork_id(philo, 0)]);
	print_log(philo, FORK_LOG, YELLOW);
	print_log(philo, EAT_LOG, GREEN);
	pthread_mutex_lock(philo->he_ate_mutex);
	gettimeofday(&tv, NULL);
	philo->last_time_he_ate = time_ms(tv, NULL);
	++(philo->number_of_times_he_ate);
	pthread_mutex_unlock(philo->he_ate_mutex);
	ft_usleep(philo->param.time_to_eat);
	pthread_mutex_unlock(&philo->shared_mutex->forks[fork_id(philo, 0)]);
	pthread_mutex_unlock(&philo->shared_mutex->forks[fork_id(philo, 1)]);
}

void	*thread_routine(t_philo *philo)
{
	if (philo->param.number_of_philo == 1)
	{
		pthread_mutex_lock(&philo->shared_mutex->forks[fork_id(philo, 1)]);
		ft_usleep(philo->param.time_to_die * 1.1);
		pthread_mutex_unlock(&philo->shared_mutex->forks[fork_id(philo, 1)]);
	}
	if (philo->id % 2)
		ft_usleep(philo->param.time_to_die * 0.10);
	while (!is_end(philo) && (philo->param.max_eat == -1
			|| number_of_times_he_ate(philo) < philo->param.max_eat))
	{
		if (philo->param.number_of_philo % 2 && number_of_times_he_ate(philo))
			ft_usleep(philo->param.time_to_die * 0.10);
		eat_routine(philo);
		print_log(philo, SLEEP_LOG, BLUE);
		ft_usleep(philo->param.time_to_sleep);
		print_log(philo, THINK_LOG, WHITE);
	}
	return (NULL);
}

int	death_check(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	int				finished_eating;
	int				i;

	i = -1;
	finished_eating = 0;
	while (++i < data->param.number_of_philo && !is_end(philo + i))
	{
		if (data->param.max_eat == -1
			|| number_of_times_he_ate(&philo[i]) < data->param.max_eat)
		{
			gettimeofday(&tv, NULL);
			if (time_ms(tv, NULL) - last_eat_time(&philo[i])
				> data->param.time_to_die)
			{
				print_log(&philo[i], DEATH_LOG, RED);
				global_end(data, philo);
			}
		}
		else if (data->param.max_eat != -1)
			++(finished_eating);
	}
	return (finished_eating);
}

void	*death_thread(t_data *data)
{
	int		finished_eating;

	finished_eating = 0;
	while (!check_global_end(data)
		&& finished_eating < data->param.number_of_philo)
		finished_eating = death_check(data, data->philo);
	return (NULL);
}
