/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_all_tab.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:48 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:33:51 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int   set_map(t_name **name, t_link **link, t_map *map)
{
	t_name *tmp_name;
	t_link *tmp_link;
	int 	i;

	i = 0;
	if (!(map->matrix = malloc(sizeof(int*) * map->inf.size_name)))
		return (0);
	while (i < map->inf.size_name)
	{
		if (!(map->matrix[i] = malloc(sizeof(int) * map->inf.size_name)))
			return (0);
		ft_bzero(map->matrix[i], map->inf.size_name);
		i++;
	}
	map->cpt.i = 0;
	tmp_name = *name;
	tmp_link = *link;
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
		/*if (!(map->map_name[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
		  return (0);*/
		if (!(map->map_co[map->cpt.i] = malloc(sizeof(int) * 2)))
			return (0);
		map->map_co[map->cpt.i][0] = tmp_name->co_x;
		map->map_co[map->cpt.i][1] = tmp_name->co_y;
		//printf("[%s]\n", tmp_name->name);
		if (!(map->map_name[map->cpt.i] = ft_strdup(tmp_name->name)))
			return (0);
		//printf("[%s]\n", tmp_name->name);
		map->cpt.i++;
		tmp_name = tmp_name->next;
	}
	//map->map_name[map->cpt.i] = 0;
	//print_tab(map->map_name);
	map->cpt.i = 0;
	if (!(map->map_link = malloc(sizeof(char*) * map->inf.size_link + 1)))
		return (0);
	while (tmp_link)
	{
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_link->link);
		/*if (!(map->map_link[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
		  return (0);*/
		map->map_link[map->cpt.i] = ft_strdup(tmp_link->link);
		map->cpt.i++;
		tmp_link = tmp_link->next;
	}
	//map->map_link[map->cpt.i] = 0;
	//print_tab(map->map_link);
	if (check_valid_co(map->map_co, map->inf.size_name) == -1)//check coord valides
		return (-1);
	//printf("%s\n", "salut");
	//print_tab_int(map->map_co, map->inf.size_name, 2);
	return (1);
}

int 	set_matrix(t_map *map)
{
	int 	i;
	int 	j;
	int 	save_y;
	int 	save_x;
	char	*str;
	int 	salut;

	i = 0;
	j = 0;

	save_x = 0;
	save_y = 0;
	while (map->inf.size_link > i)
	{
		//map->matrix[i][j] = 0;
		//printf("[%s]\n", map->map_name[j]);
		save_y = 0;
		j = 0;
		str = NULL;
		while (map->inf.size_name > j)
		{
			salut = ft_strcheck(map->map_link[i], map->map_name[j]);
			if (salut)
			{
				save_y = j;
				str = map->map_name[j];
				break;
			}
			j++;
		}
		save_x = 0;
		j = 0;
		while (map->inf.size_name > j)
		{
			salut = ft_strcheck(map->map_link[i], map->map_name[j]);
			if (salut && str)
				save_x = j;
			j++;
		}
		map->matrix[save_y][save_x] = 1;
		map->matrix[save_x][save_y] = 1;
		i++;
		//printf("[%d][%d]\n", save_y, save_x);
	}
	print_tab_int(map->matrix, map->inf.size_name, map->inf.size_name);
	return (1);
}
