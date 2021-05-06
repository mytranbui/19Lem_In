/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:00:32 by mbui              #+#    #+#             */
/*   Updated: 2021/05/06 13:36:46 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define MAX_STRING 65535
# define SIZE 100
typedef struct s_room
{
	char	*name;
	t_point	pt;
	char	**link;
}				t_room;

/*
 ** key	 = name of the room
 ** value = hash(key)
 ** pt	 = coords of the room
 */
typedef struct	s_hashmap
{
	char	*key;
	int		value;
	t_point	pt;
	int		start;
	int		end;
	//t_room	r;
}				t_hashmap;

typedef struct s_lemin
{
	int			nb_ants;
	int			nb_rooms;
	char		**rooms;
	int			**adj_matrix;
	int		start;
	int		end;
	// t_room		start;
	// t_room		end;
	t_hashmap	*hm[SIZE];
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

/*
 ** free.c
 */
void			free_lemin(t_lemin *lemin);
int				nbchar_string(char *s, char c);
int				isdigitstr(char *s);
t_hashmap		*match_key(char *s, t_hashmap **hm);
int				hash(char *key);
int				error(int errnum);
t_hashmap	*init_hashmap_item(void);
void	free_hashmap_item(t_hashmap **item, char *key);
void	print_key(t_hashmap **hm);

#endif
