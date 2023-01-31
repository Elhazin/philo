/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:35:34 by abouzanb          #+#    #+#             */
/*   Updated: 2023/01/27 23:35:37 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct t_phil
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	save;
	pthread_mutex_t	print;
	pthread_mutex_t	tcheck;
	int				id_left;
	int				check;
	int				all;
	int				number_of_eat;
	int				id;
	int				idn;
	int				ttd;
	int				tts;
	int				tte;
	long			time;
	long			last_meal;
	long			current_time;
	int				nof;
	int				nop;
	pthread_t		pid;
}t_philo;

int	ft_atoi(const char *s);

#endif
