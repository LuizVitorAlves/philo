/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalves-d <lalves-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:52:56 by lalves-d          #+#    #+#             */
/*   Updated: 2025/06/27 09:37:24 by lalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simulation_has_ended(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_lock);
	if (philo->data->simulation_should_end)
	{
		pthread_mutex_unlock(&philo->data->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->sim_lock);
	return (0);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a right fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->sim_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->sim_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_has_ended(philo))
	{
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
