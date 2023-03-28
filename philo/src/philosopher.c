/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:16:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/29 00:44:19 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_log(t_philo *philo, int state)
{
	struct timeval		time;
	unsigned long		millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000L) + (time.tv_usec / 1000L) - philo->s_time;
	pthread_mutex_lock(philo->p_lck);
	if (state == FORK_TAKEN)
		printf("%5lu %3d has taken a fork\n", millisec, philo->id);
	if (state == STATE_THINKING)
		printf("%5lu %3d is thinking\n", millisec, philo->id);
	if (state == STATE_EATING)
		printf("%5lu %3d is eating\n", millisec, philo->id);
	if (state == STATE_SLEEPING)
		printf("%5lu %3d is sleeping\n", millisec, philo->id);
	if (state == STATE_DEAD)
		printf("%5lu %3d died\n", millisec, philo->id);
	pthread_mutex_unlock(philo->p_lck);
}

int	main(int argc, char *argv[])
{
	int				i;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	t_philo			*ptr;
	pthread_mutex_t	p_lck;

	if(check_argv(argc, argv))
	{
		init_mutex(forks, &p_lck, argv);
		i = 0;
		while (++i <= ft_atoi(argv[1]))
		{
			ptr = malloc(sizeof(t_philo));
			if (ptr)
			{
				ptr->p_lck = &p_lck;
				philo_copy2(ptr, argv, i, forks);
				pthread_create(&philo[i - 1], NULL, philosopher, ptr);
			}
		}
		while (--i >= 1)
		{
			pthread_join(philo[i - 1], NULL);
			pthread_mutex_destroy(&forks[i - 1]);
		}
		pthread_mutex_destroy(&p_lck);
	}
	return (0);
}
