/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:13:39 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 14:03:56 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	while (--ac)
	{
		if (!ft_strdigit(av[ac + 1]))
			return (0);
	}
	return (1);
}

void	create_processes(t_data *data, t_philo *philo)
{
	int			i;
	int			nb;
	pthread_t	*tid;

	nb = data->param.number_of_philo;
	tid = (pthread_t *) ft_calloc(sizeof(pthread_t), nb + 1);
	if (!tid)
	{
		free_all(data);
		return ;
	}
	i = -1;
	while (++i < nb)
	{
		pthread_create(tid + i, NULL,
			(void *)(*thread_routine), philo + i);
	}
	pthread_create(tid + i, NULL,
		(void *)(*death_thread), (void *) data);
	i = -1;
	while (++i < nb + 1)
		pthread_join(tid[i], NULL);
	free(tid);
}

int	main(int ac, char **av)
{
	t_param	param;
	t_data	*data;

	if (!check_args(ac, av))
		return (ft_error(ARG_ERROR));
	param = init_param(ac, av);
	if (!param.number_of_philo)
		return (0);
	data = init_data(param);
	if (!data)
		return (ft_error(MALLOC_ERROR));
	data->philo = init_philosophers(data);
	if (!data->philo)
	{
		free_shared_mutex(data->shared_mutex, param.number_of_philo);
		free_data(data);
		return (ft_error(MALLOC_ERROR));
	}
	create_processes(data, data->philo);
	free_all(data);
	return (0);
}
