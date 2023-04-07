/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:15 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:08:00 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philosophers(t_data *data)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo) * data->nb);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb)
	{
		philosophers[i] = init_philo(i, data);
		++i;
	}
	return (philosophers);
}

t_philo	init_philo(int i, t_data *data)
{
	t_philo	philo;

	philo.data = data;
	philo.id = i;
	philo.number_of_times_he_ate = 0;
	gettimeofday(&philo.start, NULL);
	gettimeofday(&philo.last_time_he_ate, NULL);
	return (philo);
}

t_data	init_data(int ac, char **av)
{
	t_data	data;

	data.nb = ft_atoi(av[1]);
	if (data.nb)
	{
		data.time_to_eat = (long) ft_atoi(av[3]);
		data.time_to_sleep = (long) ft_atoi(av[4]);
		data.time_to_die = (long) ft_atoi(av[2]);
		if (ac == 6)
			data.nb_of_times_philo_must_eat = ft_atoi(av[5]);
		else
			data.nb_of_times_philo_must_eat = -1;
		data.forks = sem_open(FORKS, O_CREAT | O_EXCL, 777, data.nb);
	}
	return (data);
}
