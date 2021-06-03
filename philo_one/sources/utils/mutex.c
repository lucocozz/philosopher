/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 00:31:26 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/03 00:34:44 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	read_mutex(t_mutex *mutex)
{
	int	value;

	pthread_mutex_lock(&mutex->lock);
	value = mutex->value;
	pthread_mutex_unlock(&mutex->lock);
	return (value);
}

void	write_mutex(t_mutex *mutex, int value)
{
	pthread_mutex_lock(&mutex->lock);
	mutex->value = value;
	pthread_mutex_unlock(&mutex->lock);
}
