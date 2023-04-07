/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:16:14 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:10:28 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		++len;
	return (len);
}

void	ft_error(char *str)
{
	printf("Error: %s\n", str);
	exit(0);
}

int	ft_isdigit(int c)
{
	return ((c < 256) && '0' <= (char) c && (char) c <= '9');
}

int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		++str;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '+') - (*str == '-');
		++str;
	}
	while (ft_isdigit(*str))
	{
		res = 10 * res + *str - '0';
		++str;
	}
	return (sign * res);
}
