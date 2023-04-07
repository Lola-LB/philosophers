/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:13:39 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 17:51:15 by lle-bret         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;

	if (!check_args(ac, av))
		return (ft_error(ARG_ERROR));
	data = init_data(av);
	if (!data.nb)
		return (0);
	if (!data.forks)
		return (ft_error(MALLOC_ERROR));
	philosophers = init_philosophers(&data, ac, av);
	if (!philosophers)
	{
		free_forks(data.forks, data.nb);
		return (ft_error(MALLOC_ERROR));
	}
	create_processes(philosophers);
	free_philo(philosophers);
	return (0);
}
