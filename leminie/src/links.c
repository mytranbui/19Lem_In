/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:34:22 by mbui              #+#    #+#             */
/*   Updated: 2021/05/21 13:34:24 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_link	*new_link(t_lemin *l, int i)
{
	t_link *new;

	new = (t_link *)ft_memalloc(sizeof(t_link));
	if (!new)
		return (NULL);
	// new->node = (t_node *)ft_memalloc(sizeof(t_node));
	// if (!new->node)
	// 	return (NULL);
	// new->node = copy_item(l, i);
	// if (!new->node)
	// 	return (NULL);
	new->node = init_node_item();
	if (!new->node)
		return (NULL);
	// new->index = i;
	new->nb = 0;
	new->node = l->hm[i];
	new->next = NULL;
	return (new);
}

t_link *add_link(t_lemin *l, int i, int i2)
{
	// ft_printf("ADD_LINK\n");
	t_link	*head;
	t_link	*new;

	head = l->hm[i]->links;
	head->nb++;
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
		if (!new->next)
			return (NULL);
	}
	// ft_printf("hm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links->node->key);
	// ft_printf("ADD_LINK~OK\n");
	 return (head);
}

int	check_link(char *line, t_lemin *l, t_node **hm)
{
	ft_printf("~CHECK_LINK~\n");
	char	**info;
	int		i;
	int		i2;

	if (l->read_ok[0] == 0 || l->read_ok[1] == 0 || invalid_read(line, l) == 1)
		return (ERR_LINE);
	l->read_ok[2] = 1;
	info = ft_strsplit(line, '-');
	i = 0;
	i2 = 0;
	if (!info)
		return (-1);
	ft_printf("s1[%s]-s2[%s]\n", info[0], info[1]);
	if (!room_exists(info[0], hm) || !room_exists(info[1], hm) || ft_strequ(info[0], info[1]))
		return (ERR_LINKS);
	i = hash(info[0]);
	i2 = hash(info[1]);
	if (i2 != l->node_start->index)
		l->hm[i]->links = add_link(l, i, i2);
	if (i != l->node_start->index)
		l->hm[i2]->links = add_link(l, i2, i);
	info = free_tab(info, 1);
	l->nb_links++;
	ft_printf("~CHECK_LINK~OK\n");
	return (1);
}