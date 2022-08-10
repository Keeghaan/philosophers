/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:08:35 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 12:08:53 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	free_all(t_data *data, t_philo *philo, int mutex)
{
	if (mutex)
	{
		destroy_four(data, philo);
		pthread_mutex_destroy(&data->stop);
	}
	free(data->forks);
	free(philo);
}
