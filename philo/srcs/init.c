/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:18:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 12:17:13 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_args(int ac, char **av)
{
	int	j;

	j = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"), 1);
	while (j < ac)
	{
		if (!all_num(av[j]))
			return (printf("Only positive numbers expected\n"), 2);
		j++;
	}
	return (0);
}

int	data_init(int ac, char **av, t_data *data)
{
	data->n_ph = ft_atoi(av[1]);
	data->to_die = ft_atoi(av[2]);
	data->to_eat = ft_atoi(av[3]);
	data->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (!data->n_ph)
		return (printf("At least one philosopher expected\n"), 1);
	if (!data->must_eat)
		return (2);
	data->the_end = 0;
	return (0);
}

int	mutex_init(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_ph);
	if (!data->forks)
		return (1);
	while (++j < data->n_ph)
	{
		if (pthread_mutex_init(&philo[j].eat, NULL) != 0)
			return (printf("Eat mutex init error\n"), 2);
		if (pthread_mutex_init(&philo[j].mutex, NULL) != 0)
			return (printf("Mutex mutex init error\n"), 3);
		if (pthread_mutex_init(&data->forks[j], NULL) != 0)
			return (printf("Fork mutex init error\n"), 4);
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (printf("Print mutex init error\n"), 5);
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (printf("Stop mutex init error\n"), 6);
	return (0);
}

int	philo_init(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	while (++j < data->n_ph)
	{
		philo[j].n = j + 1;
		philo[j].eating = 0;
		philo[j].ate = 0;
		philo[j].last_meal = 0;
		philo[j].finish = 0;
		philo[j].data = data;
	}	
	return (0);
}
