/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:16:14 by lle-bret          #+#    #+#             */
/*   Updated: 2023/05/11 13:57:47 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		++len;
	return (len);
}

int	ft_error(char *str)
{
	printf("Error: %s\n", str);
	return (0);
}

int	ft_strdigit(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (i < ft_strlen(str))
	{
		c = str[i];
		if (!((c < 256) && '0' <= (char) c && (char) c <= '9'))
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
	while ((((int) *str < 256) && '0' <= (int) *str
			&& (int) *str <= '9'))
	{
		res = 10 * res + *str - '0';
		++str;
	}
	return (sign * res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;
	int		n;

	n = size * nmemb;
	buff = malloc(n);
	if (!buff)
		return (NULL);
	while (n > 0)
	{
		*(char *)(buff + n - 1) = 0;
		--n;
	}
	return (buff);
}
