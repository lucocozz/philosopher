/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:48:28 by lucocozz          #+#    #+#             */
/*   Updated: 2021/05/25 22:27:48 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_isnumber(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '-' && !(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
