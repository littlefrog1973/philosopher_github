/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:16:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/24 06:10:00 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_log(t_philo *philo, int state)
{
	struct timeval		time;
	long long unsigned	millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
	pthread_mutex_lock(philo->p_lck);
	if (state == FORK_TAKEN)
		printf("%llu %d has taken a fork\n", millisec, philo->id);
	if (state == STATE_THINKING)
		printf("%llu %d is thinking\n", millisec, philo->id);
	if (state == STATE_EATING)
		printf("%llu %d is eating\n", millisec, philo->id);
	if (state == STATE_SLEEPING)
		printf("%llu %d is sleeping\n", millisec, philo->id);
	if (state == STATE_DEAD)
		printf("%llu %d died\n", millisec, philo->id);
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
				philo_copy2(ptr, argv, i, forks);
				ptr->p_lck = &p_lck;
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
