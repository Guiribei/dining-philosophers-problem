/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:40:23 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/05 22:58:02 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time_in_ms();
	data->num_philos = philo_atoi(argv[1]);
	return (data);
}

t_philo	*init_philos(t_data *data, int *forks)
{
	t_philo	*philos;
	int		i;

	i = 0;
	(void)forks;
	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return NULL;
	pthread_mutex_init(&data->printf_mutex, NULL);
	while(i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		//philos[i].right_fork = forks[i];
		// if (i == (data->num_philos - 1))
		// 	philos[i].left_fork = forks[0];
		// else
		// 	philos[i].left_fork = forks[i + 1];
		i++;
	}
	return (philos);
}