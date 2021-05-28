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
		if (!new->next)
			return (NULL);
	}
	// ft_printf("hm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links->node->key);
	// ft_printf("ADD_LINK~OK\n");
	 return (head);
}

t_link2	*new_link2(int i)
{
	t_link2 *new;

	new = (t_link2 *)ft_memalloc(sizeof(t_link2));
	if (!new)
		return (NULL);
	new->value = i;
	new->next = NULL;
	return (new);
}

t_link2 *add_link2(t_lemin *l, int i, int i2)
{
	// ft_printf("ADD_LINK2\n");
	t_link2	*head;
	t_link2	*new;

	head = l->hm[i]->links2;
	if (l->hm[i]->links2 == NULL)
	{
		head = new_link2(i2);
		if (!head)
			return (NULL);
		l->hm[i]->links2 = head;
	}
	else
	{
		new = head;
		while (new->next != NULL)
			new = new->next;
		new->next = new_link2(i2);
		if (!new->next)
			return (NULL);
	}
	// ft_printf("hm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->links2->node->key);
	// ft_printf("ADD_LINK~OK\n");
	 return (head);
}

int	check_link(char *line, t_lemin *l, t_node **hm)
{
	// ft_printf("~CHECK_LINK~\n");
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
	if (l->adj_matrix[i][i2] == 1 || l->adj_matrix[i2][i] == 1)
        return (ERR_LINKS2);
	l->adj_matrix[i][i2] = 1;
	l->adj_matrix[i2][i] = 1;
	l->hm[i]->links = add_link(l, i, i2);
	l->hm[i2]->links = add_link(l, i2, i);
	l->hm[i]->links2 = add_link2(l, i, i2);
	l->hm[i2]->links2 = add_link2(l, i2, i);
	info = free_tab(info, 1);
	l->nb_links++;
	// ft_printf("~CHECK_LINK~OK\n");
	return (1);
}