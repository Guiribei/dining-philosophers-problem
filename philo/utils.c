/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:31:05 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/14 14:48:52 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(char *str, int exit_code)
{
	printf("philo: %s\n", str);
	return (exit_code);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_extra_mutexes(t_data *data)
{
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
}

void	delay_start(t_philo *philo)
{
	time_t	wait_time;

	wait_time = 0;
	pthread_mutex_lock(&philo->data->time_mutex);
	wait_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->time_mutex);
	while (get_time_in_ms() < wait_time)
		continue ;
}

void	clean_and_quit(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (data->forks_mutex != NULL)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks_mutex[i]);
			i++;
		}
		free(data->forks_mutex);
		data->forks_mutex = NULL;
	}
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	free(data);
	free(philos);
}
