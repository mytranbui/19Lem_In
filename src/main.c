/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <mbui@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:22:10 by mbui              #+#    #+#             */
/*   Updated: 2021/04/01 17:26:02 by mbui             ###   ########.fr       */
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
	return (1);
}

int	get_nb_ants(char *line)
{
	ft_printf("GET_ANTS\n");
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i++]))
			return (-1);
	}
	return (ft_atoi(line));
}

void	init_room(t_room *r)
{
	r->name = NULL;
	r->link = NULL;
	assign_pt(&r->pt, 0, 0);
}

t_room	*get_room(char *line)
{
	t_room	*r;

	init_room(r);
	r->name = ft_strtrim(line);
	r->pt.x = ft_atoi(ft_strchr(line, ' '));
	r->pt.y = ft_atoi(ft_strrchr(line, ' '));
	ft_printf("room=%s x=%d y=%d\n", r->name, r->pt.x, r->pt.y);
	return (r);
}

void	init_lemin(t_lemin *l)
{
	l->nb_ants = 0;
}

int	main(void)
{
	t_lemin	*l;
	char	*line;

	// if ((ft_read(0)) == -1)
	// {
	// 	ft_putendl("ERROR");
	// 	return (-1);
	// }
	l = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	if (!l)
		return (-1);
	init_lemin(l);
	if (!(get_next_line(0, &line)))
		return (-1);
	ft_printf("[%s]\n", line);
	if (l->nb_ants == 0)
		l->nb_ants = get_nb_ants(line);
	if (l->nb_ants == -1)
		free_lemin(l);
	ft_printf("[%d]\n", l->nb_ants);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		if (line && !ft_strcmp(line, "##start"))
		if (line && !ft_strcmp(line, "##end"))
		if (line)
			ft_strdel(&line);
	}
	return (0);
}
