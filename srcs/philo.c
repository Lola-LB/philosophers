/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:13:39 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/10 12:12:18 by lle-bret         ###   ########.fr       */
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
	t_param	param;
	t_death	death;
	t_philo	*philosophers;

	if (!check_args(ac, av))
		return (ft_error(ARG_ERROR));
	param = init_param(ac, av);
	if (!param.number_of_philo)
		return (0);
	data = init_data(param.number_of_philo);
	if (!data.forks)
		return (ft_error(MALLOC_ERROR));
	philosophers = init_philosophers(&data, param);
	if (!philosophers)
	{
		free_forks(data.forks, param.number_of_philo);
		return (ft_error(MALLOC_ERROR));
	}
	death = init_death(&data, philosophers);
	create_processes(&death, philosophers);
	free_philo(&death);
	return (0);
}
