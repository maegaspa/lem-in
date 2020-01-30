/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:02:07 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 01:24:12 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int			name_cmp(char *s1, char *s2)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			j++;
		i++;
	}
	if (j == len)
		return (1);
	return (0);
}

int			ft_strcheck(char *s1, char *s2, int chose)
{
	unsigned int		i;
	unsigned int		j;
	char				**split;

	i = 0;
	j = 0;
	split = ft_strsplit(s1, '-');
	if (chose == 1)
	{
		if (ft_strlen(s2) != ft_strlen(split[0]))
			return (0);
		while (s2[i] || split[0][i])
		{
			if (s2[i] == split[0][i])
				j++;
			i++;
		}
		if (j == i)
		{
			free(split[0]);
			free(split[1]);
			free(split);
			return (1);
		}
	}
	if (chose == 2)
	{
		if (ft_strlen(s2) != ft_strlen(split[1]))
			return (0);
		while (split[1][i] || s2[i])
		{
			if (s2[i] == split[1][i])
				j++;
			i++;
		}
		if (j == i)
		{
			free(split[0]);
			free(split[1]);
			free(split);
			return (1);
		}
	}
	free(split[0]);
	free(split[1]);
	free(split);
	return (0);
}

int			ft_atoi_3(char const *str)
{
	int			i;
	int			nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || ft_isalpha(str[i]) || str[i] == '#' || str[i] == ':')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

void		get_line_expected(t_map *map, char *line)
{
	if (ft_strstr(line, "#Here is"))
		map->line_expected = ft_atoi_3(line);
}
