/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:51:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 16:38:34 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eating(t_philo *philo)
{
	fork_func(philo, 1);
	philo->last_meal = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->eat);
	print_func(philo->data, philo->n, EAT, 1);
	pthread_mutex_unlock(&philo->eat);
	usleep_func(philo->data, philo->data->to_eat);
	philo->ate++;
	if (philo->ate == philo->data->must_eat && !philo->finish)
	{
		pthread_mutex_lock(&philo->data->stop);
		philo->finish = 1;
		pthread_mutex_unlock(&philo->data->stop);
	}
	fork_func(philo, 0);
}

void	*process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_dead(philo->data) && !philo->finish)
	{
		if (!check_dead(philo->data))
			eating(philo);
		print_func(philo->data, philo->n, SLEEP, 1);
		usleep_func(philo->data, philo->data->to_sleep);
		print_func(philo->data, philo->n, THINK, 1);
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_func(philo->data, philo->n, FORK, 1);
	usleep_func(philo->data, philo->data->to_die);
	print_func(philo->data, philo->n, DEAD, 1);
	return (NULL);
}
