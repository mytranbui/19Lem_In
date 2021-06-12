/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:42:44 by mbui              #+#    #+#             */
/*   Updated: 2021/05/20 13:43:15 by mbui             ###   ########.fr       */
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

void	get_start_and_end(t_lemin *l, t_node *item)
{
	if (l->startend == 1)
	{
		l->node_start = item;
	}
	else if (l->startend == 2)
	{
		l->node_end = item;
	}
	if (l->startend != 0)
		l->startend = 0;
}
