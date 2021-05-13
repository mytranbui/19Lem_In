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
	//init_matrix(l->adj_matrix, SIZE, SIZE);//kk
	//init_matrix(l->adj_matrix, SIZE, SIZE);//kk
	              ft_bzero(&l->adj_matrix, SIZE); ///??? working?
	l->start = 0;
	l->end = 0;
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
	l->node_start = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->node_start)
		return (NULL);
		l->node_end = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->node_end)
		return (NULL);
	return (l);
}

t_hashmap	*insert_item(t_hashmap **hm, char *key, t_point pt, int stnd)
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
	if (stnd == 1)
	{
		item->start = 1;
		item->visited = 0;
	}
	if (stnd == 2)
		item->end = 1;
	// ft_printf("h[%d]=%s x=%d y=%d		====>i=%d	%s\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y, i, hm[i]->key);
	//free_hashmap_item(&item), item->key);
	//if free can't print so free after?
	// ft_printf("~INSERT~OK\n");
	return (hm[i] = item);
}

int	check_room(char *line, t_hashmap **hm, t_lemin *l, int stnd)
{
	// ft_printf("~CHECK_ROOM~\n");
	char	**info;
	t_point	pt;
	t_hashmap *item;

	info = NULL;
	item = NULL;
	assign_pt(&pt, 0, 0);
	info = ft_strsplit(line, ' ');
	if (!info)
		return (-1);
	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (-1);
	}
	pt.x = ft_atoi(info[1]);
	pt.y = ft_atoi(info[2]);
	item = insert_item(hm, info[0], pt, stnd);
	if (!item)
		return (-1);
	if (stnd == 1)
	{
		// l->str_start = ft_strdup(info[0]);
		l->node_start = item;
	}
	if (stnd == 2)
	{
		// l->str_end = ft_strdup(info[0]);
		l->node_end = item;
	}
	ft_printf("room[%s] x[%d] y[%d]\n", info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	// ft_printf("~CHECK_ROOM~OK\n");
	l->nb_rooms++;
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
		if (!new)
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

	info = ft_strsplit(line, '-');
	i = 0;
	i2 = 0;
	if (!info)
		return (-1);
	ft_printf("s1[%s]-s2[%s]\n", info[0], info[1]);
	if (!match_key(info[0], hm) || !match_key(info[1], hm))
	{
		ft_printf("MATCH_KEY ERROR\n");
		return (-1);
	}
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
	while (i < SIZE && j < l->nb_rooms)
	{
		if (l->hm[i] != NULL)
		{
			l->rooms[j++] = ft_strdup(l->hm[i]->key);
			if (l->rooms[j])
				return ;
		}
		i++;
	}
	print_rooms(l);
}

/*
** Room will never start with the character 'L' nor the character '#'
*/
int	main(void)
{
	t_lemin	*l;
	char	*line;
	int		start;
	int		end;
	int		stnd;

	start = 0;
	end = 0;
	stnd = 0;
	// if ((ft_read(0)) == -1)
	// {
	// 	ft_putendl("ERROR");
	// 	return (-1);
	// }
	// ft_printf("READ OK\n");
	l = init_lemin();
	if (!l)
		return (-1);
	if (!(get_next_line(0, &line)))
		return (-1);
	ft_printf("[%s]\n", line);
	if (l->nb_ants == 0)
		l->nb_ants = isdigitstr(line);
	if (l->nb_ants == -1)
		free_lemin(l);
	ft_printf("ANTS[%d]\n", l->nb_ants);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) > 0 && line) //&& (line[0] == '#' || nb_word(line, ' ') == 3))
	{
		ft_printf("[%s]\n", line);
		if (!ft_strcmp(line, "##start"))
		{
			stnd = 1;
			l->start++;
		}
		else if (!ft_strcmp(line, "##end"))
		{
			stnd = 2;
			l->end++;
		}
		if (line[0] == 'L' || l->start > 1 || l->end > 1)
			return (-1);
		if (line[0] != '#')
		{
			if (nb_word(line, ' ') == 3)
			{
				if (check_room(line, l->hm, l, stnd) == -1)
					return (-1);
				if (stnd != 0)
					stnd = 0;
			}
			else if (nb_word(line, '-') == 2)
			{
				if (check_link(line, l, l->hm) == -1)
					return (-1);	
			}
		}
		if (line)
			ft_strdel(&line);
	}
	// get_rooms(l);
	// while (get_next_line(0, &line) > 0 && line && (line[0] == '#' || nb_word(line, '-') == 2))
	// {
	// 	ft_printf("{%s}\n", line);
	// 	// if (line[0] == 'L')
	// 	// 	return (-1);
	// 	if (line[0] != '#')
	// 		if (check_link(line, l, l->hm) == -1)
	// 			return (-1);
	// 	if (line)
	// 		ft_strdel(&line);
	// }
	if (l->start == 0 || l->end == 0)
		return (-1);
	ft_printf("nb_rooms=%d\n", l->nb_rooms);
	ft_printf("nb_links=%d\n", l->nb_links);
	ft_printf("start=%d end=%d\n", start, end);
	print_key(l->hm);
	print_link(l);
	print_link2(l, 90);
	print_link2(l, 96);
	print_link2(l, 8);
	print_link2(l, 14);
	print_link2(l, 60);
	get_rooms(l);
	//algo(l);
	return (0);
}
