/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:46:00 by guribeir          #+#    #+#             */
/*   Updated: 2023/03/05 15:38:42 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	philo_atoi(char *str)
{
	long long int			nb;
	int						i;

	i = 0;
	nb = 0;
	if (ft_strlen(str) > 18)
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return ((int)nb);
}

static int	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_wrong_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!is_only_digit(argv[i]))
			return (error_handler("Wrong entry", 1));
		nb = philo_atoi(argv[i]);
		if (i == 1 && nb <= 0)
			return (error_handler("Incorrect number os philos", 1));
		if (i != 1 && nb == -1)
			return (error_handler("Invalid entry", 1));
		i++;
	}
	return (0);
}
