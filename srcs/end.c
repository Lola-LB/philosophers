/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:30:11 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 12:31:46 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->end_mutex);
	end = philo->end;
	pthread_mutex_unlock(&philo->end_mutex);
	return (end);
}

void	global_end(t_death *death, t_philo *philo)
{
	int	j;

	j = -1;
	while (++j < philo->param.number_of_philo)
	{
		pthread_mutex_lock(&philo[j].end_mutex);
		philo[j].end = 1;
		pthread_mutex_unlock(&philo[j].end_mutex);
	}
	pthread_mutex_lock(&death->global_end_mutex);
	death->global_end = 1;
	pthread_mutex_unlock(&death->global_end_mutex);
}

int	check_global_end(t_death *death)
{
	int	end;

	pthread_mutex_lock(&death->global_end_mutex);
	end = death->global_end;
	pthread_mutex_unlock(&death->global_end_mutex);
	return (end);
}
