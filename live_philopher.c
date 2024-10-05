/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_philopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:45:58 by dgermano          #+#    #+#             */
/*   Updated: 2024/10/05 09:53:52 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	cur_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec) * 1000 + tv.tv_usec / 1000);
}

int printer(long time, t_philo *philo, const char *str)
{
	int current_control;

	pthread_mutex_lock(philo->ctrl_mutex);
	current_control = *(philo->ctrl);
	pthread_mutex_unlock(philo->ctrl_mutex);
	if (current_control != 1)
	{
		pthread_mutex_lock(philo->printer);
		printf("[%ld]-%d %s\n", time, philo->id_philo, str);
		pthread_mutex_unlock(philo->printer);
	}
	return (0);
}


static void	ft_smart_usleep(t_philo *phil, long time)
{
	while (time)
	{
		if ((cur_time() - *phil->start) > phil->time_morte)
		{
			printer(cur_time() - *phil->start, phil, "is dead");
			*(phil->ctrl) = 1;
			break ;
		}
		usleep(10 * 1000);
		time -= 10;
	}
}

static int phil_status(t_philo *philo, long time_increase) {
    pthread_mutex_lock(philo->ctrl_mutex);
    if (*(philo->ctrl) == 1) {
        pthread_mutex_unlock(philo->ctrl_mutex);
        return 1;
    }
    pthread_mutex_unlock(philo->ctrl_mutex);
    
    printer(cur_time() - *philo->start, philo, "is thinking");
    pthread_mutex_lock(philo->garfo_esquerdo);
    printer(cur_time() - *philo->start, philo, "has taken a fork");
    if(philo->garfo_esquerdo == philo->garfo_directo)
    {
        pthread_mutex_unlock(philo->garfo_esquerdo);
        ft_smart_usleep(philo, philo->time_morte + 10);
        return 1;
    }
    pthread_mutex_lock(philo->garfo_directo);
    printer(cur_time() - *philo->start, philo, "has taken a fork2");
    
    philo->eat++;
    printer(cur_time() - *philo->start, philo, "eating...");
    ft_smart_usleep(philo, philo->time_comer);
    
    pthread_mutex_unlock(philo->garfo_esquerdo);
    pthread_mutex_unlock(philo->garfo_directo);
    
    if (philo->opt && philo->eat == philo->opt)
        return 1;
    printer(cur_time() - *philo->start, philo, "sleeping");
    philo->time_morte += time_increase;
    ft_smart_usleep(philo, philo->time_dormir);
    return 0;
}

void *live_philo(void *arg) {
    t_philo *philo = (t_philo *)arg;
    long time_increase = philo->time_morte;
    while (!phil_status(philo, time_increase))
    {
        // Loop until the philosopher is done
    }
    return NULL;
}
