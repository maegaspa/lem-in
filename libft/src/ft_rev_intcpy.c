/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_rev_intcpy.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 15:04:00 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 15:04:14 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		*ft_rev_intcpy(int *dst, const int *src, int size)
{
	int	i;
	int	j;

	i = 0;
	j = size - 1;
	while (i < size)
	{
		dst[j] = src[i];
		i++;
		j--;
	}
	return (dst);
}
