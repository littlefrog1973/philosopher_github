/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:34:45 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/02/26 07:50:38 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philo(char *argv[], t_philo *philo)
{
	(*philo).n_philo = ft_atoi(argv[1]);
	(*philo).t_die = ft_atoi(argv[2]);
	(*philo).t_eat = ft_atoi(argv[3]);
	(*philo).t_sleep = ft_atoi(argv[4]);
	return (1);
}
