#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5)
	{
		printf("Erro: Número incorreto de argumentos.\n");
		printf("Uso: ./philo num_filosofos tempo_para_morrer tempo_para_comer tempo_para_dormir\n");
		return (1);
	}
	data.num_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);

	printf("--- Configuração da Simulação ---\n");
	printf("Número de filósofos: %d\n", data.num_philos);
	printf("Tempo para morrer: %lld ms\n", data.time_to_die);
	printf("Tempo para comer: %lld ms\n", data.time_to_eat);
	printf("Tempo para dormir: %lld ms\n", data.time_to_sleep);
	printf("----------------------------------\n");
	printf("Tempo atual em ms: %lld\n", get_time());
	return (0);
}
