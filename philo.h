#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int			num_philos;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
}				t_data;

//utils.c
int			ft_atoi(const char *str);
long long	get_time(void);

#endif
