/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:23:46 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/23 08:59:10 by sdeeyien         ###   ########.fr       */
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
	int				id;
//	int				state;
	int				last_meal;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
}	t_philo;

typedef struct s_philo_prop
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int t_sleep;
}	t_philo_prop;

#define	MAX_PHILO		100
#define	STATE_THINKING	0
#define	STATE_EATING	1
#define	STATE_SLEEPING	2
#define	STATE_DEAD		3
#define	FORK_TAKEN		4


/*philosopher.c*/

/*init.c*/
int	init_philo_prop(char *argv[], t_philo_prop *philo);

/*ft_atoi.c*/
int	ft_atoi(char *str);

/* thread.c */
void	*thread(void *vargp);

#endif
