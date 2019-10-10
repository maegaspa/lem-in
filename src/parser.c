/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 16:31:54 by hmichel     ###    #+. /#+    ###.fr     */
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
			}
			else
			{
				if (!((*name)->next = insert_name(split[0], map->cpt.i)))
					return (0);
				*name = (*name)->next;
			}
			map->cpt.i++;
		}
		if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && count_word(line, '-') == 2 && ft_strchr(line, '-')) //strchr inutil
		{
			split = ft_strsplit(line, ' ');
			if (start_link)
			{
				if (!(*link = insert_link(split[0], 0)))
					return (0);
				start_link = 0;
			}
			else
			{
				if (!((*link)->next = insert_link(split[0], map->cpt.j)))
					return (0);
				*link = (*link)->next;
			}
			//(*link)->next = NULL;//insert_link(split[0], map->cpt.j);
			map->cpt.j++;
			map->cpt.yes = 3;
		}
		if (map->cpt.yes == 1)
			map->cpt.yes++;
		ft_strdel(&line);
	}
	map->inf.size_name = list_len(*name, *link, 0);
	map->inf.size_link = list_len(*name, *link, 1);
	print_info_map(name, link, map);
	return (1);
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

	map->cpt.i = 0;
	tmp_name = *name;
	tmp_link = *link;
	if (!(map->map_name = malloc(sizeof(char*) * map->inf.size_name + 1)))
		return (0);
	while (tmp_name)
	{
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_name->name);
		if (!(map->map_name[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
			return (0);
		map->map_name[map->cpt.i] = ft_strcpy(map->map_name[map->cpt.i], tmp_name->name);
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
		if (!(map->map_link[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
			return (0);
		map->map_link[map->cpt.i] = ft_strcpy(map->map_link[map->cpt.i], tmp_link->link);
		map->cpt.i++;
		tmp_link = tmp_link->next;
	}
	map->map_link[map->cpt.i] = 0;
	//print_tab(map->map_link);
	return (0);
}

int 		init_list(t_name **name, t_link **link)
{
	if (!(*name = malloc(sizeof(t_name))))
		return (0);
	(*name)->next = NULL;
	(*name)->index = 0;
	if (!(*link = malloc(sizeof(t_link))))
		return (0);
	(*link)->next = NULL;
	(*link)->index = 0;
	return (0);
}

int	main(void)
{
	t_name	*name;
	t_link	*link;
	t_map	map;

	//name = NULL;
	//link = NULL;
	//init_list(&name, &link);
	init_value(&map);
	parser(&name, &link, &map);
	set_map(&name, &link, &map);
	//set_matrix(&name, &link, &info);
	clear(&name, &link);
	return (0);
}
