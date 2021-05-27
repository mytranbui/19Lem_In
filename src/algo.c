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

// void	add_edge()
// {

// }

// t_path	*init_path(t_lemin *l)
// {
// 	t_path	*p;

// 	p = (t_path *)ft_memalloc(sizeof(t_path));
// 	if (!p)
// 		return (NULL);
// 	// p->key = l->str_start;//hm
// 	// p->hm = l->hm[l];
// 	p->node = init_node_item();
// 	if (!p->node)
// 		return (NULL);
// 	p->node = l->node_start;
// 	// ft_printf("%s%d",p->hm->key, p->hm->value);
// 	p->next = NULL;
// 	return (p);
// }

int get_path3(t_lemin *l, int i)//,t_node *node)
{
	ft_printf("-------GET_PATH\n");
	t_node *tmp;
	t_link	*tmp_link;                                                                                                                                                                                                                                                                                                                                                                                                                                 
	//int	value;

	if (i == l->node_end->value)
			ft_printf("BEEND\n");
	l->hm[i]->visited = 1;
	printf("Visited %d \n", l->hm[i]->visited);
	tmp = l->hm[i]->links->node;
	tmp_link = l->hm[i]->links;
	while (tmp->visited == 1 && tmp_link != NULL)
	{
		tmp = tmp_link->next->node;
	}
	ft_printf("BEvisited %s\n", l->hm[i]->key);
	ft_printf("BEvisited %s\n", tmp->key);
	ft_printf("BEvalue %d\n", i);
	// tmp = node->links;
	// value = tmp->node->value;
	if (tmp->value == l->node_end->value)
	{
			ft_printf("tmpEND\n");
			return (1);
	}
	if (i == l->node_end->value)
	{
			ft_printf("BEEND\n");
			return (1);
	}
	while (tmp->links != NULL)
	{
		printf("WHILE\n");
		ft_printf("wvisited %s\n", l->hm[i]->key);
		ft_printf("wvalue %d\n", i);
		if (l->hm[i]->visited == 0)// && tmp->visited == 1)
		{
			//l->hm[value]->visited = 1;
			ft_printf("ifvisited %s\n", l->hm[i]->key);
			ft_printf("ifvalue %d\n", i);
			if (i == l->node_end->value)
			{
			ft_printf("ifEND\n");
				return(1);
			}
			if (get_path3(l, i) == 1)
				return(1);
		}
		else if (tmp->visited == 0)
		{
			ft_printf("TMP RECUR\n");
			if (get_path3(l, tmp->value)==1)
				return (1);
		}
		if (i == l->node_end->value)
		{
			ft_printf("END\n");
				return(1);
			}
		i = tmp->links->node->value;
		tmp = tmp->links->next->node;
	}
	return (-1);
}

t_path *get_path2(t_lemin *l)//, t_node *node)
{
	ft_printf("ADD_path\n");
	t_path	*head;
	t_path	*new;
	t_node *tmp;

	tmp = copy_item(l, l->node_start->value);
	if (!tmp)
		return (NULL);
	head = new_path(l->node_start);
	if (!head)
		return (NULL);
	new = head;
	free_node(&tmp, tmp->key, &tmp->links);
		ft_printf("tmp=%s\n", new->node->key);
		tmp = copy_item(l, new->node->links->node->value);

		ft_printf("tmp=%s\n", new->node->key);
	if (tmp != l->node_end)
		ft_printf("tmp=%s\n", new->node->key);

	while (tmp != l->node_end)
	{
		ft_printf("WHILE\n");
		tmp = new->node->links->node;
		// if (new->node == l->node_end)
		// 	return (head);
		ft_printf("tmp=%s\n", tmp->key);
		if (tmp->visited != 0)
		{
			ft_printf("IF\n");
			tmp->visited = 1;
			new->next = new_path(tmp);
			if (!new->next)
			return (lstdel_path(&head));
		}
		//new = new->next;
	}
	new->next = NULL;
	// ft_printf("hm[%d]%s->%s\n", i, l->hm[i]->key, l->hm[i]->paths->node->key);
	// ft_printf("ADD_path~OK\n");
	 return (head);
}

int algo(t_lemin *l)
{
	t_path **p;
	int		i;

	i = 0;
	p = (t_path **)ft_memalloc(sizeof(t_path *) * l->nb_ants);
	if (!p)
		return (-1);
	// while (i < l->nb_ants)
	// {
		// p[i++] = init_path(l);
	// }
	ft_printf("%s%d",p[0]->node->key, p[0]->node->value);
	ft_printf("%s%d",p[1]->node->key, p[1]->node->value);
	return (1);
}