/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 18:02:07 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	init_value(t_map *map)
{
	map->inf.nb_fourmie = -1;
	map->cpt.yes = 0;
	map->cpt.i = 0;
	map->cpt.j = 0;
	map->inf.start = 0;
	map->inf.end = 0;
}

int		parser(t_name **name, t_link **link, t_map *map)
{
	char	*line;
	char	**split;
	int		start_name;
	int		start_link;
	t_link 	*tmp_link;
	t_name 	*tmp_name;

	start_name = 1;
	start_link = 1;
	while (get_next_line(0, &line))
	{
		if (line[0] != '#' && line[0] != 'L' && !map->cpt.yes)
		{
			if (count_word(line, ' ') && !(ft_strchr(line, '-')))
			{
				map->inf.nb_fourmie = ft_atoi(line);
				map->cpt.yes = 1;
			}
		}
		if (ft_strstr(line, "##start"))
			map->inf.start = map->cpt.i;
		if (ft_strstr(line, "##end"))
			map->inf.end = map->cpt.i;
		if (line[0] != '#' && line[0] != 'L' && map->cpt.yes > 1 && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		{
			split = ft_strsplit(line, ' ');
			if (start_name)
			{
				if (!(*name = insert_name(split[0], 0)))
					return (0);
				start_name = 0;
				tmp_name = *name;
				//printf("[%s]\n", (*name)->name);
			}
			else
			{
				//printf("[%s]\n", (*name)->name);
				if (!(tmp_name->next = insert_name(split[0], map->cpt.i)))
					return (0);
				tmp_name = tmp_name->next;
			}
			map->cpt.i++;
		}
		if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && count_word(line, '-') == 2 && ft_strchr(line, '-'))
		{
			split = ft_strsplit(line, ' ');
			if (start_link)
			{
				if (!(*link = insert_link(split[0], 0)))
					return (0);
				start_link = 0;
				tmp_link = *link;
				//printf("[%s]\n", (*link)->link);
			}
			else
			{
				//printf("[%s]\n", (*link)->link);
				if (!(tmp_link->next = insert_link(split[0], map->cpt.j)))
					return (0);
				tmp_link = tmp_link->next;
			}
			map->cpt.j++;
		}
		if (map->cpt.yes == 1)
			map->cpt.yes++;
		ft_strdel(&line);
	}
	map->inf.size_name = list_len(*name, *link, 0);
	map->inf.size_link = list_len(*name, *link, 1);
	//print_info_map(name, link, map);
	return (0);
}

/*int   set_matrix(t_name **list, t_link **link, t_info *info)
  {
  if (!(info->matrix = malloc(sizeof(info->size_name))))
  return (0);
  }*/

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
	while (tmp_name)
	{
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_name->name);
		/*if (!(map->map_name[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
			return (0);*/
		map->map_name[map->cpt.i] = ft_strdup(tmp_name->name);
		//printf("[%s]\n", tmp_name->name);
		map->cpt.i++;
		tmp_name = tmp_name->next;
	}
	map->map_name[map->cpt.i] = 0;
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
	map->map_link[map->cpt.i] = 0;
	//print_tab(map->map_link);
	return (0);
}

void 	print_tab_int(int **tab, int y, int x)
{
	int i = 0;
	int j = 0;

	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%d ", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int 	ft_strcheck(char *s1, char *s2)
{
	unsigned int 	i;
	int 	j;
	int 	k;
	int 	len;

	i = 0;
	j = 0;
	len = ft_strlen(s2);
	while (s1[i])
	{
		j = 0;
		k = i;
		while (s2[j] && s1[k] && s1[k] == s2[j])
		{
			k++;
			j++;
		}
		if (len == j)
		{	
			//printf("[%s][%s][%d]\n", s1, s2, j);
			return (1);
		}
		i++;
	}
	return (0);
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
	return (0);
}

int		main(void)
{
	t_name	*name;
	t_link	*link;
	t_map	map;
	
	init_value(&map);
	parser(&name, &link, &map);
	set_map(&name, &link, &map);
	//print_tab(map.map_name);
	//print_tab(map.map_link);
	//print_info_map(&name, &link, &map);
	set_matrix(&map);
	//set_matrix(&name, &link, &info);
	clear(&name, &link);
	return (0);
}
