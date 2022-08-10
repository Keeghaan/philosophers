/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:47:51 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/10 12:15:28 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEAD "died"
# define TH_MAX 1024

typedef struct s_data
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		stop;
	struct timeval		start;
	struct timeval		timestamp;
	int					n_ph;
	int					to_die;
	int					to_eat;
	int					to_sleep;
	int					must_eat;
	int					the_end;
}	t_data;	

typedef struct s_philo
{
	pthread_t			th;
	pthread_mutex_t		eat;
	pthread_mutex_t		mutex;
	struct s_data		*data;
	int					n;
	int					eating;
	int					ate;
	int					last_meal;
	int					finish;
}	t_philo;

int		check_args(int ac, char **av);
int		data_init(int ac, char **av, t_data *data);
int		philo_init(t_data *data, t_philo *philo);
int		ft_atoi(const char *s);
int		all_num(char *s);
int		mutex_init(t_data *data, t_philo *philo);
int		check_stop(t_data *data, t_philo *philo);
int		check_dead(t_data *data);
int		get_timestamp(t_data *data);
void	usleep_func(t_data *data, int how_long);
void	*process(void *arg);
void	*one_philo(void *arg);
void	destroy_mutex(t_data *data, t_philo *philo, int err);
void	free_all(t_data *data, t_philo *philo, int mutex);
void	destroy_four(t_data *data, t_philo *philo);
void	destroy_three(t_data *data, t_philo *philo);
void	destroy_two(t_philo *philo);
void	print_func(t_data *data, int num, char *action, int thread);
void	fork_func(t_philo *philo, int lock);
#endif
