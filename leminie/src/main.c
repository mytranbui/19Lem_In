/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <mbui@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:22:10 by mbui              #+#    #+#             */
/*   Updated: 2021/05/06 13:36:17 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	ft_read(int fd)
{
	char	*file;
	int		ret;

	file = ft_strnew(MAX_STRING + 1);
	if (!file)
		return (-1);
	if ((ret = read(fd, file, MAX_STRING + 1)) <= 0 || ret > MAX_STRING)
	{
		ft_strdel(&file);
		return (-1);
	}
	//ft_bzero(file, MAX_STRING);
	ft_strdel(&file);
	close(fd);
	return (1);
}

t_lemin	*init_lemin(void)
{
	t_lemin	*l;
	int	j;

	l = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	if (!l)
		return (NULL);
	l->nb_ants = 0;
	l->nb_rooms = 0;
	l->nb_links = 0;
	l->rooms = NULL;
	l->start = 0;
	l->end = 0;
	l->i_start = 0;
	l->i_end = 0;
	l->read_ok[0] = 0;
	l->read_ok[1] = 0;
	l->read_ok[2] = 0;
	j = 0;
	while (j < SIZE)
	{
		l->hm[j++] = NULL;
	}
	l->node_start = (t_node *)ft_memalloc(sizeof(t_node));
	if (!l->node_start)
		return (NULL);
		l->node_end = (t_node *)ft_memalloc(sizeof(t_node));
	if (!l->node_end)
		return (NULL);
	l->tab = NULL;
	l->startend = 0;
	return (l);
}

/*
** Room will never start with the character 'L' nor the character '#'
*/
int	main(void)
{
	t_lemin	*l;
	int	ret;

	ret = 0;
	// if ((ft_read(0)) == -1)
	// {
	// 	ft_putendl("ERROR");
	// 	return (-1);
	// }
	// ft_printf("READ OK\n");
	l = init_lemin();
	if (!l)
		return (-1);
	ret = read_map(l);
	if (ret != 1)
		return (error(ret));
	ft_printf("nb_ants:	%d\n", l->nb_ants);
	ft_printf("nb_rooms:	%d\n", l->nb_rooms);
	ft_printf("nb_links:	%d\n", l->nb_links);
	ft_printf("start:	%d end:	%d\n", l->start, l->end);
	// print_key(l->hm);
	// // print_link(l);
	get_rooms(l);
	// algoo(l, l->node_start->index);
	get_path4(l, l->node_start->index);
	// get_mult_path(l);
	// while (l->pp[i] != NULL)
	//	print_path(l->pp[i++]);
	// bfs(l);
	return (0);
}
