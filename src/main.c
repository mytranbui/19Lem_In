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

void	init_filler(t_filler *f)
{
	assign_pt(&f->me.init, -1, -1);
	assign_pt(&f->opp.init, -1, -1);
	f->nb_piece = 0;
}

char	*ft_read(int fd)
{
	char	*file;
	int		ret;
	int		i;

	if (!(file = ft_strnew(MAX_STRING + 1)))
		return (NULL);
	if ((ret = read(fd, file, MAX_STRING + 1)) <= 0 || ret > MAX_STRING)
	{
		ft_strdel(&file);
		return (NULL);
	}
	i = -1;
	while (file[++i])
		if (file[i] != '#' && file[i] != '\n' && file[i] != '.')
		{
			ft_strdel(&file);
			return (NULL);
		}
	if (link_count(file) == 1)
	{
		ft_strdel(&file);
		return (NULL);
	}
	return (file);
}

int	main(void)
{
	t_lemin	*l;
	char	*file;
	int		fd;

	// if (argc != 2)
	// {
	// 	ft_putendl("usage: ./fillit [file]");
	// 	return (-1);
	// }
	l = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	if (!l)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if ((file = ft_read(fd)) == NULL)
	{
		ft_putendl("ERROR");
		return (-1);
	}
	if ((tetro = stock(file)) == NULL)
	{
		ft_putendl("ERROR");
		return (-1);
	}
	if ((get_solv(tetro)) == -1)
		return (-1);
	return (0);
}
