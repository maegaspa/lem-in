/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:01:39 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 12:09:09 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

unsigned int	count_word(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

void	print_info_map(t_name **name, t_link **link, t_map *map)
{
	printf("FOURMI : [%d]\n", map->inf.nb_fourmi);
	printf("Nb d'elements 1 list : [%d]\n", list_len(*name, *link, 0));
	printf("Nb d'elements 2 list : [%d]\n", list_len(*name, *link, 1));
	printf("Nb d'elements totals : [%d]\n", list_len(*name, *link, 2));
	print_list(*name, *link);
	printf("Start : [%d] | End : [%d]\n", map->inf.start, map->inf.end);
}

void	free_map(char	**map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_strdel(&map[i]);
		i++;
	}
}

void	print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("[%d] - [%s]\n", i, tab[i]);
		i++;
	}
}

int		check_str_number(char *str)
{
	int i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (!(48 <= str[i] && str[i] <= 57))
				return (0);
			i++;
		}
	}
	return (1);
}
