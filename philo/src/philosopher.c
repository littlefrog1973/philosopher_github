/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:16:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/23 15:39:14 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher(void *vargp);

int	check_argv(int argc, char *argv[])
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
		|| ft_atoi(argv[4]) < 1 || argc != 5)
		return (0);
	return (1);
}

int	init_philo_prop(char *argv[], t_philo_prop *philo)
{
	philo->n_philo = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (philo->n_philo < 1 || philo->t_die < 1 || philo->t_eat < 1
		|| philo->t_sleep < 1)
			return (0);
	return (1);
}

void	philo_copy2(t_philo *ptr, char *argv[], int i, pthread_mutex_t *forks)
{
	ptr->id = i;
	ptr->t_die = ft_atoi(argv[2]);
	ptr->t_eat = ft_atoi(argv[3]);
	ptr->t_sleep = ft_atoi(argv[4]);
	ptr->left_fork = &forks[i - 1];
	ptr->right_fork = &forks[i % ft_atoi(argv[1])];
}

void	philo_copy(t_philo *ptr, t_philo_prop philo_prop, int i, pthread_mutex_t *forks)
{
	ptr->id = i;
	ptr->t_die = philo_prop.t_die;
	ptr->t_eat = philo_prop.t_eat;
	ptr->t_sleep = philo_prop.t_sleep;
	ptr->left_fork = &forks[i - 1];
	ptr->right_fork = &forks[i % philo_prop.n_philo];
}
void	print_log(t_philo *philo, int state)
{
	struct timeval		time;
	long long unsigned	millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
	pthread_mutex_lock(philo->print_lock);
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
	pthread_mutex_unlock(philo->print_lock);
}

void	init_thread_mutex(pthread_mutex_t *forks, pthread_mutex_t *print_lock, char **argv)
{
	int	i;

	pthread_mutex_init(print_lock, NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
//	while (i < MAX_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int				i;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	t_philo			*ptr;
	pthread_mutex_t	print_lock;

	if(check_argv(argc, argv))
	{
		init_thread_mutex(forks, &print_lock, argv);
		i = 0;
		while (++i <= ft_atoi(argv[1]))
		{
			ptr = malloc(sizeof(t_philo));
			if (ptr)
			{
				philo_copy2(ptr, argv, i, forks);
				ptr->print_lock = &print_lock;
				pthread_create(&philo[i - 1], NULL, philosopher, ptr);
			}
		}
		while (--i >= 1)
		{
			pthread_join(philo[i - 1], NULL);
			pthread_mutex_destroy(&forks[i - 1]);
		}
		pthread_mutex_destroy(&print_lock);
	}
	return (0);
}

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
