/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:41:48 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 13:52:24 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mut, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(mut + i);
		++i;
	}
	free_if(mut);
}

void	free_shared_mutex(t_shared_mutex *shared_mutex, int n)
{
	free_mutex(shared_mutex->forks, n);
	free_mutex(shared_mutex->printf_mutex, 1);
	free_if(shared_mutex);
}

void	free_data(t_data *data)
{
	free_mutex(data->global_end_mutex, 1);
	free_if(data);
}

void	free_all(t_data *data)
{
	free_shared_mutex(data->shared_mutex, data->param.number_of_philo);
	free_mutex(data->philo->end_mutex, data->param.number_of_philo);
	free_mutex(data->philo->he_ate_mutex, data->param.number_of_philo);
	free_if(data->philo);
	free_data(data);
}

void	free_if(void *to_free)
{
	if (to_free)
		free(to_free);
}
