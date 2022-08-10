/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:59:10 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 18:33:14 by jcourtoi         ###   ########.fr       */
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

static int	philosophers(t_data *data, t_philo *philo)
{
	int	j;
	int	status;
//(void)philo;
	j = -1;
	gettimeofday(&data->start, NULL);
	while (++j < data->n_ph && !check_dead(data))
	{
		data->pid[j] = fork();
		status = getpid();
		if (check_stop(data, philo))
		{
			data->the_end = 1;
			break ;
		}
		if (j % 2 != 0)
			usleep(1000);
		if (data->pid[j] < 0)
			return (printf("Fork error(pid[%d])\n", j), 1);
		if (data->pid[j] == 0)
			process(data, philo, j);
	}
	j = -1;
	while (++j < data->n_ph && !data->the_end)
	{
		waitpid(data->pid[j], NULL, 0);
		kill(status, SIGINT);
		kill(status, SIGQUIT);
		kill(status, SIGHUP);
	}
	return (0);
}

void	exit_philo(t_data *data, t_philo *philo)
{
	close_s(data, 3);
	sem_unlink(".eat");
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
