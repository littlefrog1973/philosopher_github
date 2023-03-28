/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 05:50:41 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/24 06:13:41 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long unsigned	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

void	eat(t_philo *philo_ptr)
{
	print_log(philo_ptr, STATE_EATING);
	usleep(philo_ptr->t_eat * 1000);
}

void	sleeping(t_philo *philo_ptr)
{
	print_log(philo_ptr, STATE_SLEEPING);
	usleep(philo_ptr->t_sleep * 1000);
}

void	*philosopher(void *vargp)
{
	t_philo				*philo_ptr;
	long long unsigned	last_eat_time;

	philo_ptr = (t_philo *) vargp;
	while (1)
	{
		print_log(philo_ptr, STATE_THINKING);
		usleep(philo_ptr->id * 100);
		if (!pthread_mutex_lock(philo_ptr->left_fork))
		{
			print_log(philo_ptr, FORK_TAKEN);
			if (!pthread_mutex_lock(philo_ptr->right_fork))
			{
				print_log(philo_ptr, FORK_TAKEN);
				last_eat_time = current_time();
				eat(philo_ptr);
				pthread_mutex_unlock(philo_ptr->right_fork);
				pthread_mutex_unlock(philo_ptr->left_fork);
			}
			else
				pthread_mutex_unlock(philo_ptr->left_fork);
		}
		sleeping(philo_ptr);
		if ((current_time() - last_eat_time) > (long long unsigned) philo_ptr->t_die)
		{
			print_log(philo_ptr, STATE_DEAD);
			free(philo_ptr);
			break;
		}
	}
	return (NULL);
}
