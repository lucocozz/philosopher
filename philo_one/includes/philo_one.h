/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:24:13 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/02 14:51:39 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_action
{
	Take_fork,
	Eat,
	Sleep,
	Think,
	Die,
}					t_action;

typedef struct s_time
{
	int				sleep;
	int				die;
	int				eat;
	int				start;
}					t_time;

typedef struct s_philo
{
	int				nb;
	int				nb_eat;
	int				last_meal;
	int				is_dead;
	pthread_t		thread;
}					t_philo;

typedef struct s_state
{
	int				nb_philo;
	int				max_eat;
	int				philos_dead;
	t_time			time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_state;

typedef struct s_args
{
	t_state			*state;
	t_philo			*philo;
}					t_args;

//	utils/
int					ft_isnumber(const char *s);
int					ft_atoi(const char *str);

//	time.c
unsigned int		gettime(void);
void				ft_usleep(unsigned int ms);

//	routine.c
void				*routine(void *args);

//	philos_utils.c
void				create_philos(t_state *state);
void				join_philos(t_state *state);
void				exit_philos(t_state *state);

#endif
