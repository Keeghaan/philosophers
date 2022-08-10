/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:28:39 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 16:30:19 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

void	print_func(t_data *data, int num, char *action, int thread)
{
	int	time;

	if (thread)
		pthread_mutex_lock(&data->stop);
	time = get_timestamp(data);
	pthread_mutex_lock(&data->print);
	if (thread && !data->the_end)
		printf("%d %d %s\n", time, num, action);
	if (!thread)
		printf("%d %d %s\n", time, num, action);
	pthread_mutex_unlock(&data->print);
	if (thread)
		pthread_mutex_unlock(&data->stop);
}

void	usleep_func(t_data *data, int how_long)
{
	int	time;

	time = get_timestamp(data) * 1000;
	while ((get_timestamp(data) * 1000) - time < how_long * 1000)
		usleep(10);
}

static void	fork_mutex(t_philo *philo, int lock, int n)
{
	if (lock)
	{
		pthread_mutex_lock(&philo->data->forks[n]);
		print_func(philo->data, philo->n, FORK, 1);
	}
	else
		pthread_mutex_unlock(&philo->data->forks[n]);
}

void	fork_func(t_philo *philo, int lock)
{
	if (philo->n % 2 != 0)
	{
		fork_mutex(philo, lock, philo->n - 1);
		if (philo->n == philo->data->n_ph)
			fork_mutex(philo, lock, 0);
		else
			fork_mutex(philo, lock, philo->n);
	}
	else
	{
		if (philo->n == philo->data->n_ph)
			fork_mutex(philo, lock, 0);
		else
			fork_mutex(philo, lock, philo->n);
		fork_mutex(philo, lock, philo->n - 1);
	}
}
