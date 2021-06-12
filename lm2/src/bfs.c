/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:21:50 by mbui              #+#    #+#             */
/*   Updated: 2021/06/04 12:10:26 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path	*bfs(t_lemin *l)//, t_node start, t_node end)
{
	ft_printf("BFS\n");
	int step;
	int i;
	int j;
	t_path	*head;
	t_link	*tmp_link;

	step = 0;
	i = 0;
	head = new_path(l->node_start);
	if (!head)
		return (NULL);
	tmp_link = l->node_start->links;
				ft_printf("]%d[\n", tmp_link->node->visited);

	// tmp_link = copy_link(l->node_start->links);
	ft_printf("BFS\n");
	j = 0;
	while (l->tab[j])
	{
		ft_printf("while1\n");
		i = 0;
		step++;
		while (i < SIZE)
		{
		ft_printf("while2\n");
			tmp_link = l->hm[i]->links;
				ft_printf("]%d[\n", tmp_link->node->visited);

		ft_printf("while2\n");

			if (i == l->node_end->index)
			{
				ft_printf("end\n");
				
				head = add_path(head, l->node_end);
				if (!head)
			return (NULL);
				return (head);
			}
			while (tmp_link)//->next)
			{
				ft_printf("link\n");
				ft_printf("]%d[\n", tmp_link->node->visited);
				if (tmp_link->node->visited == 0)
				{
					//l->hm[i]->visited = 1;
			// 		head = add_path(head, l->hm[i]->node);
			// 		if (!head)
			// return (NULL);
					ft_printf("node=%s\n", tmp_link->node->key);
					tmp_link->node->visited = 1;
					
					head = add_path(head, tmp_link->node);
					if (!head)
			return (NULL);

				}
				tmp_link = tmp_link->next;
			}
			tmp_link = l->hm[i]->links;

			i++;
		}
		j++;

	}
	return (NULL);
}
