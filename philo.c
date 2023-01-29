/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:36:18 by abouzanb          #+#    #+#             */
/*   Updated: 2023/01/28 23:30:34 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	state_change(t_philo *str, int philosopher_number, char* state) {
	struct  timeval tv;

	pthread_mutex_lock(&str->mutexes);
	gettimeofday(&tv, NULL);
	long timestamp_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ldms philo %d %s\n", timestamp_in_ms - str->time, philosopher_number, state);
	if (state[3] != 'D')
		pthread_mutex_unlock(&str->mutexes);
}

void	*function(void *strr)
{
	struct timeval tv;
	
	t_philo *str = strr;
	while(1337)
	{	
		pthread_mutex_lock(&str->mutexes);
		gettimeofday(&tv, NULL);
		str->current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		pthread_mutex_unlock(&str->mutexes);
		pthread_mutex_lock(&str->mutex[str->id]);
		state_change(str, str->id, "has take a fork");
		pthread_mutex_lock(&str->mutex[str->id_left]);
		gettimeofday(&tv, NULL);
		state_change(str, str->id, "is eating");
		usleep(str->tte * 1000);
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&str->mutexes);
		str->last_meal = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		pthread_mutex_unlock(&str->mutexes);
		pthread_mutex_unlock(&str->mutex[str->id]);
		pthread_mutex_unlock(&str->mutex[str->id_left]);
		state_change(str, str->id, "is sleeping");
		usleep(str->tts * 1000);
		state_change(str, str->id, "is thinking");
	}
}
int main(int ac, char *av[])
{
	if (ac != 5 && ac != 6)
		return (1);
	int		i;
	int		pil;
	long	time;

	i = 0;
	pil = ft_atoi(av[1]);
	pthread_mutex_t *mutex;
	t_philo *philo = malloc(sizeof(t_philo) * pil);
	mutex = malloc(sizeof(pthread_mutex_t) * pil);
	while (i < pil)
	{
		pthread_mutex_init(&mutex[i], NULL);
		pthread_mutex_init(&philo[i].mutexes, NULL);
		i++;
	}
	i = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (i < pil)
	{
		philo[i].mutex = mutex;
		philo[i].id = i;
		philo[i].nof = pil;
		philo[i].ttd = ft_atoi(av[2]);
		philo[i].tte =  ft_atoi(av[3]);
		philo[i].tts = ft_atoi(av[4]);
		if (i == (pil - 1))
			philo[i].id_left = 0;
		else
			philo[i].id_left = i + 1;

		i++;
	}
	i = 0;
	while (i < pil)
	{
			philo[i].time = time;
			philo[i].last_meal = time;
			pthread_create(&philo[i].pid, NULL, function, &philo[i]);
			usleep(20);
			i++;
	}
	i =0;
	 while (1)
	 {
	 	pthread_mutex_lock(&philo[i].mutexes);
		
		gettimeofday(&tv, NULL);
		philo[i].current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	 	if (philo[i].current_time - philo[i].last_meal > philo[i].ttd)
	 	{
	 		pthread_mutex_lock(&philo[i].mutex[philo[i].id]);
	 		state_change(&philo[i],philo[i].id, "is died");
	 		exit(1);
	 	}
	 	pthread_mutex_unlock(&philo[i].mutexes);

	 		i++;
	 		if (i >= pil)
	 			i = 0;
	 }
}