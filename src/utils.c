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

#include "../lem_in.h"i

void free_lemin(t_lemin *lemin)
{
  free(lemin);
  lemin = NULL;
  exit(-1);
}

int	get_nb_chartab(char **tab, char c)
{
	int	nb;
	int	i;
	int	j;

	nb = 0;
	j = 0;
	while (j < o->h)
	{
		i = 0;
		while (i < o->w)
		{
			if (tab[j][i] == c)
				nb++;
			i++;
		}
		j++;
	}
	return (nb);
}

void	print_tab(t_object *o)
{
	FILE *ID;
	int j;

	j = 0;
	while (j < o->h)
	{
		ID = fopen("debugi.txt", "a");
		fprintf(ID, "%03d %s\n", j, o->tab[j]);
		fclose(ID);
		j++;
	}
}