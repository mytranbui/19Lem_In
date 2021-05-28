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

t_path	*add_path(t_path *head, t_node *node)
{
	//t_path	*head;
	t_path	*new;

	//head = NULL;
	// if (!head)
	// {
	// 	head = new_path(l->node_start);
	// 	if (!head)
	// 		return (NULL);
	// }
	// else
	// {
		new = head;
		while (new->next != NULL)
			new = new->next;
		new->next = new_path(node);
		ft_printf("new %s\n", new->key);
		ft_printf("new->next %s\n", new->next->key);
		if (!new->next)
			return (NULL);
	// }
	head->dist++;
	return (head);
}

t_path *get_path3(t_lemin *l, t_path *p, int i)//,t_node *node)
{
	ft_printf("-------GET_PATH\n");
	t_node *tmp;
	t_node *tmp2;
	t_link	*tmp_link;
	//int	value;

	tmp2 = NULL;
	ft_printf("enter: l->hm[%d] = %s\n", i, l->hm[i]->key);
	if (i == l->node_end->value)
	{
		p = add_path(p, l->node_end);
		if (!p)
			return (NULL);
		ft_printf("BEEND\n");
		return (p);
	}
	l->hm[i]->visited = 1;
	tmp = l->hm[i]->links->node;
	tmp_link = l->hm[i]->links;
	while (tmp_link->next != NULL && tmp->visited == 1 && tmp->value != l->node_end->value)
	{
		// ft_printf("tmp->%s\n", tmp->key);
		// ft_printf("tmplink->%s\n", tmp_link->node->key);
			tmp2 = tmp;
			tmp = tmp_link->next->node;
			if (tmp == tmp2)
				return (lstdel_path(&p));
	}
	// ft_printf("BEvisited %s\n", l->hm[i]->key);
	// ft_printf("BEvisited %s\n", tmp->key);
	// ft_printf("BEvalue %d\n", i);
	if (tmp->value == l->node_end->value)
	{
		p = add_path(p, l->node_end);
		if (!p)
			return (lstdel_path(&p));
		ft_printf("tmpEND\n");
		return (p);
	}
	while (tmp->links != NULL)
	{
		// printf("WHILE\n");
		// ft_printf("wvisited %s\n", l->hm[i]->key);
		// ft_printf("wvalue %d\n", i);
		if (l->hm[i]->visited == 0)// && tmp->visited == 1)
		{
			// ft_printf("ifvisited %s\n", l->hm[i]->key);
			// ft_printf("ifvalue %d\n", i);
			if (i == l->node_end->value)
			{
				p = add_path(p, l->node_end);
				if (!p)
				return (lstdel_path(&p));
				ft_printf("ifEND\n");
				return (p);
			}
			p = add_path(p, tmp);
			if (!p)
			return (lstdel_path(&p));
			if (get_path3(l, p, i) != NULL)
				return (p);
		}
		else if (tmp->visited == 0)
		{
			p = add_path(p, tmp);
			if (!p)
			return (lstdel_path(&p));
			ft_printf("TMP RECUR\n");
			if (get_path3(l, p, tmp->value) != NULL)
				return (p);
		}
		// if (i == l->node_end->value)
		// {
		// 	p = add_path(p, l->node_end);
		// 	if (!p)
		// 		return (lstdel_path(&p));
		// 	ft_printf("END\n");
		// 	return (p);
		// }
		i = tmp->links->node->value;
		tmp = tmp->links->next->node;
	}
	return (lstdel_path(&p));
}

t_path	*algo2(t_lemin *l)
{
	t_path	*head;

	head = new_path(l->node_start);
	if (!head)
		return (NULL);
	// head = add_path(head, NULL);
	// if (!head)
	// 	return (NULL);
	head = get_path3(l, head, l->node_start->value);
	if (!head)
		return (NULL);
	return (head);
}

void	get_mult_path(t_lemin *l)
{
	int i;

	i = 0;
	l->pp = (t_path **)ft_memalloc(sizeof(t_path *) * l->nb_rooms);
	if (!l->pp)
		return ;
	while (i < l->nb_rooms)
	{
		ft_printf("pp[%d]\n", i);
		l->pp[i] = algo2(l);
		if (!l->pp[i])
			return ;
		i++;
	}
	return ;
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