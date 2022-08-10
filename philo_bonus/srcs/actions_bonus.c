/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:57:09 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 18:51:43 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	eating(t_philo *philo)
{
	philo->last_meal = get_timestamp(philo->data);
	fork_func(philo, 1);
	sem_wait((*philo).eat);
	print_func(philo->data, philo->n, EAT);
	sem_post((*philo).eat);
	usleep(philo->data->to_eat * 1000);
	philo->ate++;
	sem_wait((*philo).eat);
	if (philo->ate == philo->data->must_eat && !philo->finish)
		philo->finish = 1;
	sem_post((*philo).eat);
	fork_func(philo, 0);
}

void	*thread_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_dead(philo->data) && !philo->finish)
	{
		if (!check_dead(philo->data))
			eating(philo);
		print_func(philo->data, philo->n, SLEEP);
		usleep(philo->data->to_sleep * 1000);
		print_func(philo->data, philo->n, THINK);
	}
	return (NULL);
}

void	process(t_data *data, t_philo *philo, int j)
{
	(void)data;
	if (pthread_create(&philo[j].th, NULL,
			&thread_func, (void *)&philo[j]) != 0)
	{
		printf("Pthread create error (philo %d)\n", j);
		exit(1);
	}
	pthread_join(philo[j].th, NULL);
	pthread_detach(philo[j].th);
}

void	one_philo(t_data *data, t_philo *philo)
{
	printf("%d %d %s\n", get_timestamp(data), philo->n, FORK);
	usleep(data->to_die * 1000);
	printf("%d %d %s\n", get_timestamp(data), philo->n, DEAD);
}
