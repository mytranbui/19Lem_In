/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:34:11 by mbui              #+#    #+#             */
/*   Updated: 2021/05/21 13:34:16 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
	// {
		item->visited = 0;
	// 	item->start = 1;
	// }
	// else if (startend == 2)
	// 	item->end = 1;
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
	if (l->read_ok[0] == 0 || l->read_ok[2] == 1 || invalid_read(line, l) == 1)
		return (-2);
	info = ft_strsplit(line, ' ');
	if (!info)
		return (-1);
	if (isprint_str(info[0]) == -1 || room_exists(info[0], hm) ||
	isdigit_str(info[1]) == -1 || isdigit_str(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (-4);
	}
	pt.x = ft_atoi(info[1]);
	pt.y = ft_atoi(info[2]);
	item = insert_item(hm, info[0], pt, l->startend);
	if (!item)
		return (-1);
	get_start_and_end(l, item);
	ft_printf("room[%s] x[%d] y[%d]\n", info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	// ft_printf("~CHECK_ROOM~OK\n");
	l->nb_rooms++;
	l->read_ok[1] = 1;
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
	//copy nodes
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