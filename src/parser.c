/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:27:20 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int			check_ant_line(t_map *map, char *line)
{
	while (get_next_line(0, &line) && !(check_str_number(line)) && line[0] == '#')//passe les commentaires
		ft_strdel(&line);
	if (line[0] == '\0' || !check_str_number(line))//si pas de nombres de fourmis
		map->cpt.error = 1;
	map->inf.nb_fourmi = ft_atoi(line);
	ft_strdel(&line);
	if (map->inf.nb_fourmi <= 0)
		return (-1);
	return (1);
}

int			check_link_line(t_link **link, t_map *map, char *line, char **split)
{
	if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && count_word(line, '-') == 2 && ft_strchr(line, '-'))
	{
		split = ft_strsplit(line, ' ');
		if (map->cpt.start_link)
		{
			if (!(*link = insert_link(split[0], 0)))
				return (-1);
			map->cpt.start_link = 0;
			map->tmp_link = *link;
		}
		else
		{
			if (!(map->tmp_link->next = insert_link(split[0], map->cpt.j)))
				return (-1);
			map->tmp_link = map->tmp_link->next;
		}
		map->cpt.j++;
	}
	return (1);
}

int			check_name_line(t_name **name, t_map *map, char *line, char **split)
{
	if (map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, ' ') >= 1 && !(ft_strchr(line, '-'))))
	{
		split = ft_strsplit(line, ' ');
		if (!split[1] || !split[2] || ft_strlen(split[3]) || !check_str_number(split[1]) || !check_str_number(split[2]))
			return (-1);
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
		map->cpt.i++;
	}
	if (map->cpt.j != 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		return (-1);
	return (1);
}

void		check_start_end(t_map *map, char **line)
{
	if ((ft_strstr(*line, "##start") || ft_strstr(*line, "##end")) && map->cpt.j == 0)//si start/end
	{
		if (ft_strstr(*line, "##start"))
			map->inf.start = map->cpt.i;
		if (ft_strstr(*line, "##end"))
			map->inf.end = map->cpt.i;
		ft_strdel(&(*line));
		get_next_line(0, &(*line));
		if (!(map->cpt.j == 0 && *line[0] != '#' && *line[0] != 'L' && (count_word(*line, '-') == 1 && !(ft_strchr(*line, '-')))))//si next line n'est pas une room
			map->cpt.error = 1;
	}
}

int		parser(t_name **name, t_link **link, t_map *map)
{
	char	*line;
	char	**split;

	split = NULL;
	line = NULL;
	if ((check_ant_line(map, line) != 1))
		return (-1);
	while (get_next_line(0, &line))
	{
		if (line[0] == '\0' || count_word(line, '-') > 2)//si ligne vide
			map->cpt.error = 1;
		check_start_end(map, &line);
		if ((check_name_line(name, map, line, split) != 1))
			return (-1);
		if ((check_link_line(link, map, line, split) != 1))
			return (-1);
		ft_strdel(&line);
		if (map->cpt.error == 1)
			return (-1);
	}
	if (map->inf.start == -1 || map->inf.end == -1 || !map->tmp_link || !map->tmp_name)
		return (-1);
	map->inf.size_name = list_len(*name, *link, 0);
	map->inf.size_link = list_len(*name, *link, 1);
	//print_info_map(name, link, map);
	return (1);
}
