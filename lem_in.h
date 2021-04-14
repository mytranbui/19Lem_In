/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:00:32 by mbui              #+#    #+#             */
/*   Updated: 2021/04/08 18:49:11 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <fcntl.h> //use for open() ?
# define MAX_STRING 65535
typedef struct s_room
{
	char	*name;
	t_point	pt;
	char	**link;
}				t_room;

// /*
// ** w = width & h = height
// */
// typedef struct s_object
// {
// 	int		w;
// 	int		h;
// 	int		nb;
// 	char	**tab;
// }				t_object;

typedef struct s_lemin
{
	int		nb_ants;
	t_room	start;
	t_room	end;
}				t_lemin;

int				main(void);

/*
** parse.c
*/

/*
** algo.c & algo2.c
*/

/*
** utils.c & utils2.c
*/
void free_lemin(t_lemin *lemin);
#endif
