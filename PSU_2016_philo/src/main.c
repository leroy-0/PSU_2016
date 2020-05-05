/*
** main.c for main in /home/tekm/tek2/PSU_2016_philo
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Mar  9 08:26:03 2017 leroy_0
** Last update Thu Mar  9 08:26:05 2017 leroy_0
*/

#include "philo.h"

bool 		check_nbs(int nb_ph, int max_eat)
{
	if (nb_ph <= 0)
	{
		printf("%s\n", "Number of philosophers should be positive.");
		return (false);
	}
	if (max_eat <= 0)
	{
		printf("%s\n", "Number of max eat occurence should be positive.");
		return (false);
	}
	return (true);
}

int			*get_args(int ac, char **av)
{
	int 	x;
	int 	*res;

	x = 0;
	if ((res = malloc(sizeof(int) * 2)) == NULL)
		return (NULL);
	res[0] = 0;
	res[1] = 0;
	while (x < ac)
	{
		if (strcmp(av[x], "-p") == 0)
			res[0] = atoi(av[x + 1]);
		else if (strcmp(av[x], "-e") == 0)
			res[1] = atoi(av[x + 1]);
		x++;
	}
	if (!check_nbs(res[0], res[1]))
		return (NULL);
	return (res);
}

t_list 		*new_node()
{
	t_list 	*node;

	if ((node = malloc(sizeof(t_list))) == NULL)
		return (NULL);

	node->left = NULL;
	node->right = NULL;
	node->chopstick = true;
	node->eated = 0;
	return (node);
}

t_list 		*init_list(int size)
{
	t_list 	*head;
	t_list 	*tmp;
	int 	x;

	if ((head = new_node()) == NULL)
		return (NULL);

	x = 0;
	tmp = head;
	while (x < size)
	{
		if ((tmp->right = new_node()) == NULL)
			return (NULL);
		tmp->right->right = tmp;
		tmp = tmp->right;
		x++;
	}
	tmp->right = head;
	return (head);
}

void 		eat(t_list *node)
{
	//lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
	//lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
	node->chopstick = false;
	node->right->chopstick = false;
	lphilo_eat();
	//lphilo_release_chopstick(const pthread_mutex_t *mutex_id);
	//lphilo_release_chopstick(const pthread_mutex_t *mutex_id);
	node->chopstick = true;
	node->right->chopstick = true;
	node->sleeping = false;
	node->eated++;
}

void 		think(t_list *node)
{
	//lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
	node->chopstick = false;
	lphilo_think();
	//lphilo_release_chopstick(const pthread_mutex_t *mutex_id);
	node->chopstick = true;
	node->thinking = true;
	node->sleeping = false;
}

void 		sleep(t_list *node)
{
	if (node->thinking == true)
	{
		node->thinking = false;
		eat(node);
	}

	lphilo_sleep();

	node->sleeping = true;
}

bool 		is_finished(t_list 	*head, int max_eat, int nb_ph)
{
	t_list 	*tmp;
	int 	finished;
	int 	x;

	x = 0;
	tmp = head;
	finished = 0;
	while (x < nb_ph)
	{
		if (tmp->eated >= max_eat)
			finished++;
		tmp = tmp->right;
		x++;
	}
	if (finished == nb_ph)
		return (false);
	return (true);
}

void 		run(t_list 	*head, int max_eat, int nb_ph)
{
	t_list 	*tmp;

	tmp = head;
	while (is_finished(head, max_eat, nb_ph))
	{
		if (CAN_EAT(tmp) && tmp->sleeping == true && tmp->eated < max_eat)
			eat(tmp);
		else if (CAN_THINK(tmp) && tmp->sleeping == true)
			think(tmp);
		else if (CAN_SLEEP(tmp))
			sleep(tmp);
		tmp = tmp->right;
	}
}

void 		philosopher(int nb_ph, int max_eat)
{
	t_list 	*head;

	if ((head = init_list(nb_ph)) == NULL)
		return ;
	run(head, max_eat, nb_ph);
}

int 		main(int ac, char **av)
{
	int 	*res;

	if (ac == 5)
	{
		if ((res = get_args(ac, av)) == NULL)
			return (84);
		RCFStartup(ac, av);
		philosopher(res[0], res[1]);
		RCFCleanup();
		free(res);
		return (0);
	}
	printf("%s\n", "Usage: ./philo -p nb -e nb");
	return (84);
}