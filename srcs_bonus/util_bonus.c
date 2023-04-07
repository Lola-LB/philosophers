/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:28:45 by lle-bret          #+#    #+#             */
/*   Updated: 2023/02/17 18:32:35 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_philo *philo)
{
	t_philo	*philosophers;

	philosophers = philo - philo->id;
	sem_close(philo->data->forks);
	free(philosophers);
	exit(0);
}

long	time_ms(struct timeval tv, t_philo *philo)
{
	long	time;

	time = (long) tv.tv_sec * 1000 + (long) tv.tv_usec / 1000;
	if (philo)
		time -= (long) philo->start.tv_sec * 1000
			+ (long) philo->start.tv_usec / 1000;
	return (time);
}

int	is_end(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_ms(tv, philo) - time_ms(philo->last_time_he_ate, philo)
		> philo->data->time_to_die)
	{
		printf("%s%09ld %d %s\n%s", RED, time_ms(tv, philo),
			philo->id, DEATH_LOG, NC);
		ft_exit(philo);
	}
	return (0);
}

void	print_log(t_philo *philo, char *log, char *color)
{
	struct timeval	tv;

	if (!is_end(philo))
	{
		gettimeofday(&tv, NULL);
		printf("%s%09ld %d %s\n%s", color, time_ms(tv, philo),
			philo->id, log, NC);
	}
}

void	ft_usleep(long time_to_sleep)
{
	struct timeval	tv;
	long			begin;
	long			time;

	gettimeofday(&tv, NULL);
	begin = time_ms(tv, NULL);
	time = begin;
	while (time - begin < time_to_sleep)
	{
		gettimeofday(&tv, NULL);
		time = time_ms(tv, NULL);
		usleep(10);
	}
}
