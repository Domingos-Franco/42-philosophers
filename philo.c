/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:01:30 by dgermano          #+#    #+#             */
/*   Updated: 2024/09/27 18:34:29 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_thread(t_manager *man, char **argv)
{
	int	i;

	i = -1;
	while (++i < man->n_philo)
		pthread_mutex_init(&man->forks[i], NULL);
	i = 0;
	if (*man->philo[i].start)
		man->philo[i].start[0] = cur_time();
	while (i < man->n_philo)
	{
		man->philo[i].id_philo = i + 1;
		man->philo[i].time_morte = atol(argv[2]);
		man->philo[i].time_comer = atol(argv[3]);
		man->philo[i].time_dormir = atol(argv[4]);
		if (argv[5])
			man->philo[i].opt = atoi(argv[5]);
		man->philo[i].garfo_esquerdo = &man->forks[i];
		man->philo[i].garfo_directo = &man->forks[(i + 1) % man->n_philo];
		pthread_create(&man->threads[i], NULL, live_philo, &man->philo[i]);
		i++;
	}
}

static void	exit_philo(t_manager *man)
{
	int	i;

	man->i = -1;
	while (++i < man->n_philo)
		pthread_join(man->threads[i], NULL);
	man->i = -1;
	while (++man->i < man->n_philo)
		pthread_mutex_destroy(&man->forks[i]);
	pthread_mutex_destroy(man->philo->printer);
	pthread_mutex_destroy(man->philo->ctrl_mutex);
	free(man->threads);
	free(man->philo);
	free(man->forks);
}

static int	init_philo(t_manager *man)
{
	if (!man->philo || !man->threads || !man->forks)
		return (1);
	man->i = -1;
	man->control = 0;
	man->start = cur_time();
	pthread_mutex_init(&man->printer, NULL);
	pthread_mutex_init(&man->control_mutex, NULL);
	while (++man->i < man->n_philo)
	{
		man->philo[man->i].printer = &man->printer;
		man->philo[man->i].start = &man->start;
		man->philo[man->i].ctrl = &man->control;
		man->philo[man->i].ctrl_mutex = &man->control_mutex;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_manager	man;

	if (argc > 1)
	{
		man.n_philo = atoi(argv[1]);
		man.philo = malloc(sizeof(t_philo) * man.n_philo);
		man.threads = malloc(sizeof(pthread_t) * man.n_philo);
		man.forks = malloc(sizeof(pthread_mutex_t) * man.n_philo);
		init_philo(&man);
		launch_thread(&man, argv);
		exit_philo(&man);
	}
	return (0);
}
