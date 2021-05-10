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

t_path	*init_path(t_lemin *l)
{
	t_path	*p;

	p = (t_path *)ft_memalloc(sizeof(t_path));
	if (!p)
		return (NULL);
	// p->key = l->str_start;//hm
	// p->hm = l->hm[l];
	p->hm = init_hashmap_item();
	if (!p->hm)
		return (NULL);
	p->hm = l->hm_start;
	// ft_printf("%s%d",p->hm->key, p->hm->value);
	p->next = NULL;
	return (p);
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
	ft_printf("%s%d",p[0]->hm->key, p[0]->hm->value);
	ft_printf("%s%d",p[1]->hm->key, p[1]->hm->value);
	return (1);
}
