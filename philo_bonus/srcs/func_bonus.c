/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:58:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 12:55:12 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	get_timestamp(t_data *data)
{
	int	time;
	int	time_usec;

	gettimeofday(&data->timestamp, NULL);
	time = data->timestamp.tv_sec - data->start.tv_sec;
	time_usec = data->timestamp.tv_usec / 1000 - data->start.tv_usec / 1000;
	time = (time * 1000) + time_usec;
	return (time);
}

void	print_func(t_data *data, int num, char *action)
{
	int	time;

	time = get_timestamp(data);
	sem_wait(data->print);
	printf("%d %d %s\n", time, num, action);
	sem_post(data->print);
}

void	usleep_func(t_data *data, int how_long)
{
	int	time;

	time = get_timestamp(data) * 1000;
	while ((get_timestamp(data) * 1000) - time < how_long * 1000)
		usleep(50);
}

void	fork_func(t_philo *philo, int take)
{
	if (take)
	{
		sem_wait(philo->data->forks);
		print_func(philo->data, philo->n, FORK);
		sem_wait(philo->data->forks);
		print_func(philo->data, philo->n, FORK);
	}
	else
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
	}
}
