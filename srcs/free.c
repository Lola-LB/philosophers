/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:41:48 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 13:07:07 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(forks + i);
		++i;
	}
	free(forks);
}

void	free_philo(t_death *death)
{
	int	i;

	free_forks(death->data->forks, death->param.number_of_philo);
	i = -1;
	while (++i < death->param.number_of_philo)
	{
		pthread_mutex_destroy(death->philo[i].end_mutex);
		pthread_mutex_destroy(death->philo[i].he_ate_mutex);
	}
	pthread_mutex_destroy(death->data->printf_mutex);
	free(death->philo);
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
		usleep(1);
	}
}

void	free_if(void *to_free)
{
	if (to_free)
		free(to_free);
}