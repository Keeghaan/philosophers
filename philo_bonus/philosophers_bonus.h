/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:54:51 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/11 14:38:20 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <wait.h>
# include <errno.h>
# include <signal.h>
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEAD "died"
# define TH_MAX 1024

typedef struct s_data
{
	struct timeval		start;
	struct timeval		timestamp;
	pid_t				*pid;
	sem_t				*forks;
	sem_t				*stop;
	sem_t				*print;
	int					n_ph;
	int					to_die;
	int					to_eat;
	int					to_sleep;
	int					must_eat;
	int					the_end;
}	t_data;	

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			th;
	sem_t				*eat;
	int					n;
	int					eating;
	int					ate;
	int					last_meal;
	int					finish;
}	t_philo;

int		data_init(int ac, char **av, t_data *data);
int		check_args(int ac, char **av);
int		ft_atoi(const char *s);
int		all_num(char *s);
int		get_timestamp(t_data *data);
int		check_stop(t_data *data, t_philo *philo);
int		check_dead(t_data *data);
int		init_sem(t_data *data, t_philo *philo);
void	free_and_kill(t_data *data, t_philo *philo, int last);
void	exit_philo(t_data *data, t_philo *philo);
void	close_s(t_data *data, int file);
void	fork_func(t_philo *philo, int take);
void	philo_init(t_data *data, t_philo **philo);
void	print_func(t_data *data, int n, char *action);
void	process(t_data *data, t_philo *philo, int j);
void	one_philo(t_data *data, t_philo *philo);
void	close_process(t_data *data);
#endif
