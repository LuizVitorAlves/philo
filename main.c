/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalves-d <lalves-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:18:07 by lalves-d          #+#    #+#             */
/*   Updated: 2025/06/19 16:18:08 by lalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Use: ./philo num_filos morrer comer dormir [num_refeicoes]\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Erro: Falha na inicialização dos dados.\n");
		return (1);
	}
	printf("Inicialização completa! %d filósofos e %d garfos prontos.\n",
		data.num_philos, data.num_philos);
	printf("Nenhuma simulação iniciada ainda. Apenas limpando os recursos.\n");
	cleanup(&data);
	return (0);
}
