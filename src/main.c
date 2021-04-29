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
	close(fd);
	return (1);
}

t_lemin	*init_lemin(void)
{
	t_lemin	*l;

	l = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	if (!l)
		return (NULL);
	l->nb_ants = 0;
	l->nb_rooms = 0;
	l->rooms = NULL;
	// ft_bzero(hm, SIZE);
	// ft_bzero(&hm, SIZE);
	return (l);
}

// t_room	*init_room(void)
// {
// 	t_room	*r;

// 	r = (t_room *)ft_memalloc(sizeof(t_room));
// 	if (!r)
// 		return (NULL);
// 	r->name = NULL;
// 	r->link = NULL;
// 	assign_pt(&r->pt, 0, 0);
// 	return (r);
// }

// t_room	*get_room(char *line)
// {
// 	char	**info;
// 	t_room	*r;

// 	info = NULL;
// 	r = init_room();
// 	if (nbchar_string(line, ' ') != 2)
// 		return (NULL);
// 	info = ft_strsplit(line, ' ');
// 	if (!info)
// 		return (NULL);
// 	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
// 	{
// 		info = free_tab(info, 2);
// 		return (NULL);
// 	}
// 	r->name = ft_strdup(info[0]);
// 	if (!r->name)
// 		return (NULL);
// 	r->pt.x = ft_atoi(info[1]);
// 	r->pt.y = ft_atoi(info[2]);
// 	info = free_tab(info, 2);
// 	ft_printf("room=%s x=%d y=%d\n", r->name, r->pt.x, r->pt.y);
// 	return (r);
// }

void	insert_item(t_hashmap **hm, char *key, int x, int y)
{
	// ft_printf("~INSERT~\n");
	t_hashmap	*item;
	int	i;

	i = hash(key);
	item = init_hashmap_item();
	if (!item)
		return ;
	item->key = ft_strdup(key);
	if (!item->key)
		return ;
	item->pt.x = x;
	item->pt.y = y;
	// while (hm[i] != NULL)// && hm[i]->key != NULL)
	// {
	// 	ft_printf("NEXT CELL\n");
	// 	i++;
	// 	// i %= SIZE;
	// }
	hm[i] = item;
	ft_printf("h[%d]=%s x=%d y=%d		====>i=%d	%s\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y, i, hm[i]->key);
	//free_hashmap_item(&item), item->key);
	//if free can't print so free after?
	// ft_printf("~INSERT~OK\n");
}

int	check_room(char *line, t_hashmap **hm)
{
	// ft_printf("~CHECK_ROOM~\n");
	char	**info;

	info = NULL;
	// if (nbchar_string(line, ' ') != 2)
	// 	return (-1);
	info = ft_strsplit(line, ' ');
	if (!info)
		return (-1);
	if (isdigitstr(info[1]) == -1 || isdigitstr(info[2]) == -1)
	{
		info = free_tab(info, 2);
		return (-1);
	}
	insert_item(hm, info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	ft_printf("room[%s] x[%d] y[%d]\n", info[0], ft_atoi(info[1]), ft_atoi(info[2]));
	info = free_tab(info, 2);
	// ft_printf("~CHECK_ROOM~OK\n");
	return (1);
}

void	get_link(char *line)//, t_hashmap **hm)
{
	ft_printf("~GET_LINK~\n");
	ft_printf("%s\n", ft_strcsub(line, 0, '-'));
}

int	check_link(char *line, t_hashmap **hm)
{
	// ft_printf("~CHECK_LINK~\n");
	char	**info;

	info = ft_strsplit(line, '-');
	if (!info)
		return (-1);
	ft_printf("s1[%s]-s2[%s]\n", info[0], info[1]);
	if (!match_key(info[0], hm) || !match_key(info[1], hm))
	{
		ft_printf("MATCH_KEY ERROR\n");
		return (-1);
	}
	// ft_printf("~CHECK_LINK~OK\n");
	get_link(line);
	info = free_tab(info, 1);
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

	start = 0;
	end = 0;
	// if ((ft_read(0)) == -1)
	// {
	// 	ft_putendl("ERROR");
	// 	return (-1);
	// }
	l = init_lemin();
	if (!l)
		return (-1);
	if (!(get_next_line(0, &line)))
		return (-1);
	// ft_printf("[%s]\n", line);
	if (l->nb_ants == 0)
		l->nb_ants = isdigitstr(line);
	if (l->nb_ants == -1)
		free_lemin(l);
	ft_printf("ANTS[%d]\n", l->nb_ants);
	if (line)
		ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("[%s]\n", line);
		if (line && !ft_strcmp(line, "##start"))
		{
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
			if (nb_word(line, ' ') == 3)
			{
				if (check_room(line, l->hm) == -1)
					return (-1);
			}
			else if (nb_word(line, '-') == 2)
			{
				if (check_link(line, l->hm) == -1)
					return (-1);
				
			}
		}
		if (line)
			ft_strdel(&line);
	}
	ft_printf("start=%d end=%d\n", start, end);
				print_key(l->hm);
	if (start == 0 || end == 0)
		return (-1);
	return (0);
}