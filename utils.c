/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalves-d <lalves-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:18:27 by lalves-d          #+#    #+#             */
/*   Updated: 2025/06/26 21:56:57 by lalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)result);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, const char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->sim_lock);
	if (!philo->data->simulation_should_end)
    {
        timestamp = get_time() - philo->data->start_time;
        printf("%lld %d %s\n", timestamp, philo->id, status);
    }
	pthread_mutex_unlock(&philo->data->sim_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}
