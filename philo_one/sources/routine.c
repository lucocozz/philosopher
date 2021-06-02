/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 02:21:05 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/02 14:25:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	do_action(int start_time, int nb, t_action action, int time)
{
	static char	*events[5] = {
		[Take_fork] = "has taken a fork",
		[Eat] = "is eating",
		[Sleep] = "is spleeping",
		[Think] = "is thinking",
		[Die] = "died"
	};

	printf("%dms %d %s\n", gettime() - start_time, nb, events[action]);
	ft_usleep(time);
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
	do_action(state->start, philo->nb, Take_fork, 0);
	do_action(state->start, philo->nb, Take_fork, 0);
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
		do_action(state->start, philo->nb, Eat, state->time.eat);
		philo->nb_eat++;
		philo->last_meal = gettime();
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
		&& state->is_dead == 0)
	{
		eat(philo, state);
		if ((gettime() - philo->last_meal) + state->time.sleep
			>= (unsigned int)state->time.die)
			state->is_dead++;
		else
		{
			do_action(state->start, philo->nb, Sleep, state->time.sleep);
			do_action(state->start, philo->nb, Think, 0);
		}
	}
	if (state->is_dead > 0)
		do_action(state->start, philo->nb, Die, 0);
	return (NULL);
}
