/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:15 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 14:07:44 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_param	init_param(int ac, char **av)
{
	t_param			param;
	struct timeval	now;

	gettimeofday(&now, NULL);
	param.start = (long) now.tv_sec * 1000 + (long) now.tv_usec / 1000;
	param.number_of_philo = ft_atoi(av[1]);
	param.time_to_die = (unsigned int) ft_atoi(av[2]);
	param.time_to_eat = (unsigned int) ft_atoi(av[3]);
	param.time_to_sleep = (unsigned int) ft_atoi(av[4]);
	if (ac == 6)
		param.max_eat = ft_atoi(av[5]);
	else
		param.max_eat = -1;
	return (param);
}

t_shared_mutex	*init_shared_mutex(int nb)
{
	t_shared_mutex	*shared_mutex;
	pthread_mutex_t	*forks;
	int				i;

	shared_mutex = malloc(sizeof(t_shared_mutex));
	if (!shared_mutex)
		return (NULL);
	shared_mutex->printf_mutex = malloc(sizeof(pthread_mutex_t));
	forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (!forks || !shared_mutex->printf_mutex)
	{
		free_if(shared_mutex->printf_mutex);
		free_if(forks);
		free(shared_mutex);
		return (NULL);
	}
	pthread_mutex_init(shared_mutex->printf_mutex, NULL);
	shared_mutex->forks = forks;
	i = -1;
	while (++i < nb)
		pthread_mutex_init(forks + i, NULL);
	return (shared_mutex);
}

t_philo	*init_philo(t_philo *philosophers, t_data *data,
	pthread_mutex_t *end_mutex, pthread_mutex_t *he_ate_mutex)
{
	int	i;

	i = -1;
	while (++i < data->param.number_of_philo)
	{
		philosophers[i].shared_mutex = data->shared_mutex;
		philosophers[i].param = data->param;
		philosophers[i].id = i;
		philosophers[i].last_time_he_ate = data->param.start;
		philosophers[i].number_of_times_he_ate = 0;
		philosophers[i].he_ate_mutex = he_ate_mutex + i;
		pthread_mutex_init(philosophers[i].he_ate_mutex, NULL);
		philosophers[i].end = 0;
		philosophers[i].end_mutex = end_mutex + i;
		pthread_mutex_init(philosophers[i].end_mutex, NULL);
	}
	return (philosophers);
}

t_philo	*init_philosophers(t_data *data)
{
	t_philo			*philosophers;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*he_ate_mutex;

	philosophers = malloc(sizeof(t_philo) * data->param.number_of_philo);
	end_mutex = malloc(sizeof(pthread_mutex_t) * data->param.number_of_philo);
	he_ate_mutex = malloc(sizeof(pthread_mutex_t)
			* data->param.number_of_philo);
	if (!philosophers || !end_mutex || !he_ate_mutex)
	{
		free_if(philosophers);
		free_if(end_mutex);
		free_if(he_ate_mutex);
		return (NULL);
	}
	return (init_philo(philosophers, data, end_mutex, he_ate_mutex));
}

t_data	*init_data(t_param param)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->param = param;
	data->global_end_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->global_end_mutex)
	{
		free(data);
		return (NULL);
	}
	pthread_mutex_init(data->global_end_mutex, NULL);
	data->global_end = 0;
	data->shared_mutex = init_shared_mutex(param.number_of_philo);
	if (!data->shared_mutex)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
