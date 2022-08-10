/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:57:35 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 17:22:52 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	dead_func(t_data *data, t_philo philo)
{
	sem_wait(data->stop);
	data->the_end = 1;
	print_func(data, philo.n, DEAD);
	sem_post(data->stop);
}

int	check_dead(t_data *data)
{
	sem_wait(data->stop);
	if (data->the_end)
		return (sem_post(data->stop), 1);
	return (sem_post(data->stop), 0);
}

int	check_stop(t_data *data, t_philo *philo)
{
	int	j;
	int	stop;

	j = -1;
	stop = 1;
	while (++j < data->n_ph)
	{
		sem_wait(philo->eat);
		if (!philo[j].finish)
			stop = 0;
		sem_post(philo->eat);
		sem_wait(philo->eat);
		if (get_timestamp(data) - philo[j].last_meal >= data->to_die)
			return (dead_func(data, philo[j]), sem_post(philo->eat), 1);
		sem_post(philo->eat);
	}
	if (stop)
		return (1);
	return (0);
}
