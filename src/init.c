/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:37 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/28 12:52:40 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	init_value(t_map *map)
{
	map->cpt.error = -1;
	map->inf.nb_fourmi = -1;
	map->cpt.i = 0;
	map->cpt.j = 0;
	map->inf.start = -1;
	map->inf.end = -1;
	map->cpt.start_name = 1;
	map->cpt.start_link = 1;
	map->cpt.yes_start = 0;
	map->cpt.yes_end = 0;
	map->n_mat.size_reduct = 0;
}

void	init_matrix(t_map *map)
{
	map->mat.i = 0;
	map->mat.tmp_i = 0;
	map->mat.j = 0;
	map->mat.save_x = -1;
	map->mat.save_y = -1;
	map->mat.name1 = NULL;
	map->mat.name2 = NULL;
	map->mat.split = NULL;
	map->mat.start_link_end = 0;
	map->mat.end_link_start = 0;
}
