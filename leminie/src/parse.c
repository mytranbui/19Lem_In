/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:55:26 by mbui              #+#    #+#             */
/*   Updated: 2021/04/01 17:26:16 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	read_map(t_lemin *l)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 0;
	while (get_next_line(0, &line) > 0 && line)
	{
		ft_printf("[%s]\n", line);
		if (l->nb_ants == 0)
			ret = get_ants(line, l);
		else if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			ret = check_start_and_end(line, l);
		else if ((line[0] != '#') && (nb_word(line, ' ') == 3))
			ret = check_room(line, l, l->hm);
		else if ((line[0] != '#') && (nb_word(line, '-') == 2))
			ret = check_link(line, l, l->hm);
		else if (invalid_read(line, l) == 1 || line[0] != '#')
			return (ERR_LINE);
		if (ret != 1)
			return (ret);
		//if (line)
		ft_strdel(&line);
	}
	if (l->start == 0 || l->end == 0 || l->read_ok[2] == 0)
		return (ERR_LINE);
	return (1);
}