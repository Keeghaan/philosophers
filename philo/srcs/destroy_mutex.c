/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:33:15 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/04 14:00:22 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_two(t_philo *philo)
{
	int	j;

	j = -1;
	while (++j < philo->data->n_ph)
	{
		pthread_mutex_destroy(&philo[j].eat);
		pthread_mutex_destroy(&philo[j].mutex);
	}
}

void	destroy_three(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	destroy_two(philo);
	while (++j < data->n_ph)
		pthread_mutex_destroy(&data->forks[j]);
}

void	destroy_four(t_data *data, t_philo *philo)
{
	destroy_three(data, philo);
	pthread_mutex_destroy(&data->print);
}

void	destroy_mutex(t_data *data, t_philo *philo, int err)
{
	int	j;

	j = -1;
	if (err == 1)
		return ;
	else if (err == 6)
		destroy_four(data, philo);
	else if (err == 5)
		destroy_three(data, philo);
	else if (err == 4)
		destroy_two(philo);
	else if (err == 3)
	{
		while (++j < data->n_ph)
			pthread_mutex_destroy(&philo[j].eat);
	}
	else
		free(data->forks);
}
