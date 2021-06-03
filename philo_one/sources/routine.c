/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 02:21:05 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/03 20:52:42 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	do_action(t_state *state, t_philo *philo, t_action action, int time)
{
	static char	*actions[] = {
		[Take_fork] = "has taken a fork",
		[Eat] = "is eating",
		[Sleep] = "is spleeping",
		[Think] = "is thinking",
		[Die] = "died"
	};

	if (read_mutex(&state->output) == 0)
	{
		printf("[%d] %d %s\n", gettime() - state->time.start, philo->nb,
			actions[action]);
		ft_usleep(time);
	}
}

static int	take_forks(t_philo *philo, t_state *state)
{
	int	i;

	i = philo->nb;
	if (pthread_mutex_lock(&state->forks[i]) != 0)
		return (-1);
	if (pthread_mutex_lock(&state->forks[(i + 1) % state->nb_philo]) != 0)
	{
		pthread_mutex_unlock(&state->forks[i]);
		return (-1);
	}
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
	if (take_forks(philo, state) == 0)
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
		if (gettime() - philo->last_meal >= state->time.die)
		{
			do_action(state, philo, Die, 0);
			write_mutex(&state->philos_dead, 1);
			write_mutex(&state->output, 1);
		}
	}
	return (NULL);
}
