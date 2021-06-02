/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:29:39 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/02 14:52:06 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	parse_arg(t_state *state, int nb, char **arg)
{
	int		i;

	i = 0;
	if (!(nb >= 4 && nb <= 5))
		return (-1);
	while (i < nb)
		if (ft_isnumber(arg[i++]) == 0)
			return (-1);
	state->nb_philo = ft_atoi(arg[0]);
	state->time = (t_time){
		.die = ft_atoi(arg[1]),
		.eat = ft_atoi(arg[2]),
		.sleep = ft_atoi(arg[3]),
		.start = gettime()
	};
	if (nb == 5)
		state->max_eat = ft_atoi(arg[4]);
	else
		state->max_eat = 0;
	return (0);
}

static int	init_state(t_state *state, int nb, char **arg)
{
	int	i;

	i = 0;
	if (parse_arg(state, nb, arg) == -1)
		return (-1);
	state->philos = malloc(sizeof(t_philo) * state->nb_philo);
	if (state->philos == NULL)
		return (-1);
	state->forks = malloc(sizeof(pthread_mutex_t) * state->nb_philo);
	if (state->forks == NULL)
	{
		free(state->philos);
		return (-1);
	}
	while (i < state->nb_philo)
	{
		state->philos[i].nb = i;
		state->philos[i].nb_eat = 0;
		state->philos[i].is_dead = 0;
		state->philos[i].last_meal = gettime();
		pthread_mutex_init(&state->forks[i++], NULL);
	}
	state->philos_dead = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (init_state(&state, argc - 1, &argv[1]) == -1)
		return (EXIT_FAILURE);
	create_philos(&state);
	join_philos(&state);
	exit_philos(&state);
	return (EXIT_SUCCESS);
}
