/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:23:46 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/02/26 07:48:41 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct  s_philo
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
} t_philo;

/*philosopher.c*/

/*init.c*/
int	init_philo(char *argv[], t_philo *philo);

/*ft_atoi.c*/
int	ft_atoi(char *str);

#endif
