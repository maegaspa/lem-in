/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 01:21:03 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int			check_ant_line(t_map *map, char **l, t_file_display **f_dis)
{
	int		chose;

	chose = 0;
	while (get_next_line(0, &(*l)) && !(check_str_number(*l)) && *l[0] == '#')
	{
		if (!insert_line_lst(map, l, f_dis, &chose))
			return (-1);
		if (ft_strstr(*l, "##start") || ft_strstr(*l, "##end"))
		{
			ft_strdel(&(*l));
			return (-1);
		}
		ft_strdel(&(*l));
	}
	if (!*l || !insert_line_lst(map, l, f_dis, &chose))
		return (-1);
	if (l[0] == '\0' || !check_str_number(*l))
		map->cpt.error = 1;
	map->inf.nb_fourmi = ft_atoi(*l);
	ft_strdel(&(*l));
	if (map->inf.nb_fourmi <= 0)
		return (-1);
	return (1);
}

int			check_link_line(t_link **link, t_map *map, char *line, char **split)
{
	if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 &&
			count_word(line, '-') == 2 && ft_strchr(line, '-'))
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
	if (map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' &&
			(count_word(line, ' ') >= 1 && !(ft_strchr(line, '-'))))
	{
		split = ft_strsplit(line, ' ');
		if (!split[1] || !split[2] || count_word(line, ' ') > 3 ||
				!check_str_number(split[1]) || !check_str_number(split[2]))
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
	if (map->cpt.j != 0 && line[0] != '#' && line[0] != 'L' &&
			(count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		return (-1);
	return (1);
}

int			check_start_end(t_map *map, char **line, t_file_display **f_dis)
{
	int		chose;

	chose = 1;
	if ((ft_strstr(*line, "##start") || ft_strstr(*line, "##end")) && map->cpt.j == 0)
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
		if (!(map->cpt.j == 0 && *line[0] != '#' && *line[0] != 'L' &&
					(count_word(*line, '-') == 1 && !(ft_strchr(*line, '-')))))
			map->cpt.error = 1;
	}
	return (1);
}

int			parser(t_name **name, t_link **l, t_map *m, t_file_display **f_dis)
{
	char	*line;
	char	**split;
	int		chose;

	split = NULL;
	line = NULL;
	chose = 1;
	if ((check_ant_line(m, &line, f_dis) != 1))
		return (-1);
	while (get_next_line(0, &line))
	{
		if (!insert_line_lst(m, &line, f_dis, &chose))
			return (-1);
		if (line[0] == '\0' || count_word(line, '-') > 2)
			m->cpt.error = 1;
		if ((check_start_end(m, &line, f_dis) != 1))
			return (-1);
		if ((check_name_line(name, m, line, split) != 1))
			return (-1);
		if ((check_link_line(l, m, line, split) != 1))
			return (-1);
		get_line_expected(m, line);
		ft_strdel(&line);
		if (m->cpt.error == 1)
			return (-1);
	}
	if (m->inf.start == -1 || m->inf.end == -1 || !m->tmp_link || !m->tmp_name)
		return (-1);
	m->inf.size_name = list_len(*name, *l, 0);
	m->inf.size_link = list_len(*name, *l, 1);
	return (1);
}
