/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 17:32:19 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

/*void	error_clean_close(t_name **name, t_link **link)
  {
  ft_putstr("Invalid map\n");
  clear(name, link);
  exit(0);
  }*/

int		is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(48 <= str[i] && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

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

	get_next_line(0, &line);
	if (!(is_number(line)))
	{
		ft_strdel(&line);
		return (-1);
	}
	ft_strdel(&line);

	while (get_next_line(0, &line))
	{
		if ((ft_strstr(line, "##start") || ft_strstr(line, "##end")) && map->cpt.j == 0)// checker s'il y a une room sur la ligne d'apres
		{
			if (ft_strstr(line, "##start"))
				map->inf.start = map->cpt.i;
			if (ft_strstr(line, "##start"))
				map->inf.end = map->cpt.i;
			ft_strdel(&line);
			get_next_line(0, &line);
			if (!(map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-')))))
				return (-1);
		}
		if (map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		{
			split = ft_strsplit(line, ' ');
			insert_name(name, split[0], map->cpt.i);
			//insert_coord(coord, split[1], split[2], map->cpt.i);
			map->cpt.i++;
		}
		if (map->cpt.j != 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
			return (-1);
		else if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && count_word(line, '-') == 2 && ft_strchr(line, '-'))
		{
			split = ft_strsplit(line, ' ');
			insert_link(link, split[0], map->cpt.j);
			map->cpt.j++;
		}
		ft_strdel(&line);
	}
	//check_valid_rooms_coord
	//check start end presents et lies
	map->inf.size_name = list_len(*name, *link, 0);
	map->inf.size_link = list_len(*name, *link, 1);
	print_info_map(name, link, map);
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

int	main(void)
{
	t_name	*name;
	t_link	*link;
	t_map	map;

	name = NULL;
	link = NULL;
	init_value(&map);
	parser(&name, &link, &map);
	set_map(&name, &link, &map);
	//set_matrix(&name, &link, &info);
	clear(&name, &link);
	return (0);
}
