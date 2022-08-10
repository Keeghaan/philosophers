/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:58:55 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 18:35:51 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

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
	data->pid = malloc(sizeof(pid_t) * data->n_ph);
	if (!data->pid)
		return (3);
	return (0);
}

int	init_sem(t_data *data, t_philo *philo)
{
	sem_unlink(".forks");
	sem_unlink(".print");
	sem_unlink(".stop");
	sem_unlink(".eat");
	data->forks = sem_open(".forks", O_CREAT, 0644, data->n_ph);
	if (data->forks == SEM_FAILED)
		return (printf("sem_open forks error\n"), 2);
	data->print = sem_open(".print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (printf("sem_open print error\n"), close_s(data, 1), 3);
	data->stop = sem_open(".stop", O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
		return (printf("sem_open stop error\n"), close_s(data, 2), 4);
	int j = -1;
	while (++j < data->n_ph)
	{
		philo[j].eat = sem_open(".eat", O_CREAT, 0644, 1);
		if (philo[j].eat == SEM_FAILED)
			return (printf("sem_open eat error\n"), close_s(data, 3), 5);
	}
	return (0);
}

void	philo_init(t_data *data, t_philo **philo)
{
	int	j;

	j = -1;
	while (++j < data->n_ph)
	{
		(*philo)[j].n = j + 1;
		(*philo)[j].eating = 0;
		(*philo)[j].ate = 0;
		(*philo)[j].last_meal = 0;
		(*philo)[j].finish = 0;
		(*philo)[j].data = data;
	}
}
