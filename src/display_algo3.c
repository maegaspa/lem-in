/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_algo3.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 17:52:28 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 18:10:20 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void	print_space(t_dispa *dis)
{
	if (dis->space == 1)
		dis->space = 0;
	else
		ft_printf(" ");
}

void	last_ant_finish(t_dispa *dis, t_sort *sort, t_map map)
{
	if (dis->k + 1 < sort->new_size_first[dis->j] &&
			sort->first_path[dis->j][dis->k + 1] == map.inf.end)
	{
		dis->ant_finish++;
		dis->ant_cross--;
	}
}
