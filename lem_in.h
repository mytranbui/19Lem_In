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

/*
** w = width & h = height
*/
typedef struct s_object
{
	int		w;
	int		h;
	int		nb;
	char	**tab;
}				t_object;

typedef struct s_lemin
{
	int		nb_ants;
	t_room	start;
	t_room	end;
	t_object	piece;
	t_object	map;
	int			nb_piece;
}				t_lemin;

int				main(void);

/*
** parse.c
*/
int				get_player(t_lemin *f);
void			get_map(t_lemin *f, char *line);
void			get_piece(t_lemin *f, char *line);
void			fill_object(t_object *o, unsigned int start);
void			find_start(t_lemin *f);

/*
** algo.c & algo2.c
*/
void			which_algo(t_lemin *f);
int				check_place(t_lemin *f, int j, int i);
int				possible_sp_no(t_lemin *f);
int				possible_sp_ne(t_lemin *f);
int				possible_sp_se(t_lemin *f);
int				possible_sp_so(t_lemin *f);
int				possible_sp_last(t_lemin *f);

int				possible_sp_no2(t_lemin *f);
int				possible_sp_ne2(t_lemin *f);
int				possible_sp_se2(t_lemin *f);
int				possible_sp_so2(t_lemin *f);

/*
** utils.c & utils2.c
*/
void			init_object(t_object *o);
t_point			*assign_pt(t_point *p, int x, int y);
void			get_nb_chartab(t_object *o, char c);
void			place(t_lemin *f, int j, int i);
void			free_tabs(t_lemin *f);

int				touch_border_right(t_lemin *f);
int				touch_border_left(t_lemin *f);
void			print_tab(t_object *o);
#endif
