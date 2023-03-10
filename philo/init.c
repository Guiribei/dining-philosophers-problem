/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:40:23 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/13 17:11:16 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;
	int				j;

	forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&forks[j]);
				j++;
			}
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (argc == 6)
		data->loops = philo_atoi(argv[5]);
	else
		data->loops = -1;
	data->is_over = 0;
	data->start_time = get_time_in_ms();
	data->num_philos = philo_atoi(argv[1]);
	data->forks_mutex = init_forks(data);
	if (!data->forks_mutex)
		return (NULL);
	return (data);
}

t_philo	*init_philos(t_data *data, char **argv, int i)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	while (i < data->num_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].time_die = philo_atoi(argv[2]);
		philos[i].time_eat = philo_atoi(argv[3]);
		philos[i].time_sleep = philo_atoi(argv[4]);
		if (philos[i].id % 2 == 1)
		{
			philos[i].r_fork = &data->forks_mutex[i];
			philos[i].l_fork = &data->forks_mutex[(i + 1) % data->num_philos];
		}
		else
		{
			philos[i].l_fork = &data->forks_mutex[i];
			philos[i].r_fork = &data->forks_mutex[(i + 1) % data->num_philos];
		}
		i++;
	}
	return (philos);
}

void	init_extra_mutexes(t_data *data)
{
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
}
