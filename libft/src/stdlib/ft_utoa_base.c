/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:59:47 by mbui              #+#    #+#             */
/*   Updated: 2021/04/02 12:59:42 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	find_size(unsigned long long index, int base)
{
	int	len;

	len = 0;
	while (index)
	{
		len++;
		index /= base;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long long index, int base, char x)
{
	char	*ret;
	char	*str_base;
	int		len;

	str_base = "0123456789abcdef";
	if (x == 'X')
		str_base = "0123456789ABCDEF";
	len = find_size(index, base);
	if (base < 2 || base > 16)
		return (0);
	if (index == 0)
		return (ft_strdup("0"));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (index)
	{
		ret[--len] = str_base[index % base];
		index /= base;
	}
	return (ret);
}
