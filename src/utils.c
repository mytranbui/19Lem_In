/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:53:46 by mbui              #+#    #+#             */
/*   Updated: 2021/03/29 10:23:04 by mbui             ###   ########.fr       */
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

int nbchar_string(char *s, char c)
{
  int nb;
  int i;

  nb = 0;
  i = 0;
  while (s[i])
  {
    if (s[i] == c)
      nb++;
    i++;
  }
  return (nb);
}

t_hashmap	*init_hashmap_item(void)
{
	t_hashmap	*item;

	item = (t_hashmap *)ft_memalloc(sizeof(t_hashmap));
	if (!item)
		return (NULL);
	item->key = NULL;
	item->value = 0;
	assign_pt(&item->pt, 0, 0);
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

void	print_key(t_hashmap **hm)
{
	ft_printf("~PRINT_KEY~\n");
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (hm[i] != NULL)
		{
			ft_printf("h[%d]=%s x[%d] y[%d]\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);
		}
		// else
		// 	ft_printf("~~\n");
		printf("i%d\n",i);
		i++;
	}
}

int	error(int errnum)
{
	ft_printf("ERROR : ");
	if (errnum == 0)
		ft_printf("Invalid Argument");
	return (-1);
}
