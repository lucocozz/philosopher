/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 23:12:08 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/02 13:57:23 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	create_philos(t_state *state)
{
	int		i;
	t_args	*args;

	i = 0;
	args = malloc(sizeof(t_args) * state->nb_philo);
	while (i < state->nb_philo)
	{
		args[i] = (t_args){.state = state, .philo = &state->philos[i]};
		pthread_create(&state->philos[i].thread, NULL, &routine, &args[i]);
		i++;
	}
	free(args);
}

void	join_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_philo)
		pthread_join(state->philos[i++].thread, NULL);
}

void	exit_philos(t_state *state)
{
	int	i;

	i = 0;
	if (i < state->nb_philo)
		pthread_mutex_destroy(&state->forks[i++]);
	free(state->forks);
	free(state->philos);
}
