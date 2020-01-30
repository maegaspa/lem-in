/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_link.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 18:30:20 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 18:35:37 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void		check_2(t_map *map)
{
	while (map->inf.size_name > map->mat.j)
	{
		if (ft_strcheck(map->map_link[map->mat.i],
					map->map_name[map->mat.j], 2) && map->mat.name1)
		{
			map->mat.save_x = map->mat.j;
			map->mat.name2 = map->map_name[map->mat.j];
			map->mat.tmp_i = map->mat.i;
			if (map->mat.name2 == map->map_name[map->inf.start])
				map->mat.start_link_end++;
			if (map->mat.name2 == map->map_name[map->inf.end])
				map->mat.end_link_start++;
		}
		map->mat.j++;
	}
}

void		check_1(t_map *map)
{
	while (map->inf.size_name > map->mat.j)
	{
		if (ft_strcheck(map->map_link[map->mat.i],
					map->map_name[map->mat.j], 1))
		{
			map->mat.save_y = map->mat.j;
			map->mat.name1 = map->map_name[map->mat.j];
			if (map->mat.name1 == map->map_name[map->inf.start])
				map->mat.start_link_end++;
			if (map->mat.name1 == map->map_name[map->inf.end])
				map->mat.end_link_start++;
			break ;
		}
		map->mat.j++;
	}
}

int			check_all_link_and_name(t_map *map, int i)
{
	if (i == 1)
		check_1(map);
	else if (i == 2)
		check_2(map);
	if ((!map->mat.name2 && map->mat.save_x == -1) ||
	(!map->mat.name1 && map->mat.save_y == -1))
		return (-1);
	return (1);
}
