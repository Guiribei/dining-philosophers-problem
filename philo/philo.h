/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:37:54 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/14 22:38:22 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

# define USAGE "usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"

typedef struct s_data
{
	time_t			start_time;
	int				num_philos;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	time_mutex;
	int				is_over;
}t_data;

typedef struct s_philo
{
	pthread_t		thread;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	time_t			last_meal;
	unsigned int	id;
	int				taken;
	int				to_take;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}t_philo;

int		check_end(t_philo *philo);
int		check_meals(t_philo *philo, int i);
int		check_wrong_input(int argc, char **argv);
int		error_handler(char *str, int exit_code);
int		get_is_over(t_data *data);
int		meals_done(t_philo *philo);
int		philo_atoi(char *str);
t_data	*init_data(char **argv);
t_philo	*init_philos(t_data *data, char **argv, int i, int argc);
time_t	get_time_in_ms(void);
void	change_is_over(t_philo *philo);
void	delay_start(t_philo *philo);
void	philo_eat(t_philo *philo, time_t time);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	init_extra_mutexes(t_data *data);
void	clean_and_quit(t_data *data, t_philo *philos);
void	get_right_fork(t_philo *philo, time_t time);
void	get_left_fork(t_philo *philo, time_t time);
void	get_printf(t_philo *philos, time_t time);
void	get_last_meal(t_philo *philos, time_t *time, time_t *meal, int i);

#endif