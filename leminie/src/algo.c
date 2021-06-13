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
// 	// ft_printf("%s%d",p->hm->key, p->hm->index);
// 	p->next = NULL;
// 	return (p);
// }

t_path	*add_path(t_path *head, t_node *node)
{
	//t_path	*head;
	t_path	*new;

	if (!node)
		return (NULL);
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
	ft_printf("dist++ %d\n", head->dist);
	return (head);
}

t_path *get_path3(t_lemin *l, t_path *p, int i)//,t_node *node)
{
	ft_printf("-------GET_PATH\n");
	t_node *tmp;
	// t_node *tmp2;
	// int tmpp;
	int tmpp2;
	t_link	*tmp_link;
	//int	index;

	// tmp2 = NULL;
	ft_printf("enter: l->hm[%d] = %s\n", i, l->hm[i]->key);
	if (i == l->node_end->index)
	{
		p = add_path(p, l->node_end);
		if (!p)
			return (NULL);
		ft_printf("BEEND\n");
		return (p);
	}
	l->hm[i]->visited = 1;
	tmp = l->hm[i]->links->node;
	// tmpp = l->hm[i]->links->node->index;
	tmp_link = l->hm[i]->links;
	while (tmp_link->next != NULL && tmp->visited == 1)//&& tmp->index != l->node_end->index)
	{
		ft_printf("tmp->%s\n", tmp->key);
		ft_printf("tmplink->%s\n", tmp_link->node->key);
			tmpp2 = tmp->index;
			tmp = tmp_link->next->node;
			if (tmp->index == tmpp2)
				return (lstdel_path(&p));
		ft_printf("lol\n");
	}
	ft_printf("BEvisited %s\n", l->hm[i]->key);
	ft_printf("BEvisited %s\n", tmp->key);
	ft_printf("BEindex %d\n", i);
	if (tmp->index == l->node_end->index)
	{
		p = add_path(p, l->node_end);
		if (!p)
			return (lstdel_path(&p));
		ft_printf("tmpEND\n");
		return (p);
	}
	while (tmp->links != NULL)
	{
		if (i == l->node_end->index)
		{
			p = add_path(p, l->node_end);
			if (!p)
				return (lstdel_path(&p));
			ft_printf("END\n");
			return (p);
		}
		if (tmp->visited == 0)
		{
			p = add_path(p, tmp);
			if (!p)
			return (lstdel_path(&p));
			if (tmp->index == l->node_end->index)
			{
				ft_printf("ifEND\n");
				return (p);
			}
			ft_printf("TMP RECUR\n");
			if (get_path3(l, p, tmp->index) != NULL)
				return (p);
		}
		i = tmp->links->node->index;
		tmp = tmp->links->next->node;
	}
	return (lstdel_path(&p));
}

void	get_info(t_lemin *l, int i, int i_prev)
{
	l->hm[i]->visited = 1;
	l->hm[i]->prev_index = i_prev;
	l->hm[i]->dist++;
	ft_printf("%s visited%d prev%s dist%d\n", l->hm[i]->key, l->hm[i]->visited, l->hm[l->hm[i]->prev_index]->key, l->hm[i]->dist);
}

t_link	*skip(t_lemin *l, t_node *node)
{
	t_link * tmp;


	tmp = node->links;
	ft_printf("SKIP\n");
	while (tmp->next != NULL)
	{
	ft_printf("SKIP\n");
		if (l->hm[node->index]->prev_index != -1)
		{
	 		tmp = tmp->next;
	return (tmp);
		}
	}
	ft_printf("SKIPEND\n");
	return (tmp);
}

int	get_path4(t_lemin *l, int i)//, t_link *link)
{
		ft_printf("PATH4\n");

	t_link *tmp_link;
	//t_link *tmp_link2;
	// t_node *tmp2;
	int	tmp_index;

	tmp_index = i;
	tmp_link = l->hm[i]->links;
	// tmp2 = tmp_link;
	while (tmp_link != NULL)// && i != l->node_end->index)
	{
		get_info(l, tmp_link->node->index, i);
			if (i == l->node_end->index) 
					return (1);
			// print_key(l, tmp_index);
			if (tmp_link->next != NULL)
			ft_printf("yup\n");
			if (tmp_link->next != NULL)
			// print_key(l, tmp_link->next->node->index);
			ft_printf("here\n");
			if (tmp_link->next && tmp_link->next->node->index == tmp_index)
				ft_printf("SAME\n");
			if (!tmp_link->next)
			{
			ft_printf("there\n");
				i = tmp_link->node->index;
				tmp_link = tmp_link->node->links;
				if (get_path4(l, i))
					return (1);
			}
			// if (tmp_link->node->links)
			// {
			// 	if (get_path4(l, tmp_link->node->index))
			// 		return (1);
			// 	// i = tmp_link->node->index;
			// 	// tmp_link = tmp_link->node->links;
			// }
			tmp_index = tmp_link->node->index;
			tmp_link = tmp_link->next;
			ft_printf("lol\n");
	}
	ft_printf("END\n");
	return (0);
}

// void algoo(t_lemin *l, int i)
// {
// 	t_link *tmp_link;
	
// 	tmp_link = l->hm[i]->links;
// 	while (i != l->node_end->index)
// 	{
// 		get_path4(l, i, tmp_link);
// 		tmp_link = l->hm[i]->links->node->links;
// 	}
// }

t_path	*algo2(t_lemin *l)
{
	t_path	*head;

	head = new_path(l->node_start);
	if (!head)
		return (NULL);
	// head = add_path(head, NULL);
	// if (!head)
	// 	return (NULL);
	head = get_path3(l, head, l->node_start->index);
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

// int	shortest_path(t_lemin *l)
// {
// 	int	i;
// 	int dist;

// 	i = 0;
// 	dist = l->nb_rooms;
// 	while (l->pp[i] != NULL)
// 	{
// 		if (dist > l->pp[i]->dist)
// 			dist = l->pp[i]->dist;
// 		i++;
// 	}
// 	i = 0;
// 	while (l->pp[i] != NULL)
// 	{
// 		if (dist == l->pp[i]->dist)
// 			return (i);
// 		i++;
// 	}
// }

// void	sol(t_lemin *l)
// {
// 	int nb;
// 	int i;

// 	nb = ft_min(l->nb_ants, l->nb_paths);
// 	if (l->nb_ants < l->nb_paths)
// 	{
// 		shortest_path(l->pp);
// 	}
// 	while (i < l-.nb_a)
// 	{
// 		ft_printf("L%d-%s", ant, key);
// 	}
// 	while (l->pp[i] < l->nb_paths)
// 	{



// 	}
// }

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
	ft_printf("%s%d",p[0]->node->key, p[0]->node->index);
	ft_printf("%s%d",p[1]->node->key, p[1]->node->index);
	return (1);
}