/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks_forks_meals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:47:04 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/14 16:17:02 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_left_fork(t_philo *philo, time_t time)
{
	pthread_mutex_lock(philo->l_fork);
	if (check_end(philo))
		return ;
	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	if (check_end(philo))
		return ;
}

void	get_right_fork(t_philo *philo, time_t time)
{
	pthread_mutex_lock(philo->r_fork);
	if (check_end(philo))
		return ;
	time = (get_time_in_ms()) - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld Philosopher %u has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	if (check_end(philo))
		return ;
}

void	get_last_meal(t_philo *philos, time_t *time, time_t *meal, int i)
{
	*time = (get_time_in_ms()) - philos->data->start_time;
	pthread_mutex_lock(&philos->data->meal_mutex);
	*meal = philos[i].last_meal;
	pthread_mutex_unlock(&philos->data->meal_mutex);
}

void	get_printf(t_philo *philos, time_t time)
{
	pthread_mutex_lock(&philos->data->printf_mutex);
	printf("%ld Philosopher %u died\n", time, philos->id);
	pthread_mutex_unlock(&philos->data->printf_mutex);
}
