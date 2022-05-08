/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:05:20 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/08 22:41:12 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include "libft.h"
# include "color.h"

typedef struct s_data {
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				timeleft;		
	int				dead;
	int				done;
	int				start;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print;
	pthread_mutex_t	checklock;
	pthread_mutex_t	startlock;
}				t_data;

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	int				rfork;
	int				lfork;
	long long		last_eaten;
	int				eaten;
	t_data			*data;
}				t_philo;

int			input_checking(char **av, int ac);
void		build_info(t_data *info, char **argv, int argc);
void		*action(void *args);
void		create_thread(t_data *info);
void		print_text(char *s, char *c, int id, t_data *info);
void		destroy_mutex(t_data *info);
long long	get_ms(void);
void		*death(void *arg);
void		ft_msleep(int time, long long start);
int			ft_malloc(void **ptr, size_t size);
int			error(int i);
int			get_start(t_philo *info);
int			get_dead(t_philo *info);

#endif