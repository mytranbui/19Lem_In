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

//replaced by nb_word
int	char_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (1);
	return (-1);
}

t_hashmap	*match_key(char *key, t_hashmap **hm)
{
	ft_printf("MATCH_KEY\n");
	int	i;
	// int ret;

	i = hash(key);
	// ret = 40;
	while(hm[i] && i < SIZE - 1)
	{
		ft_printf("WHILE %d\n", i);
		if (hm[i]->key && !ft_strcmp(hm[i]->key, key))
		{
			// ft_printf("IF\n");
			// ft_printf("ret=%d\n", ret);
	ft_printf("h[%d]=%s x=%d y=%d\n", i, hm[i]->key, hm[i]->pt.x, hm[i]->pt.y);

			return (hm[i]);
		}
		// ret = !ft_strcmp(key, hm[i]->key);
		// ft_printf("ret=%d\n", ret);
		i++;
		i %= SIZE;
	}
	// ft_printf("ret=%d\n", ret);
	return (NULL);
}

// t_hashmap *find_hash(int key, t_hashmap **hm)
// {
//    //get the hash 
//    int i = hashCode(key);  
	
//    //move in array until an empty 
//    while(hm[i] != NULL)
//    {
//       if(hm[i]->key == key)
//          return hm[i]; 
//       ++i;	
//       //wrap around the table
//       i %= SIZE;
//    }        
//    return (NULL);        
// }
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