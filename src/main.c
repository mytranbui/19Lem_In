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

t_room	*init_room(void)
{
	t_room	*r;

	r = (t_room *)ft_memalloc(sizeof(t_room));
	if (!r)
		return (NULL);
	r->name = NULL;
	r->link = NULL;
	assign_pt(&r->pt, 0, 0);
	return (r);
}

void	init_lemin(t_lemin *l)
{
	l->nb_ants = 0;
	l->rooms = NULL;
}

t_room	*get_room(char *line)
{
	char	**info;
	t_room	*r;

	info = NULL;
	r = init_room();
	if (nbchar_string(line, ' ') != 2)
		return (NULL);
	info = ft_strsplit(line, ' ');
	if (!info)
		return (NULL);
	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (NULL);
	}
	r->name = ft_strdup(info[0]);
	if (!r->name)
		return (NULL);
	r->pt.x = ft_atoi(info[1]);
	r->pt.y = ft_atoi(info[2]);
	info = free_tab(info, 2);
	ft_printf("room=%s x=%d y=%d\n", r->name, r->pt.x, r->pt.y);
	return (r);
}

int	hash(char *key)
{
	char *k;
	k = key;
	int	value;
	int	i;
	
	i = 0;
	value = 0;
	while (key[i] != '\0')
		value = value + 6 * (key[i++] % 10 + 60);
	ft_printf("value = %d\n", value);
	value = value % 200;
	ft_printf("value = %d\n", value);
	return (value);
}

void	insert_item(t_hashmap **h, char *key, int x, int y)
{
	t_hashmap	*item;
	int	i;

	i = hash(key);
	item = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!item)
		return ;
	item->key = key;
	item->pt.x = x;
	item->pt.y = y;
	h[i] = item;
	ft_printf("h[%d]=%s x=%d y=%d\n", i, h[i]->key, h[i]->pt.x, h[i]->pt.y);
	//delete hash item fct
	//return ();
}

int	check_room(char *line, t_hashmap **h)
{
	char	**info;
	char	*name;

	info = NULL;
	name = NULL;
	if (nbchar_string(line, ' ') != 2)
		return (-1);
	info = ft_strsplit(line, ' ');
	if (!info)
		return (-1);
	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (-1);
	}
	name = ft_strdup(info[0]);
	if (!name)
		return (-1);
	insert_item(h, name, ft_atoi(info[1]), ft_atoi(info[2]));
	ft_printf("room=%s x=%d y=%d\n", name, ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	return (1);
}

/*
** Room will never start with the character 'L' nor the character '#'
*/
int	main(void)
{
	t_lemin	*l;
	char	*line;
	int		start;
	int		end;
	t_hashmap	*h[SIZE];

	start = 0;
	end = 0;
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
		l->nb_ants = isdigitstr(line);
	if (l->nb_ants == -1)
		free_lemin(l);
	ft_printf("[%d]\n", l->nb_ants);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("[%s]\n", line);
		if (line && !ft_strcmp(line, "##start"))
		{
			ft_printf("start\n");
			start++;
		}
		if (line && !ft_strcmp(line, "##end"))
		{
			end++;
		}
		if (line[0] == 'L' || start > 1 || end > 1)
			return (-1);
		if (line[0] != '#')
		{
			if (check_room(line, h) == -1)
				return (-1);
			// if (get_room(line) == NULL)
				// return (-1);
			// if (char_in_string(line, '-') == 1) //check first str match with one room --?hash check
			// 	get_link();
		}
		if (line)
			ft_strdel(&line);
	}
	ft_printf("s=%d e=%d\n", start, end);
	if (start == 0 || end == 0)
		return (-1);
	return (0);
}
