/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:15 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 13:34:59 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_param	init_param(int ac, char **av)
{
	t_param	param;

	gettimeofday(&param.start, NULL);
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

t_data	init_data(int nb)
{
	t_data			data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mut;
	int				i;

	data.printf_mutex = &printf_mut;
	pthread_mutex_init(data.printf_mutex, NULL);
	forks = malloc(sizeof(pthread_mutex_t) * nb);
	data.forks = forks;
	if (!data.forks)
		return (data);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(forks + i, NULL);
		++i;
	}
	return (data);
}

t_philo	*init_philosophers(t_data *data, t_param param)
{
	t_philo			*philosophers;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*he_ate_mutex;
	int				i;

	philosophers = malloc(sizeof(t_philo) * param.number_of_philo);
	end_mutex = malloc(sizeof(pthread_mutex_t) * param.number_of_philo);
	he_ate_mutex = malloc(sizeof(pthread_mutex_t) * param.number_of_philo);
	if (!philosophers || !end_mutex || !he_ate_mutex)
	{
		free_if(philosophers);
		free_if(end_mutex);
		free_if(he_ate_mutex);
		return (NULL);
	}
	i = -1;
	while (++i < param.number_of_philo)
	{
		philosophers[i].data = data;
		philosophers[i].param = param;
		philosophers[i].id = i;
		gettimeofday(&philosophers[i].last_time_he_ate, NULL);
		philosophers[i].number_of_times_he_ate = 0;
		philosophers[i].he_ate_mutex = he_ate_mutex + i;
		pthread_mutex_init(philosophers[i].he_ate_mutex, NULL);
		philosophers[i].end = 0;
		philosophers[i].end_mutex = end_mutex + i;
		// printf("init %i: %p\n", i, philosophers[i].end_mutex );
		pthread_mutex_init(philosophers[i].end_mutex, NULL);
	}
	return (philosophers);
}

t_death	init_death(t_data *data, t_philo *philo)
{
	t_death	death;
	pthread_mutex_t	global_end_mut;

	death.philo = philo;
	death.param = philo->param;
	death.data = data;
	death.global_end_mutex = &global_end_mut;
	pthread_mutex_init(death.global_end_mutex, NULL);
	death.global_end = 0;
	return (death);
}

int	fork_id(t_philo *philo, int first)
{
	if (first)
		return (philo->id * (philo->id % 2 == 1) + (philo->id % 2 == 0)
			* ((philo->id + 1) % (philo->param.number_of_philo)));
	return (philo->id * (philo->id % 2 == 0)
		+ (philo->id % 2 == 1) * ((philo->id + 1)
			% (philo->param.number_of_philo)));
}
