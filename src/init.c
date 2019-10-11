/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:37 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:33:39 by cgarrot     ###    #+. /#+    ###.fr     */
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
}
