/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_all_tab.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:48 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 17:00:20 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int 	set_tab_link(t_link *tmp_link, t_map *map)
{
	map->cpt.i = 0;
	if (!(map->map_link = malloc(sizeof(char*) * map->inf.size_link + 1)))
		return (0);
	while (tmp_link)
	{
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_link->link);
		if (!(map->map_link[map->cpt.i] = ft_strdup(tmp_link->link)))
			return (0);
		map->cpt.i++;
		tmp_link = tmp_link->next;
	}
	return (1);
}

int 	set_tab_name_and_co(t_name *tmp_name, t_map *map)
{
	map->cpt.i = 0;
	if (!(map->map_name = malloc(sizeof(char*) * map->inf.size_name + 1)))
		return (0);
	if (!(map->map_co = malloc(sizeof(int*) * map->inf.size_name)))
		return (0);
	while (tmp_name)
	{
		if (!(tmp_name->name))
			return (-1);
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_name->name);
		if (!(map->map_co[map->cpt.i] = malloc(sizeof(int) * 2)))
			return (0);
		map->map_co[map->cpt.i][0] = tmp_name->co_x;
		map->map_co[map->cpt.i][1] = tmp_name->co_y;
		if (!(map->map_name[map->cpt.i] = ft_strdup(tmp_name->name)))
			return (0);
		map->cpt.i++;
		tmp_name = tmp_name->next;
	}
	return (1);
}

int   set_map(t_name **name, t_link **link, t_map *map)
{
	t_name *tmp_name;
	t_link *tmp_link;

	map->cpt.i = 0;
	tmp_name = *name;
	tmp_link = *link;
	if (!(map->matrix = malloc(sizeof(int*) * map->inf.size_name)))
		return (0);
	while (map->cpt.i < map->inf.size_name)
	{
		if (!(map->matrix[map->cpt.i] = malloc(sizeof(int) * map->inf.size_name)))
			return (0);
		ft_bzero(map->matrix[map->cpt.i], map->inf.size_name);
		map->cpt.i++;
	}
	if ((map->inf.ret = set_tab_name_and_co(tmp_name, map)) && map->inf.ret != 1)
		return (map->inf.ret);
	if ((map->inf.ret = set_tab_link(tmp_link, map)) && map->inf.ret != 1)
		return (map->inf.ret);
	if (check_valid_co(map->map_co, map->inf.size_name) == -1)//check coord valides
		return (-1);
	return (1);
}

void	check_all_link_and_name(t_map *map, int i)
{
	if (i == 1)
		while (map->inf.size_name > map->mat.j)
		{
			//printf("1----|%s|-|%s|\n", map->map_link[map->mat.i], map->map_name[map->mat.j]);
			if (ft_strcheck(map->map_link[map->mat.i], map->map_name[map->mat.j], 1))
			{
				map->mat.save_y = map->mat.j;
				map->mat.name1 = map->map_name[map->mat.j];
				break;
			}
			map->mat.j++;
		}
	if (i == 2)
		while (map->inf.size_name > map->mat.j)
		{
			//printf("2----|%s|-|%s|\n", map->map_link[map->mat.i], map->map_name[map->mat.j]);
			if (ft_strcheck(map->map_link[map->mat.i], map->map_name[map->mat.j], 2) && map->mat.name1)
			{
				map->mat.save_x = map->mat.j;
				map->mat.name2 = map->map_name[map->mat.j];
				map->mat.tmp_i = map->mat.i;
			}
			map->mat.j++;
		}
}

int 	set_matrix(t_map *map)
{
	init_matrix(map);
	while (map->inf.size_link > map->mat.i)
	{
		map->mat.j = 0;
		map->mat.name1 = NULL;
		map->mat.name2 = NULL;
		check_all_link_and_name(map, 1);
		if (map->mat.name1 == NULL)
			return (-1);
		map->mat.j = 0;
		check_all_link_and_name(map, 2);
		//printf("%s|----|%s\n", map->mat.name1, map->mat.name2);
		if (map->mat.name1 == map->mat.name2)
		{
			map->mat.split = ft_strsplit(map->map_link[map->mat.tmp_i], '-');
			if (ft_strcmp(map->mat.split[0], map->mat.split[1]) != 0)
				return (free_and_return(&map->mat.split, 2));
			free_and_return(&map->mat.split, 0);
		}
		map->matrix[map->mat.save_y][map->mat.save_x] = 1;
		map->matrix[map->mat.save_x][map->mat.save_y] = 1;
		map->mat.i++;
	}
	print_tab_int(map->matrix, map->inf.size_name, map->inf.size_name);
	return (1);
}