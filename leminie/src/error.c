/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:05:02 by mbui              #+#    #+#             */
/*   Updated: 2021/06/13 17:13:02 by mbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int error(int errnum)
{
	ft_printf("ERROR : ");
	if (errnum == -1)
		ft_printf("Invalid Argument\n");
	else if (errnum == ERR_LINE)
		ft_printf("Invalid Map : Invalid Line or More Than One Start/End\n");
	else if (errnum == ERR_ANTS)
		ft_printf("Invalid Map : Ant\n");
	else if (errnum == ERR_ROOMS)
		ft_printf("Invalid Map : Room\n");
	else if (errnum == ERR_LINKS)
		ft_printf("Invalid Map : Link\n");
	else if (errnum == ERR_PATH)
		ft_printf("No Path Found\n");
	//free all
	exit(0);
	return (-1);
}
