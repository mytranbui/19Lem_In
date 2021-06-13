/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrumax_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:02:00 by mbui              #+#    #+#             */
/*   Updated: 2020/10/24 17:17:34 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putnbrumax_fd(uintmax_t n, int fd)
{
	if (n >= 10)
		ft_putnbrumax_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}