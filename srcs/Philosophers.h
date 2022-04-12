/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:05:20 by wding-ha          #+#    #+#             */
/*   Updated: 2022/04/12 17:53:54 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_data t_data;
typedef struct s_philo {
	pthread_t	thread;
	int			id;
	t_data		*data;
}				t_philo;

typedef struct s_data {
	int				philo;
	int				death;
	int				eat;
	int				sleep;
	int				dead;
	pthread_mutex_t	*lock;
	t_philo			num;
}				t_data;



#endif