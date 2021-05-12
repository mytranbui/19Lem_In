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

/*
** rooms : vertices/nodes of the graph
** links : edges of the graph
*/


/*
 ** key	 = name of the room
 ** value = hash(key)
 ** pt	 = coords of the room
 */
typedef struct	s_hashmap
{
	char	*key;
	int		value;
	int		visited;
	t_point	pt;
	int		start;
	int		end;
	struct s_link *links;
	//t_room	r;
}				t_hashmap;

/*
** storing links in a adjacency list
*/
typedef struct s_link
{
	char		*s;
	t_hashmap	*hm;
	struct s_link	*next;
}				t_link;

typedef struct	s_path
{
	// int		ant;
	// char	*key;
	// int		value; visited
	t_hashmap *hm;
	struct s_path	*next;
}				t_path;

typedef struct s_lemin
{
	int			nb_ants;
	int			nb_rooms;
	int			nb_links; //useful?
	char		**rooms; //useful?
	int			adj_matrix[SIZE][SIZE];
	// int			**adj_matrix;
	int		start; //use?
	int		end;//use?
	// t_room		start;
	// t_room		end;
	t_hashmap	*hm[SIZE];
	t_hashmap	*hm_start;
	t_hashmap	*hm_end;
	// char	*str_start;
	// char	*str_end;
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
// int				nbchar_string(char *s, char c);
int				isdigitstr(char *s);
t_hashmap		*match_key(char *s, t_hashmap **hm);
int				hash(char *key);
int				error(int errnum);
t_hashmap	*init_hashmap_item(void);
void	free_hashmap_item(t_hashmap **item, char *key);

// void	init_matrix(int ***matrix, int col, int row);
t_link	*new_link(t_lemin *l, int i);

//delete
void	print_key(t_hashmap **hm);
void	print_link(t_lemin *l);
void	print_link2(t_lemin *l, int value);

int		algo(t_lemin *l);
#endif
