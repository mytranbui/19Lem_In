/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:42:44 by mbui              #+#    #+#             */
/*   Updated: 2021/06/13 17:12:52 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	check_start_and_end(char *line, t_lemin *l)
{
	if (ft_strequ(line, "##start"))
	{
		l->startend = 1;
		l->start++;
	}
	else if (ft_strequ(line, "##end"))
	{
		l->startend = 2;
		l->end++;
	}
	if (l->start > 1 || l->end > 1)
		return (-1);
	return (1);
}

void	get_start_and_end(t_lemin *l, int i)
{
	if (l->startend == 1)
	{
		l->node_start = l->hm[i];
		//l->hm[i]->dist = -1;//hm

		// l->node_start = copy_item(l, i);
		l->i_start = i;
	}
	else if (l->startend == 2)
	{
		l->node_end = l->hm[i];
		// l->node_end = copy_item(l, i);
		l->i_end = i;
	}
	if (l->startend != 0)
		l->startend = 0;
}
