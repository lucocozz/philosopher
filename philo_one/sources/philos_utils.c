/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 23:12:08 by lucocozz          #+#    #+#             */
/*   Updated: 2021/07/05 21:31:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_die(void *args)
{
	t_state	*state;
	t_philo	*philo;

	state = ((t_args *)args)->state;
	philo = ((t_args *)args)->philo;
	while ((philo->nb_eat < state->max_eat || state->max_eat == 0)
		&& read_mutex(&state->philos_dead) == 0)
	{
		if (gettime() - philo->last_meal >= state->time.die)
		{
			do_action(state, philo, Die, 0);
			write_mutex(&state->philos_dead, 1);
		}
	}
	return (NULL);
}

t_args	*create_philos(t_state *state)
{
	int		i;
	t_args	*args;

	i = 0;
	args = malloc(sizeof(t_args) * state->nb_philo);
	while (i < state->nb_philo)
	{
		args[i] = (t_args){.state = state, .philo = &state->philos[i]};
		pthread_create(&state->philos[i].thread, NULL, &routine, &args[i]);
		pthread_create(&state->philos[i].die_thread, NULL, &philo_die,
			&args[i]);
		i++;
	}
	return (args);
}

void	join_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
	{
		pthread_join(state->philos[i].thread, NULL);
		pthread_join(state->philos[i++].die_thread, NULL);
	}
}

void	exit_philos(t_state *state, t_args *args)
{
	int	i;

	i = 0;
	free(args);
	while (i < state->nb_philo)
		pthread_mutex_destroy(&state->forks[i++]);
	pthread_mutex_destroy(&state->philos_dead.lock);
	pthread_mutex_destroy(&state->output.lock);
	free(state->forks);
	free(state->philos);
}
