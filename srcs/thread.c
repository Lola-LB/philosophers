/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:10 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/09 16:40:11 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[fork_id(philo, 0)]);
	print_log(philo, FORK_LOG, YELLOW);
	print_log(philo, EAT_LOG, GREEN);
	pthread_mutex_lock(&philo->eat_mutex);
	gettimeofday(&philo->last_time_he_ate, NULL);
	philo->number_of_times_he_ate = philo->number_of_times_he_ate + 1;
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 0)]);
	pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 1)]);
	if (!is_end(philo, 0))
	{
		print_log(philo, SLEEP_LOG, BLUE);
		ft_usleep(philo->time_to_sleep);
	}
}

void	*thread_routine(t_philo *philo)
{
	// print_log(philo, CREAT_LOG, WHITE);
	if (philo->id % 2)
		ft_usleep(philo->time_to_die * 0.10);
	while (!is_end(philo, 0) && (number_of_times_he_ate(philo)
			< philo->max_eat || philo->max_eat == -1))
	{
		if (!is_end(philo, 0))
		{
			if (number_of_times_he_ate(philo) == 1 && philo->data->nb % 2)
				ft_usleep(philo->time_to_die * 0.25);
			pthread_mutex_lock(&philo->data->forks[fork_id(philo, 1)]);
			print_log(philo, FORK_LOG, YELLOW);
			if ((philo->id != 0) || (philo->number_of_philo > 1))
				eat_routine(philo);
			else
			{
				ft_usleep(philo->time_to_die * 2);
				pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 1)]);
			}
		}
		print_log(philo, THINK_LOG, WHITE);
	}
	return (NULL);
}

void	death_check(t_philo *philo, int *finished_eating)
{
	struct timeval	tv;
	int				i;

	i = -1;
	while (!is_end(philo, 0)
		&& ++i < philo->number_of_philo)
	{
		if (number_of_times_he_ate(&philo[i])
			< philo->max_eat
			|| philo->max_eat == -1)
		{
			gettimeofday(&tv, NULL);
			if (time_ms(tv, philo)
				- time_ms(last_eat_time(&philo[i]), philo)
				> philo->time_to_die)
			{
				print_log(&philo[i], DEATH_LOG, RED);
				is_end(philo, 1);
			}
		}
		else if (philo->max_eat != -1)
			++(*finished_eating);
	}
}

void	*death_thread(t_philo *philo)
{
	int				finished_eating;

	finished_eating = 0;
	while (!is_end(philo, 0) && finished_eating < philo->data->nb)
	{
		finished_eating = 0;
		death_check(philo, &finished_eating);
	}
	return (NULL);
}

void	create_processes(t_philo *philosophers)
{
	int			i;
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t)
			* (philosophers->number_of_philo + 1));
	if (!tid)
	{
		free_philo(philosophers);
		return ;
	}
	i = 0;
	while (i < philosophers->number_of_philo)
	{
		pthread_create(&tid[i], NULL,
			(void *)(*thread_routine), &philosophers[i]);
		++i;
	}
	pthread_create(&tid[i], NULL,
		(void *)(*death_thread), (void *) philosophers);
	i = -1;
	while (++i < philosophers->number_of_philo + 1)
		pthread_join(tid[i], NULL);
	free(tid);
}
