/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:06:21 by abouzanb          #+#    #+#             */
/*   Updated: 2023/01/29 23:39:58 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	the_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long time)
{
	long t;

	t = the_time();
	while ((the_time() - t) < time)
		usleep(250);
}

int	parsing(char *av[])
{
	int	i;
	int	x;

	i = 1;
	while (av[i])
	{
		x = 0;
		if (av[i][x] == '+')
			x++;
		while (av[i][x])
		{
			if (av[i][x] >= '9' && av[i][x] <= '0')
				return (-1);
			x++;
		}
		i++;
	}
	return (0);
}

void	get_init(pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nof)
	{
		pthread_mutex_init(&philo->print, NULL);
		pthread_mutex_init(&philo->save, NULL);
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	get_that(char *av[], pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nof)
	{
		philo[i].forks = forks;
		philo[i].idn = i + 1;
		philo[i].id = i;
		philo[i].ttd = ft_atoi(av[2]);
		philo[i].tte = ft_atoi(av[3]);
		philo[i].tts = ft_atoi(av[4]);
		if (i == (philo->nof - 1))
			philo[i].id_left = 0;
		else
			philo[i].id_left = (i + 1);
		if (philo[i].ttd == -1 || philo[i].tts == -1 || philo[i].tte == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	initi(char *av[], pthread_mutex_t **forks, t_philo **philo)
{
	int	phi;
	int	i;

	i = 0;
	if (parsing(av) == -1)
		return (-1);
	phi = ft_atoi(av[1]);
	if (phi <= 0)
		return (-1);
	*philo = malloc(sizeof(t_philo) * phi);
	*forks = malloc(sizeof(pthread_mutex_t) * phi);
	(*philo)->nof = phi;
	get_init(*forks, *philo);
	if (get_that(av, *forks, *philo) == -1)
		return (-1);
	return (0);
}

void	state_change(t_philo *str, char *state)
{
	pthread_mutex_lock(&str->print);
	printf("%ld | philo %d %s\n", (the_time() - str->time), str->idn, state);
	if (state[3] != 'd')
		pthread_mutex_unlock(&str->print);
}

void	*function(void *ptr)
{
	t_philo			*str;

	str = ptr;
	while (1)
	{
		pthread_mutex_lock(&str->forks[str->id]);
		state_change(str, "has taken a fork");
		pthread_mutex_lock(&str->forks[str->id_left]);
		state_change(str, "has taken another fork");
		pthread_mutex_lock(&str->save);
		str->last_meal = the_time();
		pthread_mutex_unlock(&str->save);
		state_change(str, "is eating");
		ft_usleep(str->tte);
		pthread_mutex_unlock(&str->forks[str->id]);
		pthread_mutex_unlock(&str->forks[str->id_left]);
		state_change(str, "is sleeping");
		ft_usleep(str->tts);
		state_change(str, "is thinking");
	}	
}

void	ft_pthread_create(t_philo *philo)
{
	int		i;
	long	consttime;

	consttime = the_time();
	i = 0;
	while (i < philo->nof)
	{
		philo[i].time = consttime;
		pthread_mutex_lock(&philo->save);
		philo[i].last_meal = the_time();
		pthread_mutex_unlock(&philo->save);
		pthread_create(&philo[i].pid, NULL, function, &philo[i]);
		usleep(100);
		i++;
	}
}

void	supervisore(t_philo *str)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < str->nof)
		{
			pthread_mutex_lock(&str[i].save);
			if ((the_time() - str[i].last_meal) > str[i].ttd)
			{
				state_change(&str[i], "is died");
				return ;
			}
			pthread_mutex_unlock(&str[i].save);
			i++;
		}		
	}
}

int	main(int ac, char *av[])
{
	pthread_mutex_t	*fork;
	t_philo			*philo;

	if (ac != 5 && ac != 6)
		return (0);
	if (initi(av, &fork, &philo) == -1)
		return (0);
	ft_pthread_create(philo);
	supervisore(philo);
	return (0);
}
