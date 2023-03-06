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

typedef struct s_data
{
	time_t			start_time;
	int				num_philos;
	pthread_mutex_t	printf_mutex;
}t_data;

typedef struct s_philo
{
	unsigned int	id;		
	t_data			*data;
	int				right_fork;
	int				left_fork;
}t_philo;

int		error_handler(char *str, int exit_code);
int		check_wrong_input(int argc, char **argv);
int		philo_atoi(char *str);
t_data	*init_data(int argc, char **argv);
t_philo	*init_philos(t_data *data, int *forks);
time_t	get_time_in_ms(void);

#endif