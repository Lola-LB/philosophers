/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:10:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/04/07 18:05:23 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define ARG_ERROR		"Wrong arguments"
# define MALLOC_ERROR	"Malloc failed"

# define FORK_LOG		"has taken a fork"
# define EAT_LOG		"is eating"
# define SLEEP_LOG		"is sleeping"
# define THINK_LOG		"is thinking"
# define DEATH_LOG		"died"

# define NC				"\e[0m"
# define WHITE			"\e[37m"
# define BLACK			"\e[30m"
# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"

typedef struct s_data {
	int				nb;
	int				global_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	printf_mutex;
}	t_data;

typedef struct s_philo{
	t_data			*data;
	int				id;
	int				number_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_eat;
	struct timeval	start;
	pthread_mutex_t	eat_mutex;
	int				number_of_times_he_ate;
	struct timeval	last_time_he_ate;
}	t_philo;

/* ************************************************************************** */
/*                                  thread.c                                  */
/* ************************************************************************** */

void			eat_routine(t_philo *philo);
void			*thread_routine(t_philo *philo);
void			death_check(t_philo *philo, int *finished_eating);
void			*death_thread(t_philo *philo);
void			create_processes(t_philo *philosophers);

/* ************************************************************************** */
/*                                   init.c                                   */
/* ************************************************************************** */

pthread_mutex_t	*init_forks(int nb);
t_philo			*init_philosophers(t_data *data, int ac, char **av);
t_philo			init_philo(int i, t_data *data, int ac, char **av);
t_data			init_data(char **av);
int				fork_id(t_philo *philo, int first);

/* ************************************************************************** */
/*                                   util.c                                   */
/* ************************************************************************** */

long			time_ms(struct timeval tv, t_philo *philo);
int				is_end(t_philo *philo, int e);
void			print_log(t_philo *philo, char *log, char *color);
int				number_of_times_he_ate(t_philo *philo);
struct timeval	last_eat_time(t_philo *philo);

/* ************************************************************************** */
/*                                    lib.c                                   */
/* ************************************************************************** */

int				ft_error(char *error);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
int				ft_strdigit(char *str);
int				ft_atoi(char *str);

/* ************************************************************************** */
/*                                   free.c                                   */
/* ************************************************************************** */

void			free_forks(pthread_mutex_t *forks, int nb);
void			free_philo(t_philo *philosophers);
void			ft_usleep(long time_to_sleep);

#endif