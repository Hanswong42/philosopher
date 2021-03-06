/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:25:15 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/08 18:31:51 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

/*
	1.sem_post monitor semaphore is to trigger 
	the refresh of last_eaten time on main process
*/
void	pickfork(t_philo *info)
{
	sem_wait(info->data->sem);
	monitor(get_ms(), 0, info, 0);
	print_text("has taken a fork\n", YELLOW, info->id, info->data);
	sem_wait(info->data->sem);
	monitor(get_ms(), 0, info, 0);
	print_text("has taken a fork\n", YELLOW, info->id, info->data);
	print_text("is eating\n", GREEN, info->id, info->data);
}

void	eat(t_philo *info)
{	
	pickfork(info);
	info->last_eaten = get_ms();
	monitor(get_ms(), info->data->eat, info, 0);
	info->eaten--;
	sem_post(info->data->sem);
	sem_post(info->data->sem);
}

void	sleeping(t_philo *info)
{
	print_text("is sleeping\n", BLUE, info->id, info->data);
	monitor(get_ms(), info->data->sleep, info, 0);
}

/*
	1. sem_t start started as 0, hence all process 
	will be waiting until the switch is flipped
	2. after that, it will flip its corresponding 
	monitor sem_t to refresh the last_eaten time;
	3. even number id will get delayed for half of eating time
*/
int	action(t_philo	*info)
{
	sem_wait(info->data->start);
	info->last_eaten = get_ms();
	print_text("is thinking\n", CYAN, info->id, info->data);
	sem_post(info->data->start);
	if (info->id % 2 == 0)
		monitor(get_ms(), info->data->eat / 2, info, 0);
	while (info->eaten > 0 && info->data->philo > 1)
	{
		monitor(get_ms(), 0, info, 0);
		eat(info);
		sleeping(info);
		if (info->data->eat > info->data->sleep)
			monitor(get_ms(), info->data->eat - info->data->sleep, info, 1);
		if (info->data->philo % 2 == 1)
			monitor(get_ms(), info->data->eat, info, 1);
	}
	if (info->data->philo == 1)
		monitor(get_ms(), info->data->death, info, 0);
	exit (0);
}

/*
	1. the creation of philo as a child process;
	2. Since they duplicate the value, instead of array of struct like mandatory,
	I used 1 struct and update its value before the forking process;
	3. I also store pid of child process 
	into an array in the main struct t_data;
	4. Last_eaten time will get initialized once the 
	creation of child process is finished
	5. In order to synchronize their starting time, 
	they will lie dormant until sem_t start turn into 1
	which happen after the creation of last child process;
*/
int	fork_creation(t_data *info)
{
	t_philo		ph;
	int			i;

	i = 0;
	while (i < info->philo)
	{
		ph.id = i;
		ph.data = info;
		ph.rfork = i;
		ph.lfork = (i + 1) % info->philo;
		ph.eaten = info->timeleft;
		ph.fin = 0;
		info->pid[i] = fork();
		if (info->pid[i] == 0)
			return (action(&ph));
		i++;
	}
	sem_post(info->start);
	return (0);
}
