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

int	init_path(char *key ,t_lemin *l, int i)
{
	t_path	*p;

	p = (t_path *)ft_memalloc(sizeof(t_path));
	if (!p)
		return (NULL);
	p->key = key;//hm
	p->hm = l->hm[i];
	p->next = NULL;
	return (p);
}

// int algo()
// {

// }
