/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:30:59 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 16:37:13 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	launch_one(t_philo *philo)
{
	if (pthread_create(&philo[0].th, NULL,
			&one_philo, (void *)&philo[0]) != 0)
		return (printf("Pthread create one error\n"), 1);
	pthread_join(philo[0].th, NULL);
	pthread_detach(philo[0].th);
	return (0);
}

int	thread_launch(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	gettimeofday(&data->start, NULL);
	if (data->n_ph == 1)
		return (launch_one(philo), 0);
	while (++j < data->n_ph)
	{
		if (j % 2 != 0)
			usleep(1000);
		if (pthread_create(&philo[j].th, NULL,
				&process, (void *)&philo[j]) != 0)
			return (printf("Pthread create error\n"), 1);
	}
	while (1)
	{
		if (check_stop(data, philo))
		{
			pthread_mutex_lock(&data->stop);
			data->the_end = 1;
			return (pthread_mutex_unlock(&data->stop), 0);
		}
	}
	return (0);
}

void	thread_exit(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	if (data->n_ph > 1)
	{
		while (++j < data->n_ph)
			pthread_join(philo[j].th, NULL);
	}
	free_all(data, philo, 1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		err;

	if (check_args(ac, av))
		return (1);
	err = data_init(ac, av, &data);
	if (err)
	{
		if (err == 4)
			return (free(data.forks), 2);
		return (2);
	}
	philo = malloc(sizeof(t_philo) * data.n_ph);
	if (!philo)
		return (3);
	err = mutex_init(&data, philo);
	if (err)
		return (destroy_mutex(&data, philo, err), free(philo), 4);
	if (philo_init(&data, philo))
		return (free_all(&data, philo, 1), 5);
	thread_launch(&data, philo);
	thread_exit(&data, philo);
	return (0);
}
