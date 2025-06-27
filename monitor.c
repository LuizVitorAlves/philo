/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalves-d <lalves-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:49:25 by lalves-d          #+#    #+#             */
/*   Updated: 2025/06/27 09:08:00 by lalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_data *data)
{
	int	i;
	int	philos_finished_eating;

	if (data->num_meals_limit == -1)
		return (0);
	i = 0;
	philos_finished_eating = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->sim_lock);
		if (data->philos[i].meals_eaten >= data->num_meals_limit)
			philos_finished_eating++;
		pthread_mutex_unlock(&data->sim_lock);
		i++;
	}
	if (philos_finished_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->sim_lock);
		data->simulation_should_end = 1;
		pthread_mutex_unlock(&data->sim_lock);
		return (1);
	}
	return (0);
}

static int	check_death(t_philo *philo)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->sim_lock);
	time_since_last_meal = get_time() - philo->last_meal_time;
	if (time_since_last_meal > philo->data->time_to_die)
	{
		philo->data->simulation_should_end = 1;
		pthread_mutex_unlock(&philo->data->sim_lock);
		print_status(philo, "died");
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
