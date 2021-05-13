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

void	print_key(t_hashmap **hm)
{
	ft_printf("~PRINT_KEY~\n");
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (hm[i] != NULL)
		{
			if (hm[i]->start == 1)
				ft_printf("##start\n");
			if (hm[i]->end == 1)
				ft_printf("##end\n");
			ft_printf("h[%d]=%s x[%d] y[%d]\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);
		}
		// else
		// 	ft_printf("~~\n");
		//printf("i%d\n",i);
		i++;
	}
}

void	print_link(t_lemin *l)
{
	int	i;
	int	j;
	int	n;

	j = 0;
	n = 0;
	while (j < SIZE)
	{
		i = 0;
		while (i < SIZE)
		{
			if (l->adj_matrix[j][i] == 1)
			{
				ft_printf("matrix[%d][%d]\n", j, i);
				n++;
			}
			i++;
		}
		j++;
	}
	ft_printf("nb_links db=%d\n", n);
}

void	print_link2(t_lemin *l, int value)
{
	ft_printf("\nPRINT_LINKS2\n");

	ft_printf("hm[%d]%s\n", value, l->hm[value]->key);
	while (l->hm[value]->links != NULL)
	{
		//ft_printf("WHILE\n");
		ft_printf("->%s\n", l->hm[value]->links->node->key);
		l->hm[value]->links = l->hm[value]->links->next;
	}
	ft_printf("\n");
}

void	print_rooms(t_lemin *l)
{
	int	j;

	j = 0;
	while (l->rooms[j])
	{
		ft_printf("%s|\n", l->rooms[j]);
		j++;
	}
}

// void	print_result(t_lemin *l)
// {
// 	ft_printf("L%d-%s", ant, key);
// }