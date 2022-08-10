/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:59:50 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/05 13:59:52 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	all_num(char *s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] < 48 || s[j] > 57)
			return (0);
		j++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (s * n);
}
