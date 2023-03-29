/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:06:59 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/29 23:37:14 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
//	unsigned long		last_eat_time;
	int					left_locked;
	int					right_locked;
	int					i;

	left_locked = 0;
	right_locked = 0;
	philo_ptr = (t_philo *) vargp;
	i = 0;
//	usleep(philo_ptr->id * 100);
	while (((current_time() - philo_ptr->lm_time) < (unsigned long) philo_ptr->t_die) || !i)
//	while (1)
	{
		++i;
		print_log(philo_ptr, STATE_THINKING);
		if ((current_time() - philo_ptr->lm_time) >= (unsigned long) philo_ptr->t_die)
			break;
//		usleep((philo_ptr->t_die - philo_ptr->t_eat - philo_ptr->t_sleep) * 1000);
		if (philo_ptr->id % 2)
		{
			if (!pthread_mutex_lock(philo_ptr->left_fork))
			{
				if ((current_time() - philo_ptr->lm_time) >= (unsigned long) philo_ptr->t_die)
					break;
				left_locked = 1;
				print_log(philo_ptr, FORK_TAKEN);
				if (!pthread_mutex_lock(philo_ptr->right_fork))
				{
					right_locked = 1;
					print_log(philo_ptr, FORK_TAKEN);
//					last_eat_time = current_time();
					philo_ptr->lm_time = current_time();
					eat(philo_ptr);
					pthread_mutex_unlock(philo_ptr->right_fork);
					right_locked = 0;
					pthread_mutex_unlock(philo_ptr->left_fork);
					left_locked = 0;
				}
				else
				{
					pthread_mutex_unlock(philo_ptr->left_fork);
					left_locked = 0;
				}
			}
			else
				continue;
		}
		else
		{
			if (!pthread_mutex_lock(philo_ptr->right_fork))
			{
				if ((current_time() - philo_ptr->lm_time) >= (unsigned long) philo_ptr->t_die)
					break;
				right_locked = 1;
				print_log(philo_ptr, FORK_TAKEN);
				if (!pthread_mutex_lock(philo_ptr->left_fork))
				{
					left_locked = 1;
					print_log(philo_ptr, FORK_TAKEN);
//					last_eat_time = current_time();
					philo_ptr->lm_time = current_time();
					eat(philo_ptr);
					pthread_mutex_unlock(philo_ptr->left_fork);
					left_locked = 0;
					pthread_mutex_unlock(philo_ptr->right_fork);
					right_locked = 0;
				}
				else
				{
					pthread_mutex_unlock(philo_ptr->right_fork);
					right_locked = 0;
				}
			}
			else
				continue;
		}
		sleeping(philo_ptr);
		if ((current_time() - philo_ptr->lm_time) >= (unsigned long) philo_ptr->t_die)
			break;
/*		if ((current_time() - philo_ptr->lm_time) > (unsigned long) philo_ptr->t_die)
//		if ((current_time() - last_eat_time) > (long long unsigned) philo_ptr->t_die)
		{
			print_log(philo_ptr, STATE_DEAD);
			if (right_locked)
				pthread_mutex_unlock(philo_ptr->right_fork);
			pthread_mutex_destroy(philo_ptr->right_fork);
			if (left_locked)
				pthread_mutex_unlock(philo_ptr->left_fork);
			pthread_mutex_destroy(philo_ptr->left_fork);
			free(philo_ptr);
			break;
		}
*/
	}
	printf("%d\n", (current_time() - philo_ptr->lm_time) < (unsigned long) philo_ptr->t_die);
	print_log(philo_ptr, STATE_DEAD);
	if (right_locked)
		pthread_mutex_unlock(philo_ptr->right_fork);
	pthread_mutex_destroy(philo_ptr->right_fork);
	if (left_locked)
		pthread_mutex_unlock(philo_ptr->left_fork);
	pthread_mutex_destroy(philo_ptr->left_fork);
	free(philo_ptr);
	return (NULL);
}
