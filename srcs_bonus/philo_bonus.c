/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:13:39 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:09:52 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;

	if (!check_args(ac, av))
		ft_error(ARG_ERROR);
	sem_unlink(FORKS);
	data = init_data(ac, av);
	if (!data.nb)
		return (0);
	if (!data.forks)
		ft_error(SEM_ERROR);
	philosophers = init_philosophers(&data);
	if (!philosophers)
	{
		sem_unlink(FORKS);
		ft_error(MALLOC_ERROR);
	}
	create_processes(philosophers);
	free_philo(philosophers);
	return (0);
}

void	free_philo(t_philo *philosophers)
{
	sem_close(philosophers->data->forks);
	sem_unlink(FORKS);
	free(philosophers);
}
