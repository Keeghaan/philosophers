/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:59:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/11 14:41:11 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	close_process(t_data *data)
{
	int	j;
	int	status;

	j = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (j < data->n_ph)
			kill(data->pid[j], SIGKILL);
	}
}

void	close_s(t_data *data, int file)
{
	if (file == 3)
	{
		sem_unlink(".stop");
		sem_close(data->stop);
		file--;
	}
	if (file == 2)
	{
		sem_unlink(".print");
		sem_close(data->print);
		file--;
	}
	if (file == 1)
	{
		sem_unlink(".forks");
		sem_close(data->forks);
	}
}
/*
void	free_and_kill(t_data *data, t_philo *philo, int last)
{
	int	j;

	j = -1;
	close_s(data, 3);
	sem_unlink(".eat");
	while (++j < data->n_ph)
		sem_close(philo[j].eat);
	sem_close(philo->eat);
	while (++j)
}*/
