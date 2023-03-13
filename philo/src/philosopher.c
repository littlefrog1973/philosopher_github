/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:16:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/02/26 08:22:07 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

int	count = 0;
pthread_mutex_t	mutex;

void	*increment(void *arg)
{
	pthread_mutex_lock(&mutex);
	count++;
	printf("Thread %ld incremented count to %d\n", (long) arg, count);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	struct timeval time;

	if (argc != 5)
		return (1);
	init_philo(argv, &philo);
	printf("n_philo = %d\n", philo.n_philo);
	gettimeofday(&time, NULL);
	printf("time = %ld\n", time.tv_sec);
	printf("utime = %ld\n", time.tv_usec);
	return (0);
}
