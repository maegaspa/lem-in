#include <stdio.h>
#include <stdlib.h>
#include "libft/includes/ft_printf.h"

int 	*ft_intdup(int *dst, int *src, unsigned int size)
{
	unsigned int i;

	i = 0;
	if (!(dst = malloc(sizeof(int) * size)))
		return (0);
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int 	**clear_path(int	**path, int nb_path, int nb_fourm, int start, int end, int *file)
{
	int	**new_path;
	int i;
	int j;
	int k;
	int	count;
	int	nb_new_path;
	int error;

	i = 1;
	if (!(new_path = malloc(sizeof(int*) * nb_path + 1)))
		return (0);
	//if (!(new_path[0] = malloc(sizeof(int) * nb_path + 1)))
	//	return (0);
	nb_new_path = 1;
	//new_path[0] = path[0];
	new_path[0] = ft_intdup(new_path[0], path[0], 5);
	while (i < nb_path)
	{
		j = 0;
		k = 0;
		error = 0;
		while (j < file[i])
		{
			if (path[i][0] == start)
				k++;
			if (path[i][j] == end && path[i][j + 1])
				k++;
			count = 0;
			if (path[i][j] != start && path[i][j] != end)
			{
				while (count < nb_new_path)
				{
					//printf("[%d]={%d, %d}", path[i][j], i, j);
					printf("|%d|\n", new_path[count][j]);
					if (path[i][j] == new_path[count][j])
					{
						error++;
					}
					count++;
				}
			}
			j++;
		}
		if (error == 1)
		{
				//printf("%s\n", path[i]);
				//if (!(new_path[nb_new_path] = malloc(sizeof(char) * nb_path + 1)))
				//	return (0);
			new_path[nb_new_path] = ft_intdup(new_path[nb_new_path], path[i], 5);
				//new_path[nb_new_path] = path[i];
			nb_new_path++;
		}
		i++;
	}
	/*i = 0;
	j = 0;
	while (i < nb_new_path)
	{
		j = -1;
		while (++j < 5 )
			printf("%d-", new_path[i][j]);
		i++;
		printf("\n");
	}*/
	printf("salut\n");
	return (new_path);
}

int 	path_line_ant(int	**path, int start, int end, int nb_ant, int nb_path)
{
	int 	i;
	int 	j;
	int 	k;
	int 	l;
	int		m;
	int 	ant_finish;
	int 	*status_ant;
	int 	nb_ant_cross;

	if (!(status_ant = malloc(sizeof(int) * nb_ant)))
		return (0);
	i = 0;
	while (i < nb_ant)
	{
		status_ant[i] = 1;
		//printf("[%d]", status_ant[i]);
		i++;
	}
	ant_finish = 0;
	nb_ant_cross = 0;
	while (ant_finish < nb_ant)
	{
		i = 0;
		while (i < nb_path)
		{
			j = 0;
			k = 0;
			while (j < (nb_path + nb_ant_cross))
			{
				l = 0;
				m = 0;
				//printf("[%c] == [%d]\n", path[k][l], status_ant[m]);
				while (path[k][l] == status_ant[m])
				{
					printf("[%d]-[%d]\n", m, l);
					printf("[%d] == [%d]\n", path[k][l], status_ant[m]);
					l++;
				}
				status_ant[m] = path[k][l];
				j++;
			}
			i++;
		}
		ant_finish++;
	}
	return (0);
}

int 	main(void)
{
	int **path;
	//int path[3][5] = { {1, 2, 7} , {1, 3, 5, 6, 7}, {1, 4,5, 6, 7}};
	int **new_path;
	int file[3] = {3, 5, 5};

	if (!(path = malloc(sizeof(int*) * 3)))
		return (0);
	if (!(path[0] = malloc(sizeof(int) * 3)))
		return (0);
	path[0][0] = 1;
	path[0][1] = 2;
	path[0][2] = 7;
	if (!(path[1] = malloc(sizeof(int) * 5)))
		return (0);
	path[1][0] = 1;
	path[1][1] = 3;
	path[1][2] = 5;
	path[1][3] = 6;
	path[1][4] = 7;
	if (!(path[2] = malloc(sizeof(int) * 5)))
		return (0);
	path[2][0] = 1;
	path[2][1] = 4;
	path[2][2] = 5;
	path[2][3] = 6;
	path[2][4] = 7;

	printf("%d-%d-%d\n", path[0][0], path[0][1], path[0][2]);
	printf("%d-%d-%d-%d-%d\n", path[1][0], path[1][1], path[1][2], path[1][3], path[1][4]);
	printf("\n");
	new_path = clear_path(path, 3, 10, 1, 6, file);
	printf("%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2]);
	//printf("%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3]);
	//printf("%d-%d-%d-%d-%d\n", new_path[2][0], new_path[2][1], new_path[2][2], new_path[2][3], new_path[2][4]);
	//path_line_ant(new_path, 1, 6, 10, 2);
	return (0);
}