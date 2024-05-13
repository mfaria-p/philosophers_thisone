/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:47:24 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/05/13 15:14:50 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thinking(t_philo *philo)
{
	print_state("is thinking", philo, philo->id);
	if (philo->id % 2 != 0)
		ft_usleep((philo->time_to_eat * 2) - philo->time_to_sleep);
	else
		ft_usleep(1);
}

void	sleeping(t_philo *philo)
{
	print_state("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	if (philo->num_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_state("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_state("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->l_fork);
	}
	print_state("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_state("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_gettime();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

//pthread_create(pthread_t *restrict thread,
//                         const pthread_attr_t *restrict attr,
//                         void *(*start_routine)(void *),
//                         void *restrict arg);
void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_death(philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
