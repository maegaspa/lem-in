/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 15:26:47 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

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
	map->cpt.error = -1;
	map->inf.nb_fourmie = -1;
	map->cpt.i = 0;
	map->cpt.j = 0;
	map->inf.start = -1;
	map->inf.end = -1;
	map->cpt.start_name = 1;
	map->cpt.start_link = 1;
}

int		parser(t_name **name, t_link **link, t_map *map)
{
	char	*line;
	char	**split;
	t_link	*tmp_link;
	t_name	*tmp_name;

	while (get_next_line(0, &line) && !(is_number(line)) && line[0] == '#')//passe les commentaires
		ft_strdel(&line);
	if (line[0] == '\0' || !is_number(line))//si pas de nombres de fourmis
		map->cpt.error = 1;
	map->inf.nb_fourmie = ft_atoi(line);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		if (line[0] == '\0')//si ligne vide
			map->cpt.error = 1;
		if ((ft_strstr(line, "##start") || ft_strstr(line, "##end")) && map->cpt.j == 0)//si start/end
		{
			if (ft_strstr(line, "##start"))
				map->inf.start = map->cpt.i;
			if (ft_strstr(line, "##end"))
				map->inf.end = map->cpt.i;
			ft_strdel(&line);
			get_next_line(0, &line);
			if (!(map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-')))))//si next line n'est pas une room
				map->cpt.error = 1;
		}
		if (map->cpt.j == 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, ' ') == 3 && !(ft_strchr(line, '-'))))//si room
		{
			split = ft_strsplit(line, ' ');
			if (map->cpt.start_name)
			{
				if (!(*name = insert_name(split, 0)))
					return (0);
				map->cpt.start_name = 0;
				tmp_name = *name;
			}
			else
			{
				if (!(tmp_name->next = insert_name(split, map->cpt.i)))
					return (0);
				tmp_name = tmp_name->next;
			}
			map->cpt.i++;
		}
		if ((map->cpt.j != 0 && line[0] != '#' && line[0] != 'L' && (count_word(line, '-') == 1 && !(ft_strchr(line, '-')))) || (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && !ft_strchr(line, '-')))//si room apres link ou link apres room
			map->cpt.error = 1;
		else if (line[0] != '#' && line[0] != 'L' && count_word(line, ' ') == 1 && count_word(line, '-') == 2 && ft_strchr(line, '-'))// si link
		{
			split = ft_strsplit(line, ' ');
			if (map->cpt.start_link)
			{
				if (!(*link = insert_link(split[0], 0)))
					return (0);
				map->cpt.start_link = 0;
				tmp_link = *link;
			}
			else
			{
				if(!(tmp_link->next = insert_link(split[0], map->cpt.j)))
					return (0);
				tmp_link = tmp_link->next;
			}
			map->cpt.j++;
		}
		ft_strdel(&line);
		if (map->cpt.error == 1)
			return (-1);
	}
	if (map->inf.start == -1 || map->inf.end == -1)
		return (-1);
	map->inf.size_name = list_len(*name, *link, 0);
	map->inf.size_link = list_len(*name, *link, 1);
	print_info_map(name, link, map);
	return (1);
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

int		check_valid_co(int **tab, int len)
{
	int i;
	int found;
	int a;

	a = -1;
	while (++a < len)
	{
		found = 0;
		i = a - 1;
		while (++i < len)
		{
			if (tab[i][0] == tab[a][0] && tab[i][1] == tab[a][1])
				found++;
		}
		if (found > 1)
			return (-1);
	}
	return (1);
}

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
		map->cpt.k = 0;
		map->cpt.len = ft_strlen(tmp_name->name);
		/*if (!(map->map_name[map->cpt.i] = malloc(sizeof(char) * map->cpt.len + 1)))
		  return (0);*/
		if (!(map->map_co[map->cpt.i] = malloc(sizeof(int) * 2)))
			return (0);
		map->map_co[map->cpt.i][0] = tmp_name->co_x;
		map->map_co[map->cpt.i][1] = tmp_name->co_y;
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

	if (!check_valid_co(map->map_co, map->inf.size_name))//check coord valides
		return (0);
	print_tab_int(map->map_co, map->inf.size_name, 2);
	return (1);
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
	int		error;

	error = 0;
	init_value(&map);
	if ((error = parser(&name, &link, &map)) != 1)
	{
		exit (0);
	}
	if ((error = set_map(&name, &link, &map)) != 1)
	{
		exit (0);
	}
	//print_tab(map.map_name);
	//print_tab(map.map_link);
	//print_info_map(&name, &link, &map);
	set_matrix(&map);
	//set_matrix(&name, &link, &info);
	clear(&name, &link);
	return (0);
}
