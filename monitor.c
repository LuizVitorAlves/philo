/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalves-d <lalves-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:49:25 by lalves-d          #+#    #+#             */
/*   Updated: 2025/07/09 08:59:07 by lalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_philos_have_eaten;

	if (data->num_meals_limit == -1)
		return (0);
	all_philos_have_eaten = 1;
	pthread_mutex_lock(&data->sim_lock);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->num_meals_limit)
		{
			all_philos_have_eaten = 0;
			break ;
		}
		i++;
	}
	if (all_philos_have_eaten)
		data->simulation_should_end = 1;
	pthread_mutex_unlock(&data->sim_lock);
	return (all_philos_have_eaten);
}

static int	check_death(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->sim_lock);
	if (!philo->data->simulation_should_end
		&& (get_time() - philo->last_meal_time) > philo->data->time_to_die)
	{
		philo->data->simulation_should_end = 1;
		timestamp = get_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %d %s\n", timestamp, philo->id, "died");
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->sim_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
