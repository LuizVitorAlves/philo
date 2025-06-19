#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // Adicionado para usar pthread_mutex_t
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// Forward declaration para evitar dependência circular
struct s_data;

typedef struct s_philo
{
	int				id;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_meals_limit;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_data;

// init.c
int			init_data(t_data *data, int argc, char **argv);

// utils.c
int			ft_atoi(const char *str);
long long	get_time(void);

#endif