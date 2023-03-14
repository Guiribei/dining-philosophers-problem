/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:40:23 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/14 22:09:21 by guribeir         ###   ########.fr       */
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

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->is_over = 0;
	data->num_philos = philo_atoi(argv[1]);
	data->start_time = (get_time_in_ms()) + (data->num_philos * 20);
	data->forks_mutex = init_forks(data);
	if (!data->forks_mutex)
		return (NULL);
	return (data);
}

static void	init_philo_vars(t_data *data, char **argv, int i, t_philo *philos)
{
	philos[i].last_meal = 0;
	philos[i].data = data;
	philos[i].taken = 0;
	philos[i].id = i + 1;
	philos[i].time_die = philo_atoi(argv[2]);
	philos[i].time_eat = philo_atoi(argv[3]);
	philos[i].time_sleep = philo_atoi(argv[4]);
}

t_philo	*init_philos(t_data *data, char **argv, int i, int argc)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	while (i < data->num_philos)
	{
		if (argc == 6)
			philos[i].to_take = philo_atoi(argv[5]);
		else
			philos[i].to_take = -1;
		init_philo_vars(data, argv, i, philos);
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
