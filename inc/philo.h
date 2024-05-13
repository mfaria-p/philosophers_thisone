/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:42:15 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/05/13 14:39:39 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define PHILO_MAX 200

//estrutura para cada um dos filosofos
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

//estrutura do programa que controla todos os filosofos e que tem os mutexes
typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//init
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **av);
void	user_input(t_philo *philo, char **av);

//main
int		check_arg_content(char *arg);
int		check_valid_args(char **av);

//threads
int		threads_create(t_program *program, pthread_mutex_t *forks);
void	mutex_destroy(char *str, t_program *program, pthread_mutex_t *forks);

//philos routine
void	*philo_routine(void *ptr);
int		check_death(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	one_philo(t_philo *philo);

//observer routine
void	*monitor(void *pointer);
int		check_if_all_ate(t_philo *philos);
int		check_if_died(t_philo *philos);
int		philosopher_dead(t_philo *philo, size_t time_to_die);

//time utils
int		ft_gettime(void);
int		ft_usleep(size_t milliseconds);

//other utils
int		ft_atoi(const char *nptr);
int		ft_strlen(char *str);
void	print_state(char *str, t_philo *philo, int id);

#endif
