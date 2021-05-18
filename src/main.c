/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <mbui@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:22:10 by mbui              #+#    #+#             */
/*   Updated: 2021/05/06 13:36:17 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	ft_read(int fd)
{
	char	*file;
	int		ret;

	file = ft_strnew(MAX_STRING + 1);
	if (!file)
		return (-1);
	if ((ret = read(fd, file, MAX_STRING + 1)) <= 0 || ret > MAX_STRING)
	{
		ft_strdel(&file);
		return (-1);
	}
	//ft_bzero(file, MAX_STRING);
	ft_strdel(&file);
	close(fd);
	return (1);
}

t_lemin	*init_lemin(void)
{
	t_lemin	*l;
	int	i;
	int	j;

	l = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	if (!l)
		return (NULL);
	l->nb_ants = 0;
	l->nb_rooms = 0;
	l->nb_links = 0;
	l->rooms = NULL;
	              ft_bzero(&l->adj_matrix, SIZE); ///??? working?
	l->start = 0;
	l->end = 0;
	l->read_error[0] = 0;
	l->read_error[1] = 0;
	l->read_error[2] = 0;
	j = 0;
	while (j < SIZE)
	{
		i = 0;
		while (i < SIZE)
		{
			l->adj_matrix[j][i] = 0;
			i++;
		}
		j++;
	}
	j = 0;
	while (j < SIZE)
	{
		l->hm[j++] = NULL;
	}
	l->node_start = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->node_start)
		return (NULL);
		l->node_end = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->node_end)
		return (NULL);
	l->tab = NULL;
	l->startend = 0;
	return (l);
}

t_hashmap	*insert_item(t_hashmap **hm, char *key, t_point pt, int startend)
{
	// ft_printf("~INSERT~\n");
	t_hashmap	*item;
	int	i;

	i = hash(key);
	item = init_hashmap_item();
	if (!item)
		return (NULL);
	item->value = i;
	item->key = ft_strdup(key);
	if (!item->key)
		return (NULL);
	item->pt = pt;
	// while (hm[i] != NULL)// && hm[i]->key != NULL)
	// {
	// 	ft_printf("NEXT CELL\n");
	// 	i++;
	// 	// i %= SIZE;
	// }
	if (startend == 1)
	{
		item->start = 1;
		item->visited = 0;
	}
	if (startend == 2)
		item->end = 1;
	// ft_printf("h[%d]=%s x=%d y=%d		====>i=%d	%s\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y, i, hm[i]->key);
	//free_hashmap_item(&item), item->key);
	//if free can't print so free after?
	// ft_printf("~INSERT~OK\n");
	return (hm[i] = item);
}

int	check_room(char *line, t_lemin *l, t_hashmap **hm)
{
	// ft_printf("~CHECK_ROOM~\n");
	char	**info;
	t_point	pt;
	t_hashmap *item;

	info = NULL;
	item = NULL;
	assign_pt(&pt, 0, 0);
	if (l->read_error[0]== 0 || l->read_error[2] == 1 || invalid_read(line, l) == 1)
		return (-1);
	l->read_error[1] = 1;
	info = ft_strsplit(line, ' ');
	if (!info)
		return (-1);
	if (isdigit_str(info[1]) == -1 || isdigit_str(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (-1);
	}
	pt.x = ft_atoi(info[1]);
	pt.y = ft_atoi(info[2]);
	item = insert_item(hm, info[0], pt, l->startend);
	if (!item)
		return (-1);
	if (l->startend == 1)
	{
		// l->str_start = ft_strdup(info[0]);
		l->node_start = item;
	}
	if (l->startend == 2)
	{
		// l->str_end = ft_strdup(info[0]);
		l->node_end = item;
	}
	ft_printf("room[%s] x[%d] y[%d]\n", info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	// ft_printf("~CHECK_ROOM~OK\n");
	l->nb_rooms++;
	if (l->startend != 0)
		l->startend = 0;
	return (1);
}

t_link *add_link(t_lemin *l, int i, int i2)
{
	// ft_printf("ADD_LINK\n");
	t_link	*head;
	t_link	*new;

	head = l->hm[i]->links;
	if (l->hm[i]->links == NULL)
	{
		head = new_link(l, i2);
		if (!head)
			return (NULL);
		l->hm[i]->links = head;
	}
	else
	{
		new = head;
		while (new->next != NULL)
			new = new->next;
		new->next = new_link(l, i2);
		if (!new->next) //edit added->next
			return (NULL);
	}
	// ft_printf("hm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links->node->key);
	// ft_printf("ADD_LINK~OK\n");
	 return (head);
}

int	check_link(char *line, t_lemin *l, t_hashmap **hm)
{
	// ft_printf("~CHECK_LINK~\n");
	char	**info;
	int		i;
	int		i2;

	if (l->read_error[0] == 0 || l->read_error[1] == 0 || invalid_read(line, l) == 1)
		return (-1);
	l->read_error[2] = 1;
	info = ft_strsplit(line, '-');
	i = 0;
	i2 = 0;
	if (!info)
		return (-1);
	ft_printf("s1[%s]-s2[%s]\n", info[0], info[1]);
	if (!match_key(info[0], hm) || !match_key(info[1], hm))
		return (-1);
	i = hash(info[0]);
	i2 = hash(info[1]);
	if (l->adj_matrix[i][i2] == 1 || l->adj_matrix[i2][i] == 1)
		return (-1);
	l->adj_matrix[i][i2] = 1;
	l->adj_matrix[i2][i] = 1;
	l->hm[i]->links = add_link(l, i, i2);
	l->hm[i2]->links = add_link(l, i2, i);
	info = free_tab(info, 1);
	l->nb_links++;
	// ft_printf("~CHECK_LINK~OK\n");
	return (1);
}

void	get_rooms(t_lemin *l)
{
	ft_printf("GET_ROOMS\n");
	int	i;
	int	j;

	i = 0;
	j = 0;
	l->rooms = (char **)ft_memalloc(sizeof(char *) * l->nb_rooms);
	if (!l->rooms)
		return ;
	while (j < l->nb_rooms)
	{
		l->rooms[j] = NULL;
		j++;
	}
	j = 0;
	while (i < SIZE && j < l->nb_rooms)
	{
		// ft_printf("WHILE\n");
		if (l->hm[i] != NULL)
		{
			// ft_printf("add_ROOMS\n");
			l->rooms[j] = ft_strdup(l->hm[i]->key);
			if (!l->rooms[j])
				return ;
			// ft_printf("%s|\n", l->rooms[j]);
			j++;
		}
		i++;
	}
	print_rooms(l);
	// l->tab = (t_hashmap **)ft_memalloc(sizeof(t_hashmap *) * l->nb_rooms);
	// if (!l->tab)
	// 	return ;
	// i = 0;
	// j = 0;
	// while (i < SIZE)
	// {
	// 	if (l->hm[i] != NULL)
	// 	{
	// 		l->tab[j] = copy_item(l, i);
	// 		if (!l->tab[j])
	// 			return ;
	// 		ft_printf("%s|\n", l->tab[j]->key);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

/*
** Room will never start with the character 'L' nor the character '#'
*/
int	main(void)
{
	t_lemin	*l;

	// if ((ft_read(0)) == -1)
	// {
	// 	ft_putendl("ERROR");
	// 	return (-1);
	// }
	// ft_printf("READ OK\n");
	l = init_lemin();
	if (!l)
		return (-1);
	if (read_map(l) == -1)
		return (-1);
		//error_free(l);
	ft_printf("nb_rooms=%d\n", l->nb_rooms);
	ft_printf("nb_links=%d\n", l->nb_links);
	ft_printf("start=%d end=%d\n", l->start, l->end);
	// get_rooms(l);
	// print_key(l->hm);
	// print_link(l);
	 print_link2(l, 90);
	print_link2(l, 96);
	print_link2(l, 8);
	print_link2(l, 14);
	print_link2(l, 60);
	get_rooms(l);
	//algo(l);
	return (0);
}
