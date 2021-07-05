/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:29:39 by lucocozz          #+#    #+#             */
/*   Updated: 2021/07/05 21:23:56 by lucocozz         ###   ########.fr       */
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
		state->philos[i] = (t_philo){.nb = i, .nb_eat = 0,
			.last_meal = gettime()};
		pthread_mutex_init(&state->forks[i++], NULL);
	}
	pthread_mutex_init(&state->output.lock, NULL);
	pthread_mutex_init(&state->philos_dead.lock, NULL);
	write_mutex(&state->philos_dead, 0);
	write_mutex(&state->output, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_state	state;
	t_args	*args;

	if (init_state(&state, argc - 1, &argv[1]) == -1)
		return (EXIT_FAILURE);
	args = create_philos(&state);
	join_philos(&state);
	exit_philos(&state, args);
	return (EXIT_SUCCESS);
}
