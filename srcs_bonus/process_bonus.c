/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:10 by lle-bret          #+#    #+#             */
/*   Updated: 2023/02/10 15:47:38 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	conditional_usleep(t_philo *philo, long time_to_wait)
{
	struct timeval	tv;
	long			time_since_eating;

	gettimeofday(&tv, NULL);
	time_since_eating = time_ms(tv, NULL)
		- time_ms(philo->last_time_he_ate, NULL);
	if (time_to_wait + time_since_eating < philo->data->time_to_die)
		ft_usleep(time_to_wait);
	else
	{
		ft_usleep(philo->data->time_to_die - time_since_eating);
		is_end(philo);
	}
}

void	eat_routine(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_log(philo, FORK_LOG, YELLOW);
	print_log(philo, EAT_LOG, GREEN);
	gettimeofday(&philo->last_time_he_ate, NULL);
	philo->number_of_times_he_ate = philo->number_of_times_he_ate + 1;
	conditional_usleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (!is_end(philo))
	{
		print_log(philo, SLEEP_LOG, BLUE);
		conditional_usleep(philo, philo->data->time_to_sleep);
	}
}

void	process_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_die / 4);
	while (philo->number_of_times_he_ate
		< philo->data->nb_of_times_philo_must_eat
		|| philo->data->nb_of_times_philo_must_eat == -1)
	{
		if (philo->number_of_times_he_ate > 0 && philo->data->nb % 2)
			conditional_usleep(philo, philo->data->time_to_die / 10);
		sem_wait(philo->data->forks);
		print_log(philo, FORK_LOG, YELLOW);
		if ((philo->id != 0) || (philo->data->nb > 1))
			eat_routine(philo);
		else
			ft_usleep(philo->data->time_to_die * 2);
		print_log(philo, THINK_LOG, WHITE);
	}
	ft_exit(philo);
}

void	fork_processes(t_philo *philosophers, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < philosophers->data->nb)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			free(pid);
			ft_error(FORK_ERROR);
		}
		else if (pid[i] == 0)
		{
			free(pid);
			process_routine(&philosophers[i]);
		}
		++i;
	}
}

void	create_processes(t_philo *philosophers)
{
	int		i;
	int		status;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t)
			* (philosophers->data->nb));
	if (!pid)
	{
		free_philo(philosophers);
		return ;
	}
	fork_processes(philosophers, pid);
	i = 0;
	waitpid(-1, &status, 0);
	while (i < philosophers->data->nb)
	{
		kill(pid[i], SIGKILL);
		++i;
	}
	free(pid);
}
