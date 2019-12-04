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

/*int 	**sort_lowest_path_first(int	**path, int *file, int nb_path)
{
	int 	i;
	int 	i_tmp;
	int 	min;
	int 	*tmp_path;
	int 	tmp_file;

	i = 0;
	i_tmp = 0;
	min = 2147483647;
	while (i < nb_path)
	{
		if (file[i] < min)
		{
			min = file[i];
			i_tmp = i;
		}
		i++;
	}
	if (i_tmp == 0)
		return (path);
	tmp_file = file[i];
	file[i] = file[0];
	file[0] = tmp_file;
	tmp_path = path[i];
	path[i] = path[0];
	path[0] = tmp_path;
	return (path);
}*/

int 	**clear_path2(int	**path, int nb_path, int nb_fourm, int start, int end, int *file)
{
	int 	**first_path;
	int 	**second_path;
	int 	*new_file_first;
	int 	*new_file_second;
	int 	i;
	int 	j;
	int 	k;
	int		count;
	int		nb_new_path_first;
	int		nb_new_path_second;
	int 	error;
	int 	occurrence;

	i = 1;
	occurrence = 0;
	if (!(new_file_first = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(new_file_second = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(first_path = malloc(sizeof(int*) * nb_path)))
		return (0);
	if (!(second_path = malloc(sizeof(int*) * nb_path)))
		return (0);
	nb_new_path_first = 1;
	nb_new_path_second = 0;
	first_path[0] = path[0];
	new_file_first[0] = file[0];
	while (i < nb_path)
	{
		count = -1;
		error = 0;
		while (++count < nb_new_path_first/* && j < file[i]*/)
		{
			j = -1;
			//count = -1;
			//error = 0;
			//if ((path[i][0] == start) && (path[i][j] != end))
				while (++j < file[i] - 1)
				{
					//printf("[%d]_[%d]_[%d]_[%d]\n", count, nb_new_path_first, j, file[i]);
					k = -1;
					while (++k < new_file_first[count] - 1)
					{
						if (path[i][j] == first_path[count][j])
						{
							//printf("[%d]=[%d]\n", path[i][j], first_path[count][j]);
							occurrence = count;
							error++;
						}
					}
				}
		}
		//printf("%d:::%d:::%d\n", error, i, occurrence);
		/*if (error > 1)
		{
			printf("%d-%d-%d-%d-%d\n", path[i][0], path[i][1], path[i][2], path[i][3], path[i][4]);
		}*/
		if (error == 1)
		{
			first_path[nb_new_path_first] = path[i];
			new_file_first[nb_new_path_first] = file[i];
			printf(" 1- ]%d[\n", file[i]);
			nb_new_path_first++;
		}
		else if ((file[occurrence] > file[i]))
		{
			second_path[nb_new_path_second] = first_path[occurrence];
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			printf(" 2- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		else if (new_file_first[occurrence] > file[i])
		{
			second_path[nb_new_path_second] = first_path[occurrence];
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			printf(" 3- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		else
		{
			second_path[nb_new_path_second] = path[i];
			new_file_second[nb_new_path_second] = file[i];
			printf(" 4- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		i++;
	}
	//printf("1// [%d]%d*%d*%d\n", nb_new_path_first, new_file_first[0], new_file_first[1], new_file_first[2]);
	//printf("2// [%d]%d*%d*%d\n\n", nb_new_path_second, new_file_second[0], new_file_second[1], new_file_second[2]);
	//printf("2// %d-%d-%d-%d-%d\n", second_path[0][0], second_path[0][1], second_path[0][2], second_path[0][3], second_path[0][4]);
	//printf("2// %d-%d-%d-%d-%d-%d-%d-%d\n", second_path[1][0], second_path[1][1], second_path[1][2], second_path[1][3], second_path[1][4], second_path[1][5], second_path[1][6], second_path[1][7]);
	//printf("%d-%d-%d-%d\n", second_path[2][0], second_path[2][1], second_path[2][2], second_path[2][3]);
	return (second_path);
}

int 	**clear_path(int	**path, int nb_path, int nb_fourm, int start, int end, int *file)
{
	int 	**first_path;
	int 	**second_path;
	int 	*new_file_first;
	int 	*new_file_second;
	int 	i;
	int 	j;
	int		count;
	int		nb_new_path_first;
	int		nb_new_path_second;
	int 	error;
	int 	occurrence;

	i = 1;
	occurrence = 0;
	if (!(new_file_first = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(new_file_second = malloc(sizeof(int) * nb_path)))
		return (0);
	if (!(first_path = malloc(sizeof(int*) * nb_path)))
		return (0);
	if (!(second_path = malloc(sizeof(int*) * nb_path)))
		return (0);
	nb_new_path_first = 1;
	nb_new_path_second = 0;
	first_path[0] = path[0];
	new_file_first[0] = file[0];
	while (i < nb_path)
	{
		error = 0;
		count = -1;
		//occurrence = 0;
		while (++count < nb_new_path_first)
		{
			j = -1;
			//count = -1;
			//error = 0;
			//if ((path[i][0] == start) && (path[i][j] != end))
				while (++j < file[i] - 1)
				{
					//printf("[%d]_[%d]_[%d]_[%d]\n", count, nb_new_path_first, j, file[i]);
					if (path[i][j] == first_path[count][j])
					{
						//printf("[%d]=[%d]\n", path[i][j], first_path[count][j]);
						occurrence = count;
						error++;
					}
				}
		}
		printf("%d:::%d:::%d\n", error, i, occurrence);
		/*if (error > 1)
		{
			printf("%d-%d-%d-%d-%d\n", path[i][0], path[i][1], path[i][2], path[i][3], path[i][4]);
		}*/
		if (error == 1)
		{
			first_path[nb_new_path_first] = path[i];
			new_file_first[nb_new_path_first] = file[i];
			printf(" 1- ]%d[\n", file[i]);
			nb_new_path_first++;
		}
		else if ((file[occurrence] > file[i]))
		{
			second_path[nb_new_path_second] = first_path[occurrence];
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			printf(" 2- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		else if (new_file_first[occurrence] > file[i])
		{
			second_path[nb_new_path_second] = first_path[occurrence];
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			printf(" 3- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		else
		{
			second_path[nb_new_path_second] = path[i];
			new_file_second[nb_new_path_second] = file[i];
			printf(" 4- ]%d[\n", file[i]);
			nb_new_path_second++;
		}
		i++;
	}
	//printf("1// [%d]%d*%d*%d\n", nb_new_path_first, new_file_first[0], new_file_first[1], new_file_first[2]);
	//printf("2// [%d]%d*%d*%d\n\n", nb_new_path_second, new_file_second[0], new_file_second[1], new_file_second[2]);
	//printf("2// %d-%d-%d-%d-%d\n", second_path[0][0], second_path[0][1], second_path[0][2], second_path[0][3], second_path[0][4]);
	//printf("2// %d-%d-%d-%d-%d-%d-%d-%d\n", second_path[1][0], second_path[1][1], second_path[1][2], second_path[1][3], second_path[1][4], second_path[1][5], second_path[1][6], second_path[1][7]);
	//printf("%d-%d-%d-%d\n", second_path[2][0], second_path[2][1], second_path[2][2], second_path[2][3]);
	return (first_path);
}


int 	main(void)
{
	int **path;
	char **copy_path;
	int **new_path;
	int **new_path2;
	int **new_copy_path;
	int file[4] = {8, 4, 5, 5};
	int file2[3] = {5, 5, 8};
	int file3[4] = {4, 5, 5, 8};

	if (!(path = malloc(sizeof(int*) * 4)))
		return (0);
	if (!(path[0] = malloc(sizeof(int) * 4)))
		return (0);
	path[0][0] = 1;
	path[0][1] = 3;
	path[0][2] = 6;
	path[0][3] = 8;
	if (!(path[1] = malloc(sizeof(int) * 5)))
		return (0);
	path[1][0] = 1;
	path[1][1] = 2;
	path[1][2] = 5;
	path[1][3] = 6;
	path[1][4] = 8;
	if (!(path[2] = malloc(sizeof(int) * 5)))
		return (0);
	path[2][0] = 1;
	path[2][1] = 3;
	path[2][2] = 4;
	path[2][3] = 7;
	path[2][4] = 8;
	if (!(path[3] = malloc(sizeof(int) * 8)))
		return (0);
	path[3][0] = 1;
	path[3][1] = 2;
	path[3][2] = 5;
	path[3][3] = 6;
	path[3][4] = 3;
	path[3][5] = 4;
	path[3][6] = 7;
	path[3][7] = 8;


	//path = sort_lowest_path_first(path, file, 4);
	new_path = clear_path2(path, 4, 10, 1, 8, file3);
	printf("2// %d-%d-%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2], new_path[0][3], new_path[0][4]);
	printf("2// %d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	//printf("1// %d-%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2], new_path[0][3]);
	new_path2 = clear_path(new_path, 3, 10, 1, 8, file2);
	printf("3// %d-%d-%d-%d-%d\n", new_path2[0][0], new_path2[0][1], new_path2[0][2], new_path2[0][3], new_path2[0][4]);
	printf("3// %d-%d-%d-%d-%d\n", new_path2[1][0], new_path2[1][1], new_path2[1][2], new_path2[1][3], new_path2[1][4]);
	//printf("1// %d-%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2], new_path[0][3]);
	//printf("%d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	//printf("1// %d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	printf("\n\n");
	//path_line_ant(new_path, new_copy_path, 1, 8, 10, 2, 1, file, file2);
	return (0);
}