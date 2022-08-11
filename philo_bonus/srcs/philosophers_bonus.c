/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:59:10 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/11 14:57:01 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

static	int	philosopher(t_data *data, t_philo *philo)
{
	gettimeofday(&data->start, NULL);
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		return (printf("Fork error\n"), 1);
	if (data->pid[0] == 0)
		one_philo(data, philo);
	waitpid(data->pid[0], NULL, 0);
	return (0);
}

static void	wait_pid(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->n_ph && !data->the_end)
		waitpid(data->pid[j], NULL, 0);
}

static int	philosophers(t_data *data, t_philo *philo)
{
	int	j;

	j = -1;
	gettimeofday(&data->start, NULL);
	while (++j < data->n_ph && !check_dead(data))
	{
		if (!check_dead(data))
		{
			data->pid[j] = fork();
			if (j % 2 != 0)
				usleep(1000);
			if (data->pid[j] < 0)
				return (printf("Fork error(pid[%d])\n", j), 1);
			if (data->pid[j] == 0)
				process(data, philo, j);
		}
	}
	while (1)
	{
		if (check_stop(data, philo))
		{
			data->the_end = 1;
			kill(data->pid[j], SIGINT);
		}
	}
	wait_pid(data);
	return (0);
}

void	exit_philo(t_data *data, t_philo *philo)
{
//	int	j;

//	j = -1;
	close_s(data, 3);
	sem_unlink(".eat");
//	while (++j < data->n_ph)
		sem_close(philo->eat);
	free(data->pid);
	free(philo);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (check_args(ac, av))
		return (1);
	if (data_init(ac, av, &data))
		return (2);
	philo = malloc(sizeof(t_philo) * data.n_ph);
	if (!philo)
		return (free(data.pid), 3);
	philo_init(&data, &philo);
	if (init_sem(&data, philo))
		return (free(data.pid), free(philo), 4);
	if (data.n_ph == 1)
		philosopher(&data, philo);
	else
		philosophers(&data, philo);
	exit_philo(&data, philo);
	return (0);
}
