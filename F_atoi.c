/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_atoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:53:23 by abouzanb          #+#    #+#             */
/*   Updated: 2023/01/29 23:37:46 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	helper_function(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
			i++;
	if (s[i] == '-')
		return (-1);
	return (i);
}

int	ft_atoi(const char *s)
{
	int			i;
	long		x;
	int			type;
	long		l;

	type = 1;
	i = helper_function(s);
	if (i < 0)
		return (-1);
	x = 0;
	l = 0;
	while (s[i] <= '9' && s[i] >= '0')
	{
		x = x * 10 + (s[i] - 48);
		if ((x > 2147483647 && type == 1) || ((x > 2147483648 && type == -1)))
		{
			write(2, "Error\n", 6);
			return (-1);
		}
		i++;
		l = x;
	}
	return (x * type);
}
