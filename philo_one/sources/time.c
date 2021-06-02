/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 02:24:31 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/02 02:28:53 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned int	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned int ms)
{
	unsigned int	start;

	start = gettime();
	while (gettime() - start < ms)
		usleep(400);
}
