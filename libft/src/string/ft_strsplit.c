/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:59:58 by mbui              #+#    #+#             */
/*   Updated: 2021/04/21 15:32:52 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	len_word(const char *s, char c)
{
	int len;

	len = 0;
	while (*s == c)
		s++;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int	i;
	int	j;
	int	k;

	if (!s)
		return (NULL);
	tab = (char **)malloc((nb_word(s, c) + 1) * sizeof(*tab));
	if (!tab)
		return (NULL);
	j = -1;
	k = 0;
	while (++j < nb_word(s, c))
	{
		i = 0;
		tab[j] = ft_strnew(len_word(s + k, c));// + 1);
		// tab[j] = ft_strnew(len_word(s + k, c) + 1);
		if (!tab[j])
			return (free_tab(tab, j));
		while (s[k] == c)
			k++;
		while (s[k] && s[k] != c)
			tab[j][i++] = s[k++];
		tab[j][i] = '\0';
	}
	(tab[j] = 0);
	return (tab);
}