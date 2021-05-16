/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 01:08:15 by mbui              #+#    #+#             */
/*   Updated: 2021/04/17 15:56:55 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	add_edge()
{

}

t_path	*init_path(t_lemin *l)
{
	t_path	*p;

	p = (t_path *)ft_memalloc(sizeof(t_path));
	if (!p)
		return (NULL);
	// p->key = l->str_start;//hm
	// p->hm = l->hm[l];
	p->node = init_hashmap_item();
	if (!p->node)
		return (NULL);
	p->node = l->node_start;
	// ft_printf("%s%d",p->hm->key, p->hm->value);
	p->next = NULL;
	return (p);
}

void	get_path(t_lemin *l, t_path **p, int i)
{
	int	i;
	int	index;
	int min;
	t_path	*path;

	i = 0;
	index = 0;
	min = SIZE;
	path =
	while (p[i]->node->links)
	{
		
		p[i]->node->links->next;
	}
	while (i != l->node->end->value)
	{

	}
	while (i < SIZE)
	{
		if (l->hm[i]->visited == 0 && l->hm[i]->dist <= min)
		{
			min = l->hm[i]->dist;
			index = i;
		}
		i++;
	}
	return (index);
}

int algo(t_lemin *l)
{
	t_path **p;
	int		i;

	i = 0;
	p = (t_path **)ft_memalloc(sizeof(t_path *) * l->nb_ants);
	if (!p)
		return (-1);
	while (i < l->nb_ants)
	// {
		p[i++] = init_path(l);
	// }
	ft_printf("%s%d",p[0]->node->key, p[0]->node->value);
	ft_printf("%s%d",p[1]->node->key, p[1]->node->value);
	return (1);
}