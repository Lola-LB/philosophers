/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:10:46 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define FORKS "forks"

# define ARG_ERROR "Wrong arguments"
# define MALLOC_ERROR "Malloc failed"
# define SEM_ERROR "Semaphore failed"
# define FORK_ERROR "Fork failed"
# define EAT_STATUS 0
# define SLEEP_STATUS 1
# define THINK_STATUS 2

# define FORK_LOG "has taken a fork"
# define EAT_LOG "is eating"
# define SLEEP_LOG "is sleeping"
# define THINK_LOG "is thinking"
# define DEATH_LOG "died"

# define NC	"\e[0m"
# define WHITE	"\e[37m"
# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"

typedef struct s_data {
	int				nb;
	sem_t			*forks;
	pid_t			*pid;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_of_times_philo_must_eat;
}	t_data;

typedef struct s_philo{
	t_data			*data;
	int				id;
	struct timeval	start;
	int				number_of_times_he_ate;
	struct timeval	last_time_he_ate;
}	t_philo;

/* ************************************************************************** */
/*                               process_bonus.c                              */
/* ************************************************************************** */

void			eat_routine(t_philo *philo);
void			process_routine(t_philo *philo);
void			create_processes(t_philo *philosophers);

/* ************************************************************************** */
/*                               init_bonus.c                                 */
/* ************************************************************************** */

t_philo			*init_philosophers(t_data *data);
t_philo			init_philo(int i, t_data *data);
t_data			init_data(int ac, char **av);

/* ************************************************************************** */
/*                               util_bonus.c                                 */
/* ************************************************************************** */

long			time_ms(struct timeval tv, t_philo *philo);
int				is_end(t_philo *philo);
void			print_log(t_philo *philo, char *log, char *color);
void			ft_usleep(long time_to_sleep);
void			ft_exit(t_philo *philo);

/* ************************************************************************** */
/*                               lib_bonus.c                                  */
/* ************************************************************************** */

void			ft_error(char *error);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
int				ft_strdigit(char *str);
int				ft_atoi(char *str);

/* ************************************************************************** */
/*                               philo_bonus.c                                */
/* ************************************************************************** */

void			free_philo(t_philo *philosophers);

#endif