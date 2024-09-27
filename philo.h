/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:05:52 by dgermano          #+#    #+#             */
/*   Updated: 2024/09/26 08:44:48 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX 2147483647

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				opt;
	int				meal;
	int				*ctrl;
	int				id_philo;
	long			time_morte;
	long			time_comer;
	long			time_dormir;
	long			*start;
	pthread_mutex_t	*garfo_esquerdo;
	pthread_mutex_t	*garfo_directo;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*ctrl_mutex;
}					t_philo;

typedef struct s_manager
{
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t	control_mutex;
	int				n_philo;
	int				control;
	int				i;
	long			start;
}					t_manager;

/*typedef struct s_philo
{
	pthread_mutex_t		*garfo_esquerdo;
	int		left;
	pthread_mutex_t		*garfo_directo;
	pthread_mutex_t		*printer;
	int		rigth;
	long			*start;
	long			time_morte;
	long			time_dormir;
	long			time_comer;
	int			id_philo;
	int			opt;
	int			eat;
	int			*ctrl;
}	t_philo;*/

unsigned int		ft_atoui(const char *nptr);
long long			cur_time(void);
void				*live_philo(void *arg);
int					printer(long time, t_philo *philo, const char *str);
#endif
