/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_over.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:36:41 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/14 23:28:29 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_over(t_data *data)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&data->end_mutex);
	flag = data->is_over;
	pthread_mutex_unlock(&data->end_mutex);
	return (flag);
}

void	change_is_over(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	philo->data->is_over = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
}

int	check_end(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philo->data->end_mutex);
	flag = philo->data->is_over;
	pthread_mutex_unlock(&philo->data->end_mutex);
	if (flag)
		return (flag);
	return (0);
}

int	check_meals(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (i != philo->to_take)
	{
		philo->taken++;
		pthread_mutex_unlock(&philo->data->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (1);
}

int	meals_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->taken == philo->to_take)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (0);
}
