/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 19:18:34 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int 		insert_line_lst(t_map *map, char **line, t_file_display	**f_dis, int *chose)
{
	if (*chose == 0)
	{
		if (!(*f_dis = insert_line(*line)))
				return (-1);
		map->tmp_f_dis = *f_dis;
		*chose = 1;
	}
	else if (*chose == 1)
	{
		if (!(map->tmp_f_dis->next = insert_line(*line)))
				return (-1);
		map->tmp_f_dis = map->tmp_f_dis->next;
	}
	return (1);
}

int			check_ant_line(t_map *map, char **line, t_file_display	**f_dis)
{
	int  chose;

	chose = 0;
	while (get_next_line(0, &(*line)) && !(check_str_number(*line)) && *line[0] == '#')//passe les commentaires
	{
		if (!insert_line_lst(map, line, f_dis, &chose))
			return (-1);
		if (ft_strstr(*line, "##start") || ft_strstr(*line, "##end"))
		{
			ft_strdel(&(*line));
			return (-1);
		}
		ft_strdel(&(*line));
	}
	if (!insert_line_lst(map, line, f_dis, &chose))
			return (-1);
	if (!*line)
		return (-1);
	if (line[0] == '\0' || !check_str_number(*line))//si pas de nombres de fourmis
		map->cpt.error = 1;
	map->inf.nb_fourmi = ft_atoi(*line);
	//printf("|%s|\n", *line);
	ft_strdel(&(*line));
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
		if (!split[1] || !split[2] || count_word(line, ' ') > 3 || !check_str_number(split[1]) || !check_str_number(split[2]))
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
	else if (line[0] == 'L')
		return (-1);
	if (map->cpt.j != 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		return (-1);
	return (1);
}

int		check_start_end(t_map *map, char **line, t_file_display	**f_dis)
{
	int chose;

	chose = 1;
	if ((ft_strstr(*line, "##start") || ft_strstr(*line, "##end")) && map->cpt.j == 0)//si start/end
	{
		if (ft_strstr(*line, "##start"))
		{
			if (map->cpt.yes_start != 0)
				return (-1);
			map->inf.start = map->cpt.i;
			map->cpt.yes_start = 1;
		}
		if (ft_strstr(*line, "##end"))
		{
			if (map->cpt.yes_end != 0)
				return (-1);
			map->inf.end = map->cpt.i;
			map->cpt.yes_end = 1;
		}
		ft_strdel(&(*line));
		get_next_line(0, &(*line));
		if (!insert_line_lst(map, line, f_dis, &chose))
			return (-1);
		if (!(map->cpt.j == 0 && *line[0] != '#' && *line[0] != 'L' && (count_word(*line, '-') == 1 && !(ft_strchr(*line, '-')))))//si next line n'est pas une room
			map->cpt.error = 1;
	}
	return (1);
}

int		parser(t_name **name, t_link **link, t_map *map, t_file_display	**f_dis)
{
	char	*line;
	char	**split;
	int 	chose;

	split = NULL;
	line = NULL;
	chose = 1;
	if ((check_ant_line(map, &line, f_dis) != 1))
		return (-1);
	while (get_next_line(0, &line))
	{
		if (!insert_line_lst(map, &line, f_dis, &chose))
			return (-1);
		if (line[0] == '\0' || count_word(line, '-') > 2)//si ligne vide
			map->cpt.error = 1;
		if ((check_start_end(map, &line, f_dis) != 1))
			return (-1);
		if ((check_name_line(name, map, line, split) != 1))
			return (-1);
		if ((check_link_line(link, map, line, split) != 1))
			return (-1);
		get_line_expected(map, line);
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
