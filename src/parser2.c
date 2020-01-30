/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 18:47:17 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 19:05:49 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int		ft_get_map_size(t_map *m, t_name **name, t_link **l)
{
	if (m->inf.start == -1 || m->inf.end == -1 || !m->tmp_link || !m->tmp_name)
		return (-1);
	m->inf.size_name = list_len(*name, *l, 0);
	m->inf.size_link = list_len(*name, *l, 1);
	return (1);
}

int		check_start(t_map *map)
{
	if (map->cpt.yes_start != 0)
		return (-1);
	map->inf.start = map->cpt.i;
	map->cpt.yes_start = 1;
	return (1);
}

int		check_end(t_map *map)
{
	if (map->cpt.yes_end != 0)
		return (-1);
	map->inf.end = map->cpt.i;
	map->cpt.yes_end = 1;
	return (1);
}

int		check_start_name(t_map *map, t_name **name, char **split)
{
	if (map->cpt.start_name)
	{
		if (!(*name = insert_name(split, 0)))
			return (-1);
		map->cpt.start_name = 0;
		map->tmp_name = *name;
	}
	else
	{
		if (!(map->tmp_name->next = insert_name(split, map->cpt.i)))
			return (-1);
		map->tmp_name = map->tmp_name->next;
	}
	return (1);
}
