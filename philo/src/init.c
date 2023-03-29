/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:34:45 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/03/29 02:21:10 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	ptr->s_time = current_time();
	ptr->lm_time = ptr->s_time;
}

void	init_mutex(pthread_mutex_t *forks, pthread_mutex_t *p_lck, char **argv)
{
	int	i;

	pthread_mutex_init(p_lck, NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
//	while (i < MAX_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
