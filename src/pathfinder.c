/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinder.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 10:24:52 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 14:59:08 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	get_min_path(t_map *map, t_bfs *bfs)
{
	int		count_start;
	int		x;
	int		count_end;

	x = 0;
	count_start = 0;
	count_end = 0;
	while (x < map->inf.size_name)
	{
		if (map->matrix[map->inf.start][x] == 1)
			count_start++;
		if (map->matrix[map->inf.end][x] == 1)
			count_end++;
		x++;
	}
	if (count_start >= count_end)
		bfs->min_path = count_end;
	else if (count_end > count_start)
		bfs->min_path = count_start;
}

void	reverse_pathfinding(t_map *map, t_bfs *bfs)
{
	int x = map->inf.size_name - 1;
	print_tab_int(map->matrix, map->inf.size_name, map->inf.size_name);
	printf("Tableau de distance :\n");
	while (x > map->inf.start)
	{
		printf("%s[%d]\n", map->map_name[x], bfs->distance[x]);
		x--;
	}
	get_min_path(map, bfs);
	printf("min_path : %d\n", bfs->min_path);
//	printf("")
}
