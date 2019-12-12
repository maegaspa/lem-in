/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:02:07 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 16:59:59 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int		name_cmp(char *s1, char *s2)
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
	//printf("%d---%d\n", j, len);
	if (j == len)
		return (1);
	return (0);
}

int 	ft_strcheck(char *s1, char *s2, int chose)
{
	unsigned int 	i;
	unsigned int 	j;
	char 		**split;

	i = 0;
	j = 0;
	split = ft_strsplit(s1, '-');
	if (chose == 1)
	{
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
		while (s2[i] || split[1][i])
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