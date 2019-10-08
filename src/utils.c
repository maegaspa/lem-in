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
	printf("FOURMIE : [%d]\n", map->inf.nb_fourmie);
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