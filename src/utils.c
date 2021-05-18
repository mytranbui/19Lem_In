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

// int nbchar_string(char *s, char c)
// {
// 	int nb;
// 	int i;

// 	nb = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			nb++;
// 		i++;
// 	}
// 	return (nb);
// }

t_hashmap	*init_hashmap_item(void)
{
	t_hashmap	*item;

	item = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
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

void	free_hashmap_item(t_hashmap **item, char *key)
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

t_hashmap	*room_exists(char *key, t_hashmap **hm)
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
		// ft_printf("FOUND KEY\n");
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
	if (errnum == 0)
		ft_printf("Invalid Argument");
	return (-1);
}

t_hashmap *copy_item(t_lemin *l, int i)
{
	t_hashmap *new;

	new = init_hashmap_item();
	if (!new)
		return (NULL);
	new->value = i;
	new->key = ft_strdup(l->hm[i]->key);
	if (!new->key)
		return (NULL);
	new->pt = l->hm[i]->pt;
	new->visited = l->hm[i]->visited;
	new->start = l->hm[i]->start;
	new->end = l->hm[i]->end;
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
	// new->node = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	// if (!new->node)
	// 	return (NULL);
	// new->node = copy_item(l, i);
	// if (!new->node)
	// 	return (NULL);
	new->node = init_hashmap_item();
	if (!new->node)
		return (NULL);
	new->node = l->hm[i];
	new->next = NULL;
	return (new);
}

t_path	*new_path(t_hashmap *hm)
{
	t_path *new;

	new = (t_path *)ft_memalloc(sizeof(t_path));
	if (!new)
		return (NULL);
		new->node = init_hashmap_item();
	if (!new->node)
		return (NULL);
	new->node = hm;
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
		free(curr);
		curr = next;
	}
	*head = NULL;
	return (NULL);
}