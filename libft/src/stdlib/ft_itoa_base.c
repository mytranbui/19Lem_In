/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:59:47 by mbui              #+#    #+#             */
/*   Updated: 2021/04/02 13:08:42 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	find_size(long long index, int base)
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

static char	*which_str_base(char x)
{
	char	*str_base;

	str_base = "0123456789abcdef";
	if (x == 'X')
		str_base = "0123456789ABCDEF";
	return (str_base);
}

static char	*ft_itoa_base2(long long index, int base)
{
	if (base < 2 || base > 16)
		return (0);
	if (index == 0)
		return (ft_strdup("0"));
	return (0);
}

char	*ft_itoa_base(long long index, int base, char x)
{
	char	*ret;
	char	*str_base;
	int		len;
	int		no_sign_len;

	str_base = which_str_base(x);
	len = find_size(index, base);
	no_sign_len = len;
	if (base < 2 || base > 16 || index == 0)
		return (ft_itoa_base2(index, base));
	if (base == 10 && index < 0)
		len++;
	if (index < 0)
		index = -index;
	ret = ft_strnew(len);
	if (!ret)
		return (NULL);
	if (no_sign_len < len)
		ret[0] = '-';
	while (index)
	{
		ret[--len] = str_base[index % base];
		index /= base;
	}
	return (ret);
}
