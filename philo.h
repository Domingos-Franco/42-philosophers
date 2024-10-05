/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:05:52 by dgermano          #+#    #+#             */
/*   Updated: 2024/10/05 10:15:18 by dgermano         ###   ########.fr       */
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
	int				eat;
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
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t	control_mutex;
	int				n_philo;
	int				control;
	int				i;
	int				a;
	long			start;
}					t_manager;

unsigned int		ft_atoui(const char *nptr);
int					printer(long time, t_philo *philo, const char *str);
long long			cur_time(void);
void				*live_philo(void *arg);
void				supervisor_launcher(t_manager *man);
#endif
