/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 02:21:05 by lucocozz          #+#    #+#             */
/*   Updated: 2021/10/25 15:43:10 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	do_action(t_state *state, t_philo *philo, t_action action, int time)
{
	static char	*actions[] = {
		[Take_fork] = "has taken a fork",
		[Eat] = "is eating",
		[Sleep] = "is spleeping",
		[Think] = "is thinking",
		[Die] = "died"
	};

	pthread_mutex_lock(&state->output.lock);
	if (state->output.value == 1)
	{
		if (action == Die)
			state->output.value = 0;
		printf("[%d] %d %s\n", gettime() - state->time.start, philo->nb,
			actions[action]);
		pthread_mutex_unlock(&state->output.lock);
		ft_usleep(time);
	}
	else
		pthread_mutex_unlock(&state->output.lock);
}

static int	take_forks(t_philo *philo, t_state *state)
{
	int	i;

	i = philo->nb;
	pthread_mutex_lock(&state->forks[i]);
	pthread_mutex_lock(&state->forks[(i + 1) % state->nb_philo]);
	do_action(state, philo, Take_fork, 0);
	do_action(state, philo, Take_fork, 0);
	return (0);
}

static void	put_forks(t_philo *philo, t_state *state)
{
	int	i;

	i = philo->nb;
	pthread_mutex_unlock(&state->forks[i]);
	pthread_mutex_unlock(&state->forks[(i + 1) % state->nb_philo]);
}

static void	eat(t_philo *philo, t_state *state)
{
	if (state->nb_philo > 1 && take_forks(philo, state) == 0)
	{
		philo->last_meal = gettime();
		do_action(state, philo, Eat, state->time.eat);
		philo->nb_eat++;
		put_forks(philo, state);
	}
}

void	*routine(void *args)
{
	t_state	*state;
	t_philo	*philo;

	state = ((t_args *)args)->state;
	philo = ((t_args *)args)->philo;
	while ((philo->nb_eat < state->max_eat || state->max_eat == 0)
		&& read_mutex(&state->philos_dead) == 0)
	{
		eat(philo, state);
		do_action(state, philo, Sleep, state->time.sleep);
		do_action(state, philo, Think, 0);
	}
	return (NULL);
}
