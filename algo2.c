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
	int 	**new_path_copy;
	int 	*new_file;
	int i;
	int j;
	int	count;
	int	nb_new_path;
	int error;

	i = 1;
	if (!(new_file = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(new_path_copy = malloc(sizeof(int*) * nb_path)))
		return (0);
	nb_new_path = 1;
	new_path_copy[0] = ft_intdup(new_path_copy[0], path[0], file[0]);
	while (i < nb_path)
	{
		j = -1;
		error = 0;
		while (++j < file[i])
		{
			count = -1;
			if ((path[i][0] == start) && (path[i][j] != end))
				while (++count < nb_new_path && j < file[i] - 1)
					if (path[i][j] == new_path_copy[count][j])
					{
						error++;
						break;
					}
		}
		if (error == 1)
		{
			new_path_copy[nb_new_path] = ft_intdup(new_path_copy[nb_new_path], path[i], file[i]);
			new_file[nb_new_path] = file[i];
			nb_new_path++;
		}
		else if (file[nb_new_path - 1] > file[i])
		{
			ft_bzero(&new_path_copy[nb_new_path - 1], file[count - 1]);
			new_path_copy[nb_new_path - 1] = path[i];
			new_file[nb_new_path - 1] = file[i];
		}
		i++;
	}
	return (new_path_copy);
}

int 	path_line_ant(int	**path, int start, int end, int nb_ant, int nb_path, int *file)
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
				printf("[%d] == [%d]\n", path[k][l], status_ant[m]);
				while (path[k][l] == status_ant[m])
				{
					//printf("[%d]-[%d]\n", m, l);
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
	char **copy_path;
	int **new_path;
	char **new_copy_path;
	int file[3] = {5, 4, 3};
	int file2[2] = {3, 4};

	if (!(path = malloc(sizeof(int*) * 3)))
		return (0);
	if (!(path[2] = malloc(sizeof(int) * 3)))
		return (0);
	path[2][0] = 1;
	path[2][1] = 2;
	path[2][2] = 7;
	if (!(path[1] = malloc(sizeof(int) * 4)))
		return (0);
	path[1][0] = 1;
	path[1][1] = 3;
	path[1][2] = 5;
	path[1][3] = 7;
	if (!(path[0] = malloc(sizeof(int) * 5)))
		return (0);
	path[0][0] = 1;
	path[0][1] = 4;
	path[0][2] = 5;
	path[0][3] = 6;
	path[0][4] = 7;

	if (!(copy_path = malloc(sizeof(char*) * 4)))
		return (0);
	if (!(copy_path[2] = malloc(sizeof(char) * 4)))
		return (0);
	copy_path[2][0] = '1';
	copy_path[2][1] = '2';
	copy_path[2][2] = '7';
	copy_path[2][3] = '\0';
	if (!(copy_path[1] = malloc(sizeof(char) * 5)))
		return (0);
	copy_path[1][0] = '1';
	copy_path[1][1] = '3';
	copy_path[1][2] = '5';
	copy_path[1][3] = '7';
	copy_path[1][4] = '\0';
	if (!(copy_path[0] = malloc(sizeof(char) * 6)))
		return (0);
	copy_path[0][0] = '1';
	copy_path[0][1] = '4';
	copy_path[0][2] = '5';
	copy_path[0][3] = '6';
	copy_path[0][4] = '7';
	copy_path[0][5] = '\0';
	copy_path[3] = NULL;

	if (!(new_copy_path = malloc(sizeof(char*) * 3)))
		return (0);
	if (!(new_copy_path[0] = malloc(sizeof(char) * 4)))
		return (0);
	new_copy_path[0][0] = '1';
	new_copy_path[0][1] = '2';
	new_copy_path[0][2] = '7';
	new_copy_path[0][3] = '\0';
	if (!(new_copy_path[1] = malloc(sizeof(char) * 5)))
		return (0);
	new_copy_path[1][0] = '1';
	new_copy_path[1][1] = '3';
	new_copy_path[1][2] = '5';
	new_copy_path[1][3] = '7';
	new_copy_path[1][4] = '\0';



	new_path = clear_path(path, 3, 10, 1, 7, file);
	printf("%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2]);
	//printf("%d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	printf("%d-%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2], new_path[0][3]);
	path_line_ant(new_path, 1, 6, 10, 2, file);
	return (0);
}