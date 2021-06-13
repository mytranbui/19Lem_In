/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:00:32 by mbui              #+#    #+#             */
/*   Updated: 2021/06/04 12:10:01 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define MAX_STRING 65535
# define SIZE 2000

# define ERR_MAP 100
# define ERR_LINE	-2
# define ERR_ANTS	-3
# define ERR_ROOMS	-4
# define ERR_LINKS	-5
# define ERR_PATH	-6

/*
** rooms : vertices/nodes of the graph
** links : edges of the graph
*/


/*
 ** key	 = name of the room
 ** index = index in the hashmap, hash(key) 
 ** pt	 = coords of the room
 */
typedef struct	s_node
{
	char	*key;
	int		index;
	int		visited;
	int		dist;
	int		prev_index;
	t_point	pt;
	// int		start;
	// int		end;
	struct s_link *links;
	struct s_link2 *links2;
}				t_node;

/*
** storing links in a adjacency list
*/
typedef struct s_link
{
	t_node	*node;
	// int		index;
	int		nb;
	struct s_link	*next;
}				t_link;

typedef struct s_edge
{
	t_node	*src;
	t_node	*dst;
	struct s_edge	*next;
}				t_edge;

typedef struct s_queue
{
	int			*queue;
	int			*visited;
	int			*prev;
	int			length;
	int			position;
	int			**flow;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_path
{
	int		ant;
	char	*key;
	int		dist;
	// int		index; visited
	t_node *node;
	struct s_path	*next;
}				t_path;


/*
** hm[SIZE] : storing nodes/vertices in an hashmap
*/
typedef struct s_lemin
{
	int			nb_ants;
	int			nb_rooms;
	int			nb_links; //useful?
	char		**rooms; //useful?
	int			start;
	int			end;
	int			read_ok[3];
	t_node		*hm[SIZE];
	t_node		*node_start;
	t_node		*node_end;
	int			i_start;
	int			i_end;
	int			startend;
	t_node	**tab;
	t_path		**pp;
	int			nb_paths;
}				t_lemin;

int				main(void);

/*
 ** parse.c
 */
int	read_map(t_lemin *l);
int	get_ants(char *line, t_lemin *l);
int	check_start_and_end(char *line, t_lemin *l);
int	check_room(char *line, t_lemin *l, t_node **hm);
t_node	*insert_item(t_node **hm, char *key, t_point pt, int startend);
void	get_rooms(t_lemin *l);
int	check_link(char *line, t_lemin *l, t_node **hm);
t_link *add_link(t_lemin *l, int i, int i2);

/*
 ** algo.c & algo2.c
 */
t_path *get_path2(t_lemin *l);//, t_node *node)
t_path	*get_path3(t_lemin *l, t_path *p,int i);//, t_node *node)
t_path	*algo2(t_lemin *l);
/*
 ** utils.c & utils2.c
 */

/*
 ** free.c
 */
void			free_lemin(t_lemin *lemin);
// int				nbchar_string(char *s, char c);
t_node		*room_exists(char *s, t_node **hm);
int				hash(char *key);
t_node	*init_node_item(void);
void	free_hashmap_item(t_node **item, char *key);

void	get_start_and_end(t_lemin *l, int i);



int invalid_read(char *line, t_lemin *l);

// void	init_matrix(int ***matrix, int col, int row);
t_link	*new_link(t_lemin *l, int i);
t_node *copy_item(t_lemin *l, int i);
t_path	*new_path(t_node *hm);
t_path	*lstdel_path(t_path **head);
void	free_node(t_node **node, char *key, t_link **head);
//delete
void	print_key(t_node **hm);
void	print_link(t_lemin *l);
void	print_link2(t_lemin *l, int index);
void	print_rooms(t_lemin *l);
void	print_path(t_path *p);

int		algo(t_lemin *l);
void	get_mult_path(t_lemin *l);

int	error(int errnum);
t_path *bfs(t_lemin *l);//, t_node start, t_node end);
t_path	*add_path(t_path *head, t_node *node);
t_node *copy_node(t_node *node);
void	get_path4(t_lemin *l, int i);//, t_link * link);
// void algoo(t_lemin *l, int i);
#endif
