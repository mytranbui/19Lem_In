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
# define MAX_STRING 65535
# define SIZE 2000
typedef struct s_room
{
	char	*name;
	t_point	pt;
	char	**link;
}				t_room;

typedef struct s_lemin
{
	int		nb_ants;
	char	**rooms;
	t_room	start;
	t_room	end;
}				t_lemin;


/*
** key = name of the room
** value =
*/
typedef struct	s_hashmap
{
	char	*key;
	int		value;
	t_point	pt;
	//t_room	r;
}				t_hashmap;

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

/*
** free.c
*/
void			free_lemin(t_lemin *lemin);
int				nbchar_string(char *s, char c);
int				char_in_string(char *s, char c);
int				isdigitstr(char *s);
t_hashmap		*match_key(char *s, t_hashmap **hm);
#endif
