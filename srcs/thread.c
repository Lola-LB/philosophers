/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:10 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 12:41:38 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[fork_id(philo, 0)]);
	print_log(philo, FORK_LOG, YELLOW);
	print_log(philo, EAT_LOG, GREEN);
	pthread_mutex_lock(&philo->he_ate_mutex);
	gettimeofday(&philo->last_time_he_ate, NULL);
	++(philo->number_of_times_he_ate);
	pthread_mutex_unlock(&philo->he_ate_mutex);
	ft_usleep(philo->param.time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 0)]);
	pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 1)]);
	if (!is_end(philo))
	{
		print_log(philo, SLEEP_LOG, BLUE);
		ft_usleep(philo->param.time_to_sleep);
	}
}

void	*thread_routine(t_philo *philo)
{
	if (philo->id % 2)
		ft_usleep(philo->param.time_to_die * 0.25);
	while (!is_end(philo) && (philo->param.max_eat == -1
		|| number_of_times_he_ate(philo) < philo->param.max_eat))
	{
		// if (philo->param.number_of_philo % 2 && number_of_times_he_ate(philo))
		// 	ft_usleep(philo->param.time_to_die * 0.25);
		pthread_mutex_lock(&philo->data->forks[fork_id(philo, 1)]);
		print_log(philo, FORK_LOG, YELLOW);
		if ((philo->id != 0) || (philo->param.number_of_philo > 1))
			eat_routine(philo);
		else
		{
			ft_usleep(philo->param.time_to_die * 1.1);
			pthread_mutex_unlock(&philo->data->forks[fork_id(philo, 1)]);
		}
		print_log(philo, THINK_LOG, WHITE);
	}
	return (NULL);
}

int	death_check(t_death *death, t_philo *philo)
{
	struct timeval	tv;
	int				finished_eating;
	int				i;

	i = -1;
	finished_eating = 0;
	while (!is_end(philo + ++i) && i < death->param.number_of_philo)
	{
		if (death->param.max_eat == -1
			|| number_of_times_he_ate(&philo[i]) < death->param.max_eat)
		{
			gettimeofday(&tv, NULL);
			if (time_ms(tv, &death->param.start)
				- time_ms(last_eat_time(&philo[i]), &death->param.start)
				> death->param.time_to_die)
			{
				print_log(&philo[i], DEATH_LOG, RED);
				global_end(death, philo);
			}
		}
		else if (death->param.max_eat != -1)
			++(finished_eating);
	}
	return (finished_eating);
}

void	*death_thread(t_death *death)
{
	int		finished_eating;

	finished_eating = 0;
	while (!check_global_end(death)
		&& finished_eating < death->param.number_of_philo)
		finished_eating = death_check(death, death->philo);
	return (NULL);
}

void	create_processes(t_death *death, t_philo *philo)
{
	int			i;
	int			nb;
	pthread_t	*tid;

	nb = death->param.number_of_philo;
	tid = malloc(sizeof(pthread_t) * (nb + 1));
	if (!tid)
	{
		free_philo(death);
		return ;
	}
	i = -1;
	while (++i < nb)
	{
		pthread_create(tid + i, NULL,
			(void *)(*thread_routine), philo + i);
	}
	pthread_create(tid + i, NULL,
		(void *)(*death_thread), (void *) death);
	i = -1;
	while (++i < nb + 1)
		pthread_join(tid[i], NULL);
	free(tid);
}
