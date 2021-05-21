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
	int		infinity;
	int dist;
	t_point	pt;
	// int		start;
	// int		end;
	struct s_link *links;
	//t_room	r;
}				t_hashmap;

/*
** storing links in a adjacency list
*/
typedef struct s_link
{
	t_hashmap	*node;
	struct s_link	*next;
}				t_link;

typedef struct s_edge
{
	t_hashmap	*src;
	t_hashmap	*dst;
	struct s_edge	*next;
}				t_edge;

typedef struct	s_path
{
	// int		ant;
	// char	*key;
	// int		value; visited
	t_hashmap *node;
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
	int		read_ok[3];
	// t_room		start;
	// t_room		end;
	t_hashmap	*hm[SIZE];
	t_hashmap	*node_start;
	t_hashmap	*node_end;
	int			startend;
	t_hashmap	**tab;
	// char	*str_start;
	// char	*str_end;
}				t_lemin;

int				main(void);

/*
 ** parse.c
 */
int	read_map(t_lemin *l);
int	get_ants(char *line, t_lemin *l);
int	check_start_and_end(char *line, t_lemin *l);
int	check_room(char *line, t_lemin *l, t_hashmap **hm);
t_hashmap	*insert_item(t_hashmap **hm, char *key, t_point pt, int startend);
void	get_rooms(t_lemin *l);
int	check_link(char *line, t_lemin *l, t_hashmap **hm);
t_link *add_link(t_lemin *l, int i, int i2);

/*
 ** algo.c & algo2.c
 */
t_path *get_path2(t_lemin *l);//, t_hashmap *node)

/*
 ** utils.c & utils2.c
 */

/*
 ** free.c
 */
void			free_lemin(t_lemin *lemin);
// int				nbchar_string(char *s, char c);
t_hashmap		*room_exists(char *s, t_hashmap **hm);
int				hash(char *key);
int				error(int errnum);
t_hashmap	*init_hashmap_item(void);
void	free_hashmap_item(t_hashmap **item, char *key);

int	check_start_and_end(char *line, t_lemin *l);
void	get_start_and_end(t_lemin *l, t_hashmap *item);



int invalid_read(char *line, t_lemin *l);

// void	init_matrix(int ***matrix, int col, int row);
t_link	*new_link(t_lemin *l, int i);
t_hashmap *copy_item(t_lemin *l, int i);
t_path	*new_path(t_hashmap *hm);
t_path	*lstdel_path(t_path **head);
void	free_node(t_hashmap **node, char *key, t_link **head);
//delete
void	print_key(t_hashmap **hm);
void	print_link(t_lemin *l);
void	print_link2(t_lemin *l, int value);
void	print_rooms(t_lemin *l);
void	print_path(t_path *p);

int		algo(t_lemin *l);
#endif
