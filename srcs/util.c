/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:28:45 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 12:29:59 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_ms(struct timeval tv, struct timeval *start)
{
	long	time;

	time = (long) tv.tv_sec * 1000 + (long) tv.tv_usec / 1000;
	if (start)
		time -= (long) start->tv_sec * 1000 + (long) start->tv_usec / 1000;
	return (time);
}

int	number_of_times_he_ate(t_philo *philo)
{
	int	eat;

	pthread_mutex_lock(&philo->he_ate_mutex);
	eat = philo->number_of_times_he_ate;
	pthread_mutex_unlock(&philo->he_ate_mutex);
	return (eat);
}

struct timeval	last_eat_time(t_philo *philo)
{
	struct timeval	eat_time;

	pthread_mutex_lock(&philo->he_ate_mutex);
	eat_time = philo->last_time_he_ate;
	pthread_mutex_unlock(&philo->he_ate_mutex);
	return (eat_time);
}

void	print_log(t_philo *philo, char *log, char *color)
{
	struct timeval	tv;

	(void) color;
	if (!is_end(philo))
	{
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&philo->data->printf_mutex);
		printf("%09ld %d %s\n", time_ms(tv, &philo->param.start),
			philo->id, log);
		// printf("%s%09ld %d %s\n%s", color, time_ms(tv, philo),
		// 	philo->id, log, NC);
		pthread_mutex_unlock(&philo->data->printf_mutex);
	}
}
