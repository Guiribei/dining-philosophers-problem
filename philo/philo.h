/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:37:54 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/05 22:26:43 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE "usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"

typedef struct s_data
{
	time_t			start_time;
	int				num_philos;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	*forks_mutex;
}t_data;

typedef struct s_philo
{
	unsigned int	id;		
	int				fork[2];
	t_data			*data;
}t_philo;

int		error_handler(char *str, int exit_code);
int		check_wrong_input(int argc, char **argv);
int		philo_atoi(char *str);
t_data	*init_data(int argc, char **argv);
t_philo	*init_philos(t_data *data);
time_t	get_time_in_ms(void);

#endif