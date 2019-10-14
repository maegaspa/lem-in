/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:02:07 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:06:06 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

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

int 	print_and_return(int i)
{
	if (i == 0)
	{
		ft_putstr("ERROR CODE\n");
		return (0);
	}
	if (i == -1)
	{
		ft_putstr("ERROR\n");
		return (-1);
	}
	return (1);
}


int 	free_and_return(char ***split, int i)
{
	int 	j;

	j = 0;
	if (i == 1)
	{
		//free split for all blocks
		return (-1);
	}
	if (i == 2)
	{
		free(*split[0]);
		free(*split[1]);
		free(*split);
		*split = NULL;
		return (-1);
	}
	return (1);
}