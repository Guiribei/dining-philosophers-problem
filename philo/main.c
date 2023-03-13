/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:14:02 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/13 17:13:37 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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
	pthread_mutex_destroy(&data->end_mutex);
	free(data);
	free(philos);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		loop_breaker;
	int		i;

	i = 0;
	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->end_mutex);
	loop_breaker = philo->data->is_over;
	pthread_mutex_unlock(&philo->data->end_mutex);
	while (i != philo->data->loops && !loop_breaker)
	{
		philo_eat(philo, 0);
		philo_sleep(philo);
		philo_think(philo);
		i++;
	}
	return (NULL);
}

static int	run_threads(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, routine, &philos[i]) != 0)
			return (error_handler("create thread", 1));
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (error_handler("join thread", 1));
		i++;
	}
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	*data;
	int		exitcode;

	if (argc < 5 || argc > 6)
		return (error_handler(USAGE, 1));
	if (check_wrong_input(argc, argv))
		return (1);
	exitcode = 0;
	data = init_data(argc, argv);
	if (!data)
		return (error_handler("faild to init data", 1));
	init_extra_mutexes(data);
	philos = init_philos(data, argv, 0);
	if (!philos)
		return (error_handler("faild to init philos", 1));
	exitcode = run_threads(data, philos);
	clean_and_quit(data, philos);
	return (exitcode);
}
