/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:53:46 by mbui              #+#    #+#             */
/*   Updated: 2021/05/06 13:36:28 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void free_lemin(t_lemin *lemin)
{
	free(lemin);
	lemin = NULL;
	exit(-1);
}

int	isdigitstr(char *s)
{
	//ft_printf("ISDIGITSTR\n");
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i++]))
			return (-1);
	}
	return (ft_atoi(s));
}

// int nbchar_string(char *s, char c)
// {
// 	int nb;
// 	int i;

// 	nb = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			nb++;
// 		i++;
// 	}
// 	return (nb);
// }

t_hashmap	*init_hashmap_item(void)
{
	t_hashmap	*item;

	item = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!item)
		return (NULL);
	item->key = NULL;
	item->value = 0;
	item->visited = -1;
	item->start = 0;
	item->end = 0;
	assign_pt(&item->pt, 0, 0);
	item->links = NULL;
	return (item);
}

void	free_hashmap_item(t_hashmap **item, char *key)
{
	ft_strdel(&key);
	key = NULL;
	if (item)
	{
		free(*item);
		*item = NULL;
	}
	item = NULL;
}

int	hash(char *key)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	while (key[i] != '\0')
		value = value + 6 * (key[i++] % 10 + 60);
	// ft_printf("hash_i = %d\n", value);
	value = value % SIZE;
	// ft_printf("hash_i = %d\n", value);
	return (value);
}

t_hashmap	*match_key(char *key, t_hashmap **hm)
{
	// ft_printf("~MATCH_KEY~\n");
	int	i;

	i = hash(key);
	// while(hm[i])
	// {
	// 	ft_printf("WHILE %d\n", i);
	// ft_printf("key=%s | h[%d]=%s", key, i, hm[i]->key);
	if (hm[i]->key && !ft_strcmp(hm[i]->key, key))
	{
		// ft_printf("FOUND KEY\n");
		ft_printf("FOUND KEY : h[%d]=%s	x=%d y=%d\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);

		return (hm[i]);
	}
	// 	i++;
	// 	i %= SIZE;
	// }
	// ft_printf("~MATCH_KEY~END\n");
	return (NULL);
}

int	error(int errnum)
{
	ft_printf("ERROR : ");
	if (errnum == 0)
		ft_printf("Invalid Argument");
	return (-1);
}

//add to libft
void	init_matrix(int ***matrix, int col, int row)
{
	int	i;
	int	j;
	
	j = 0;
	while (j < col)
	{
		i = 0;
		while (i < row)
		{
			*matrix[j][i] = 0;
			i++;
		}
		j++;
	}
	//return (matrix);
}

t_link	*new_link(t_lemin *l, int i)
{
	t_link *new;

	new = (t_link *)ft_memalloc(sizeof(t_link));
	if (!new)
		return (NULL);
	new->node = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!new->node)
		return (NULL);
	new->node = l->hm[i];
	new->next = NULL;
	return (new);
}