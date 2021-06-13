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

void	print_key(t_node **hm)
{
	ft_printf("~PRINT_KEY~\n");
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (hm[i] != NULL)
		{
			// if (hm[i]->start == 1)
			// 	ft_printf("##start\n");
			// if (hm[i]->end == 1)
			// 	ft_printf("##end\n");
			ft_printf("h[%d]=%s x[%d] y[%d]\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);
		}
		// else
		// 	ft_printf("~~\n");
		//printf("i%d\n",i);
		i++;
	}
}

// void	print_link(t_lemin *l)
// {
// 	int	i;
// 	int	j;
// 	int	n;

// 	j = 0;
// 	n = 0;
// 	while (j < SIZE)
// 	{
// 		i = 0;
// 		while (i < SIZE)
// 		{
// 			if (l->adj_matrix[j][i] == 1)
// 			{
// 				ft_printf("matrix[%d][%d]\n", j, i);
// 				n++;
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// 	ft_printf("nb_links db=%d\n", n);
// }

void	print_link2(t_lemin *l, int index)
{
	// ft_printf("\nPRINT_LINKS2\n");
	t_link	*tmp;

	tmp = l->hm[index]->links;
	ft_printf("LINK hm[%d]%s nb(%d)", index, l->hm[index]->key, l->hm[index]->links->nb);
	while (tmp != NULL)
	{
		//ft_printf("WHILE\n");
		ft_printf("->%s", tmp->node->key);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_rooms(t_lemin *l)
{
	ft_printf("PRINT_ROOMS\n");
	int	j;
	int	room_index;

	j = 0;
	room_index = -1;
	while (j < l->nb_rooms)
	{
		ft_printf("%s|\n", l->tab[j]->key);
		room_index = l->tab[j]->index;
		print_link2(l, room_index);
		j++;
	}
}

void	print_path(t_path *p)
{
	ft_printf("\nPRINT_PATH\n");
	t_path *tmp;

	tmp = p;
	while (tmp != NULL)
	{
		//ft_tmprintf("WHILE\n");
		ft_printf("->%s\n", tmp->node->key);
		tmp = tmp->next;
	}
	ft_printf("dist=%d\n", p->dist);
}

// void	print_result(t_lemin *l)
// {
// 	ft_printf("L%d-%s", ant, key);
// }