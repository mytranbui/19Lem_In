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

//replaced by nbwords
int	char_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (1);
	return (-1);
}

int	match_key(char *s, t_hashmap **hm)
{
	int	i;

	i = 0;
	while(hm[i])
	{
		if (s && !ft_strcmp(s, hm[i]->key))
			return (i);
		i++;
	}
	return (-1);
}
// void	print_tab(t_object *o)
// {
// 	FILE *ID;
// 	int j;

// 	j = 0;
// 	while (j < o->h)
// 	{
// 		ID = fopen("debugi.txt", "a");
// 		fprintf(ID, "%03d %s\n", j, o->tab[j]);
// 		fclose(ID);
// 		j++;
// 	}
// }