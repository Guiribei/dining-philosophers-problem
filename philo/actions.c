/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:00:06 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/07 19:45:18 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	new_sleep(t_philo *philo, time_t amount)
{
	time_t	time;
	time_t	total;

	time = get_time_in_ms();
	total = time + amount;
	while (time < total)
	{
		usleep(100);
		time = get_time_in_ms();
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->is_over)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_mutex);
	}
}

void	philo_eat(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(philo->right_fork);
	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(philo->left_fork);
	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	time = (get_time_in_ms()) - philo->data->start_time;
	philo->last_meal = time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	new_sleep(philo, philo->time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	time_t	time;

	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	new_sleep(philo, philo->time_sleep);
}

void	philo_think(t_philo *philo)
{
	time_t	time;

	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	new_sleep(philo, (philo->time_die - (get_time_in_ms() - philo->last_meal) - philo->time_eat) / 2);
}
