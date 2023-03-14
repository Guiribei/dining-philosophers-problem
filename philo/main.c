/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:14:02 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/15 00:16:55 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*solo_philo(t_philo *philo)
{
	time_t	time;

	delay_start(philo);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = (get_time_in_ms()) - philo->data->start_time;
	printf("%ld Philosopher %u has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	usleep(philo->time_die * 1000);
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = (get_time_in_ms()) - philo->data->start_time;
	printf("%ld Philosopher %u died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

static void	*supervisor_routine(void *arg)
{
	t_philo	*philos;
	time_t	time;
	int		i;
	time_t	meal;

	philos = (t_philo *)arg;
	delay_start(philos);
	while (1)
	{
		i = 0;
		while (i < philos->data->num_philos)
		{
			get_last_meal(philos, &time, &meal, i);
			if (meals_done(philos))
				return (NULL);
			if (time - meal >= philos[i].time_die)
			{
				change_is_over(philos);
				get_printf(philos, time);
				return (NULL);
			}
			usleep(100);
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->time_die == 0)
		return (NULL);
	if (philo->data->num_philos == 1)
		return (solo_philo(philo));
	delay_start(philo);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!check_meals(philo, i))
	{
		if (get_is_over(philo->data))
			return (NULL);
		philo_eat(philo, 0);
		philo_sleep(philo);
		philo_think(philo);
		i++;
	}
	return (NULL);
}

static int	run_threads(t_data *data, t_philo *philos, int i, int j)
{
	pthread_t	*threads;
	pthread_t	supervisor;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (data->num_philos > 1)
		if (pthread_create(&supervisor, NULL, supervisor_routine,
				philos) != 0)
			return (error_handler("create thread", 1));
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, routine, &philos[i]) != 0)
			return (error_handler("create thread", 1));
		i++;
	}
	while (j < data->num_philos)
	{
		if (pthread_join(threads[j], NULL) != 0)
			return (error_handler("join thread", 1));
		j++;
	}
	if (data->num_philos > 1)
		if (pthread_join(supervisor, NULL) != 0)
			return (error_handler("join thread", 1));
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
	data = init_data(argv);
	if (!data)
		return (error_handler("faild to init data", 1));
	init_extra_mutexes(data);
	philos = init_philos(data, argv, 0, argc);
	if (!philos)
		return (error_handler("faild to init philos", 1));
	exitcode = run_threads(data, philos, 0, 0);
	clean_and_quit(data, philos);
	return (exitcode);
}
