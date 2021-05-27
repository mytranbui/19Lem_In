/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:53:46 by mbui              #+#    #+#             */
/*   Updated: 2021/05/06 13:36:28 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void free_lemin(t_lemin *lemin)
{
	free(lemin);
	lemin = NULL;
	exit(-1);
}

int invalid_read(char *line, t_lemin *l)
{
	if (line[0] == 'L' || l->start > 1 || l->end > 1)
		return (1);
	return (-1);
}

t_link	*lstdel_link(t_link **head)
{
	t_link	*curr;
	t_link	*next;

	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*head = NULL;
	return (NULL);
}

void	free_node(t_node **node, char *key, t_link **head)
{
	if (key)
		ft_strdel(&key);
	if (head)
		lstdel_link(head);
	if (node)
	{
		free(*node);
		*node = NULL;
	}
	node = NULL;
}

t_node	*init_node_item(void)
{
	t_node	*item;

	item = (t_node *)ft_memalloc(sizeof(t_node));
	if (!item)
		return (NULL);
	item->key = NULL;
	item->value = 0;
	item->visited = 0;
	item->infinity = 1;
	item->dist = 0;
	// item->start = 0;
	// item->end = 0;
	assign_pt(&item->pt, 0, 0);
	item->links = NULL;
	return (item);
}

void	free_hashmap_item(t_node **item, char *key)
{
	ft_strdel(&key);
	key = NULL;
	if (item)
	{
		free(*item);
		*item = NULL;
	}
	item = NULL;
}

int	hash(char *key)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	while (key[i] != '\0')
		value = value + 6 * (key[i++] % 10 + 60);
	// ft_printf("hash_i = %d\n", value);
	value = value % SIZE;
	// ft_printf("hash_i = %d\n", value);
	return (value);
}

t_node	*room_exists(char *key, t_node **hm)
{
	// ft_printf("~MATCH_KEY~\n");
	int	i;

	i = hash(key);
	// while(hm[i])
	// {
	// 	ft_printf("WHILE %d\n", i);
	// ft_printf("key=%s | h[%d]=%s", key, i, hm[i]->key);
	if (!hm[i])
		return (NULL);
	if (hm[i]->key && ft_strequ(hm[i]->key, key))
	{
		ft_printf("FOUND KEY : h[%d]=%s	x=%d y=%d\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);
		return (hm[i]);
	}
	// 	i++;
	// 	i %= SIZE;
	// }
	// ft_printf("~MATCH_KEY~END\n");
	return (NULL);
}

int	error(int errnum)
{
	ft_printf("ERROR : ");
	if (errnum == -1)
		ft_printf("Invalid Argument\n");
	else if (errnum == -2)
		ft_printf("Invalid Map : Invalid Line or More Than One Start/End\n");
	else if (errnum == -3)
		ft_printf("Invalid Map : Ants\n");
	else if (errnum == -4)
		ft_printf("Invalid Map : Room\n");
	else if (errnum == -5)
		ft_printf("Invalid Map : Link\n");
	else if (errnum == -55)
		ft_printf("Invalid Map : Two Identic Links\n");
	else if (errnum == -6)
		ft_printf("No Path Found\n");
	// else if (errnum == -7)
	// else if (errnum == 7)
	//free all
	return (-1);
}

t_node *copy_item(t_lemin *l, int i)
{
	t_node *new;

	new = init_node_item();
	if (!new)
		return (NULL);
	new->value = i;
	new->key = ft_strdup(l->hm[i]->key);
	if (!new->key)
		return (NULL);
	new->pt = l->hm[i]->pt;
	new->visited = l->hm[i]->visited;
	// new->start = l->hm[i]->start;
	// new->end = l->hm[i]->end;
	new->links = (t_link *)ft_memalloc(sizeof(t_link));
	if (!new->links)
		return (NULL);
	new->links = l->hm[i]->links;
	return (new);
}

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
	new->node = l->hm[i];
	new->next = NULL;
	return (new);
}

t_path	*new_path(t_node *hm)
{
	t_path *new;

	new = (t_path *)ft_memalloc(sizeof(t_path));
	if (!new)
		return (NULL);
		new->node = init_node_item();
	if (!new->node)
		return (NULL);
	new->node = hm;
	new->key = ft_strdup(hm->key);
	if (!new->key)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_path	*lstdel_path(t_path **head)
{
	t_path	*curr;
	t_path	*next;

	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		ft_strdel(&curr->key);
		free(curr);
		curr = next;
	}
	*head = NULL;
	return (NULL);
}