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
	item->index = 0;
	item->visited = 0;
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
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (key[i] != '\0')
		index = index + 6 * (key[i++] % 10 + 60);
	// ft_printf("hash_i = %d\n", index);
	index = index % SIZE;
	// ft_printf("hash_i = %d\n", index);
	return (index);
}

t_node	*room_exists(char *key, t_node **hm)
{
	// ft_printf("~MATCH_KEY~\n");
	int	i;

	i = hash(key);
	while (hm[i] != NULL)
	{
		if (hm[i]->key && ft_strequ(hm[i]->key, key))
		{
			ft_printf("FOUND KEY : h[%d]=%s	x=%d y=%d\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);
			return (hm[i]);
		}
		i++;
		// i %= SIZE;
	}
	// ft_printf("~MATCH_KEY~END\n");
	return (NULL);
}

t_node *copy_item(t_lemin *l, int i)
{
	t_node *new;

	new = init_node_item();
	if (!new)
		return (NULL);
	new->index = i;
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

t_node *copy_node(t_node *node)
{
	t_node *new;

	new = init_node_item();
	if (!new)
		return (NULL);
	new->index = node->index;
	new->key = ft_strdup(node->key);
	if (!new->key)
		return (NULL);
	new->pt = node->pt;
	new->visited = node->visited;
	// new->start = node->start;
	// new->end = node->end;
	new->links = (t_link *)ft_memalloc(sizeof(t_link));
	if (!new->links)
		return (NULL);
	new->links = node->links;
	return (new);
}

t_link	*copy_link(t_link *link)
{
	t_link	*copy;

	if (link)
		return (NULL);
	copy = (t_link *)ft_memalloc(sizeof(t_link));
	if (!copy)
		return (NULL);
	copy->node = copy_node(link->node);
	copy->next = copy_link(link->next);
	return (copy);
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
	new->dist = 0;
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

// t_link	*lstdel_path(t_link **head)
// {
// 	t_link	*curr;
// 	t_link	*next;

// 	curr = *head;
// 	while (curr != NULL)
// 	{
// 		next = curr->next;
// 		ft_strdel(&curr->key);
// 		free(curr);
// 		curr = next;
// 	}
// 	*head = NULL;
// 	return (NULL);
// }