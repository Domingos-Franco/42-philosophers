/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:01:30 by dgermano          #+#    #+#             */
/*   Updated: 2024/10/05 10:19:34 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int check_manager_initialization(t_manager *man) {
    if (man == NULL) {
        return 1;
    }

    if (man->philo == NULL || man->threads == NULL || man->forks == NULL) {
        return 1;
    }

    for (int i = 0; i < man->n_philo; i++) {
        if (man->philo[i].ctrl == NULL || man->philo[i].start == NULL || 
            man->philo[i].garfo_esquerdo == NULL || man->philo[i].garfo_directo == NULL || 
            man->philo[i].printer == NULL || man->philo[i].ctrl_mutex == NULL) {
            return 1;
        }
    }

    return 0;
}
void	*monitor_life(void *argment)
{
	t_manager	*man = NULL;
	int			i;
	int			in;
	int			eat_done;

	
	man = (t_manager *)argment;
	eat_done = 0;
	in = -1;
	i = 0;
	if(check_manager_initialization(man) == 1)
		printf("\033[1m\033[31mHAS A NON-INITIALIZED VALUE\033[0m\n");
	while (++in < man->n_philo)
	{
		i = 0;
		while (i < man->n_philo)
		{
			if (man->philo[i].eat == man->philo[i].opt)
				eat_done++;
			i++;
		}
		if (eat_done == man->n_philo)
		{
			*(man->philo[in].ctrl) = 1;
			break ;
		}
		if (in == man->n_philo)
			in = 0;
	}
	return (NULL);
}
void	supervisor_launcher(t_manager *man)
{
	int	i;

	i = 0;
	while (i < man->n_philo)
	{
		if (!((i + 1) % 2))
			pthread_create(&man->threads[i], NULL, live_philo, &man->philo[i]);
		i++;
	}
	usleep(man->philo[0].time_comer * 1000);
	i = 0;
	while (i < man->n_philo)
	{
		if (((i + 1) % 2))
			pthread_create(&man->threads[i], NULL, live_philo, &man->philo[i]);
		i++;
	}
	pthread_create(&man->monitor, NULL, monitor_life, &man);
}
static void	launch_thread(t_manager *man, char **argv)
{
	int	i;

	i = 0;
	man->philo[i].start[i] = cur_time();
	while (i < man->n_philo)
	{
		man->philo[i].eat = 0;
		man->philo[i].id_philo = i + 1;
		man->philo[i].time_morte = atol(argv[2]);
		man->philo[i].time_comer = atol(argv[3]);
		man->philo[i].time_dormir = atol(argv[4]);
		if (argv[5] != NULL)
			man->philo[i].opt = atoi(argv[5]);
		else
			man->philo[i].opt = MAX;
		man->philo[i].garfo_esquerdo = &man->forks[i];
		man->philo[i].garfo_directo = &man->forks[(i + 1) % man->n_philo];
		i++;
	}
	supervisor_launcher(man);
}

static void	exit_philo(t_manager *man)
{
	man->i = -1;
	while (++man->i < man->n_philo)
		pthread_join(man->threads[man->i], NULL);
	pthread_join(man->monitor, NULL);
	man->i = -1;
	while (++man->i < man->n_philo)
		pthread_mutex_destroy(&man->forks[man->i]);
	pthread_mutex_destroy(&man->printer);
	pthread_mutex_destroy(&man->control_mutex);
	free(man->threads);
	free(man->philo);
	free(man->forks);
}
static int	init_philo(t_manager *man)
{
	int	i;

	if (!man->philo || !man->threads || !man->forks)
		return (1);
	man->control = 0;
	man->start = cur_time();
	i = -1;
	while (++i < man->n_philo)
		pthread_mutex_init(&man->forks[i], NULL);
	pthread_mutex_init(&man->printer, NULL);
	pthread_mutex_init(&man->control_mutex, NULL);
	i = -1;
	while (++i < man->n_philo)
	{
		man->philo[i].printer = &man->printer;
		man->philo[i].start = &man->start;
		man->philo[i].ctrl = &man->control;
		man->philo[i].ctrl_mutex = &man->control_mutex;
	}
	return (0);
}
static void	init_man(t_manager *man)
{
	man->n_philo = 0;
	man->control = 0;
	man->i = 0;
	man->start = 0;
	return ;
}
int	main(int argc, char **argv)
{
	t_manager	man;

	init_man(&man);
	if (argc > 4)
	{
		man.n_philo = atoi(argv[1]);
		man.philo = malloc(sizeof(t_philo) * man.n_philo);
		man.threads = malloc(sizeof(pthread_t) * man.n_philo);
		man.forks = malloc(sizeof(pthread_mutex_t) * man.n_philo);
		if (!man.philo || !man.threads || !man.forks)
			return (1);
		init_philo(&man);
		launch_thread(&man, argv);
		exit_philo(&man);
	}
	else
	{
		printf("Usage: %s n_philo time_to_eat time_to_sleep time_to_think\n",
			argv[0]);
		return (1);
	}
	return (0);
}
