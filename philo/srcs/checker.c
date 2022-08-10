/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:21:10 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 16:39:35 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	dead_func(t_data *data, t_philo philo)
{
	pthread_mutex_lock(&data->stop);
	data->the_end = 1;
	print_func(data, philo.n, DEAD, 0);
	pthread_mutex_unlock(&data->stop);
}

int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->the_end)
		return (pthread_mutex_unlock(&data->stop), 1);
	return (pthread_mutex_unlock(&data->stop), 0);
}

int	check_stop(t_data *data, t_philo *philo)
{
	int	j;
	int	stop;

	j = -1;
	stop = 1;
	while (++j < data->n_ph)
	{
		pthread_mutex_lock(&philo[j].mutex);
		if (!philo[j].finish)
			stop = 0;
		pthread_mutex_unlock(&philo[j].mutex);
		pthread_mutex_lock(&philo[j].mutex);
		if (get_timestamp(data) - philo[j].last_meal >= data->to_die)
		{
			dead_func(data, philo[j]);
			return (pthread_mutex_unlock(&philo[j].mutex), 1);
		}
		pthread_mutex_unlock(&philo[j].mutex);
	}
	if (stop)
		return (1);
	return (0);
}
