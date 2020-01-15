/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_matrix.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:35:14 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 18:10:04 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int 	delete_cul_de_sac(t_map *map)
{
	map->n_mat.i = -1;
	while (++map->n_mat.i < map->inf.size_name)
	{
		map->n_mat.j = -1;
		map->n_mat.k = 0;
		while (++map->n_mat.j < map->inf.size_name)
			if (map->matrix[map->n_mat.i][map->n_mat.j] == 1 && map->n_mat.i != map->inf.end && map->n_mat.i != map->inf.start)
			{
				map->n_mat.save_x = map->n_mat.i;
				map->n_mat.save_y = map->n_mat.j;
				map->n_mat.k++;
			}
		if (map->n_mat.k == 1)
		{
			map->matrix[map->n_mat.save_x][map->n_mat.save_y] = 0;
			map->matrix[map->n_mat.save_y][map->n_mat.save_x] = 0;
			map->n_mat.y = -1;
			map->n_mat.size_reduct++;
			while (++map->n_mat.y < map->inf.size_name)
			{
				map->n_mat.x = -1;
				while (++map->n_mat.x < map->inf.size_name)
					if (map->n_mat.save_x == map->n_mat.y || map->n_mat.save_x == map->n_mat.x)
						map->matrix[map->n_mat.y][map->n_mat.x] = -1;
			}
			delete_cul_de_sac(map);
		}
	}
	return (1);
}

int 	resize_matrix(t_map *map)
{
	map->n_mat.i = -1;
	map->n_mat.j = 0;
	map->mat.size = map->inf.size_name - map->n_mat.size_reduct;
	if (!(map->new_name = malloc(sizeof(char*) * map->mat.size + 1)))
		return (0);
	while (++map->n_mat.i < map->inf.size_name)
		if (!(map->matrix[0][map->n_mat.i] == -1))
		{
		    if (map->n_mat.i == map->inf.start)
		        map->inf.start = map->n_mat.j;
		    if (map->n_mat.i == map->inf.end)
                map->inf.end = map->n_mat.j;
			if (!(map->new_name[map->n_mat.j] = ft_strdup(map->map_name[map->n_mat.i])))
				return (0);
			map->n_mat.j++;
		}
	map->new_name[map->n_mat.j] = 0;
	if (!(map->new_matrix = malloc(sizeof(int*) * map->mat.size)))
		return (0);
	map->n_mat.i = -1;
	map->n_mat.k = 0;
	map->n_mat.n = 0;
	while (++map->n_mat.i < map->inf.size_name)
	{
		map->n_mat.j = -1;
		map->n_mat.l = 0;
		if (map->n_mat.k < map->mat.size && map->n_mat.n != 1)
			if (!(map->new_matrix[map->n_mat.k] = malloc(sizeof(int) * map->mat.size)))
				return (0);
		while (++map->n_mat.j < map->inf.size_name)
		{
			map->n_mat.j--;
			map->n_mat.n = 0;
			map->n_mat.m = 0;
			while (++map->n_mat.j < map->inf.size_name && map->matrix[map->n_mat.i][map->n_mat.j] == -1)
				map->n_mat.m++;
			if (map->n_mat.m == map->inf.size_name)
			{
				map->n_mat.n = 1;
				break;
			}
			if (map->n_mat.k < map->mat.size && map->n_mat.l < map->mat.size)
				map->new_matrix[map->n_mat.k][map->n_mat.l] = map->matrix[map->n_mat.i][map->n_mat.j];
			map->n_mat.l++;
		}
		if (map->n_mat.n != 1)
			map->n_mat.k++;
	}
	//print_tab_int(map->new_matrix, map->mat.size, map->mat.size, map);
	return (1);
}
