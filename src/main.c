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
	l->hm_start = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->hm_start)
		return (NULL);
		l->hm_end = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!l->hm_end)
		return (NULL);
	return (l);
}

// t_room	*init_room(void)
// {
// 	t_room	*r;

// 	r = (t_room *)ft_memalloc(sizeof(t_room));
// 	if (!r)
// 		return (NULL);
// 	r->name = NULL;
// 	r->link = NULL;
// 	assign_pt(&r->pt, 0, 0);
// 	return (r);
// }

// t_room	*get_room(char *line)
// {
// 	char	**info;
// 	t_room	*r;

// 	info = NULL;
// 	r = init_room();
// 	if (nbchar_string(line, ' ') != 2)
// 		return (NULL);
// 	info = ft_strsplit(line, ' ');
// 	if (!info)
// 		return (NULL);
// 	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
// 	{
// 		info = free_tab(info, 2);
// 		return (NULL);
// 	}
// 	r->name = ft_strdup(info[0]);
// 	if (!r->name)
// 		return (NULL);
// 	r->pt.x = ft_atoi(info[1]);
// 	r->pt.y = ft_atoi(info[2]);
// 	info = free_tab(info, 2);
// 	ft_printf("room=%s x=%d y=%d\n", r->name, r->pt.x, r->pt.y);
// 	return (r);
// }

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
		l->hm_start = item;
	}
	if (stnd == 2)
	{
		// l->str_end = ft_strdup(info[0]);
		l->hm_end = item;
	}
	ft_printf("room[%s] x[%d] y[%d]\n", info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	// ft_printf("~CHECK_ROOM~OK\n");
	l->nb_rooms++;
	return (1);
}

t_link	*new_link(char *s)
{
	t_link *new;

	new = (t_link *)ft_memalloc(sizeof(t_link));
	if (!new)
		return (NULL);
	new->s = ft_strdup(s);
	if (!new->s)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_link *add_link(t_lemin *l, int i, char *s)
{
	ft_printf("ADD_LINK\n");
	t_link	*head;
	t_link	*new;

	head = l->hm[i]->links;
	if (l->hm[i]->links == NULL)
	{
		ft_printf("NULL\n");
		head = new_link(s);
		if (!head)
			return (NULL);
		l->hm[i]->links = head;
		ft_printf("LOLhm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links->s);
		ft_printf("HEADhm[%d]->%s\n", i, head->s);
	}
	else
	{
		new = head;
		ft_printf("NOTNULL\n");
		while (new->next != NULL)
			new = new->next;
		new->next = new_link(s);
		if (!new)
			return (NULL);
		ft_printf("HEADhm[%d]->%s\n", i, head->s);
	}
	ft_printf("LOLhm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links->s);
	 return (head);
}

// t_link	*add_link(t_lemin *l, int i, char *s)
// {
// 	t_link	*head;
// 	int		exist;

// 	head = NULL;
// 	exist = 0;
// 	if (l->hm[i]->links != NULL)
// 	{
// 		exist = 1;
// 		head = l->hm[i]->links;
// 		while (l->hm[i]->links != NULL)
// 			l->hm[i]->links = l->hm[i]->links->next;
// 	}
// 	l->hm[i]->links = (t_link *)ft_memalloc(sizeof(t_link));
// 	if (!l->hm[i]->links)
// 		return (NULL);
// 	l->hm[i]->links->s = ft_strdup(s);
// 	if (!l->hm[i]->links->s)
// 		return (NULL);
// 	if (exist == 0)
// 		head = l->hm[i]->links;
// 	l->hm[i]->links->next = NULL;
// 	return (head);
// }

int	get_link(char *line, t_lemin *l, char *info, char *info2)
{
	ft_printf("~GET_LINK~\n");
	int	i;
	int	i2;

	i = hash(info);
	i2 = hash(info2);
	ft_printf("%s\n", ft_strcsub(line, 0, '-'));
	if (l->adj_matrix[i][i2] == 1 || l->adj_matrix[i2][i] == 1)
		return (-1);
	l->adj_matrix[i][i2] = 1;
	l->adj_matrix[i2][i] = 1;
	l->hm[i]->links = add_link(l, i, info2);
	l->hm[i2]->links = add_link(l, i2, info);
	ft_printf("~GET_LINK~OK\n");
	return (1);
}

int	check_link(char *line, t_lemin *l, t_hashmap **hm)
{
	// ft_printf("~CHECK_LINK~\n");
	char	**info;

	info = ft_strsplit(line, '-');
	if (!info)
		return (-1);
	ft_printf("s1[%s]-s2[%s]\n", info[0], info[1]);
	if (!match_key(info[0], hm) || !match_key(info[1], hm))
	{
		ft_printf("MATCH_KEY ERROR\n");
		return (-1);
	}
	// ft_printf("~CHECK_LINK~OK\n");
	if (get_link(line, l, info[0], info[1]) == -1)
		return (-1);
	info = free_tab(info, 1);
	l->nb_links++;
	return (1);
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
	// ft_printf("READ OK2\n");
	if (!(get_next_line(0, &line)))
		return (-1);
	// ft_printf("READ OK3\n");
	ft_printf("[%s]\n", line);
	if (l->nb_ants == 0)
		l->nb_ants = isdigitstr(line);
	// ft_printf("READ OK4\n");
	if (l->nb_ants == -1)
		free_lemin(l);
	// ft_printf("READ OK5\n");
	ft_printf("ANTS[%d]\n", l->nb_ants);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("[%s]\n", line);
		if (line && !ft_strcmp(line, "##start"))
		{
			stnd = 1;
			l->start++;
		}
		if (line && !ft_strcmp(line, "##end"))
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
	//algo(l);
	return (0);
}
