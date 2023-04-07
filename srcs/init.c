/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:15 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:12:00 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int nb)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(forks + i, NULL);
		++i;
	}
	return (forks);
}

t_philo	*init_philosophers(t_data *data, int ac, char **av)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo) * data->nb);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb)
	{
		philosophers[i] = init_philo(i, data, ac, av);
		++i;
	}
	return (philosophers);
}

t_philo	init_philo(int i, t_data *data, int ac, char **av)
{
	t_philo	philo;

	philo.data = data;
	philo.number_of_philo = ft_atoi(av[1]);
	philo.time_to_die = (unsigned int) ft_atoi(av[2]);
	philo.time_to_eat = (unsigned int) ft_atoi(av[3]);
	philo.time_to_sleep = (unsigned int) ft_atoi(av[4]);
	if (ac == 6)
		philo.max_eat = ft_atoi(av[5]);
	else
		philo.max_eat = -1;
	philo.id = i;
	philo.number_of_times_he_ate = 0;
	gettimeofday(&philo.start, NULL);
	gettimeofday(&philo.last_time_he_ate, NULL);
	pthread_mutex_init(&philo.eat_mutex, NULL);
	return (philo);
}

t_data	init_data(char **av)
{
	t_data	data;

	data.nb = ft_atoi(av[1]);
	if (data.nb)
	{
		data.global_end = 0;
		pthread_mutex_init(&data.end_mutex, NULL);
		pthread_mutex_init(&data.printf_mutex, NULL);
		data.forks = init_forks(data.nb);
	}
	return (data);
}

int	fork_id(t_philo *philo, int first)
{
	if (first)
		return (philo->id * (philo->id % 2 == 1) + (philo->id % 2 == 0)
			* ((philo->id + 1) % (philo->data->nb)));
	return (philo->id * (philo->id % 2 == 0)
		+ (philo->id % 2 == 1) * ((philo->id + 1)
			% (philo->data->nb)));
}
