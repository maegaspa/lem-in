#include "../include/lemin.h"


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
	first_path[0] = ft_intdup(first_path[0], path[0], file[0]);
	while (i < nb_path)
	{
		j = -1;
		error = 0;
		while (++j < file[i])
		{
			count = -1;
			if ((path[i][0] == start) && (path[i][j] != end))
				while (++count < nb_new_path_first && j < file[i] - 1)
					if (path[i][j] == first_path[count][j])
					{
						occurrence = count;
						error++;
						//break;
					}
		}
		printf("%d\n", error);
		if (error > 1)
		{
			printf("%d-%d-%d-%d-%d\n", path[i][0], path[i][1], path[i][2], path[i][3], path[i][4]);
		}
		if (error == 1)
		{
			first_path[nb_new_path_first] = ft_intdup(first_path[nb_new_path_first], path[i], file[i]);
			new_file_first[nb_new_path_first] = file[i];
			nb_new_path_first++;
		}
		else if ((file[occurrence] > file[i]))
		{
			second_path[nb_new_path_second] = ft_intdup(second_path[nb_new_path_second], first_path[occurrence], file[occurrence]);
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			nb_new_path_second++;
		}
		else if (new_file_first[occurrence] > file[i])
		{
			second_path[nb_new_path_second] = ft_intdup(second_path[nb_new_path_second], first_path[occurrence], new_file_first[occurrence]);
			new_file_second[nb_new_path_second] = file[occurrence];
			ft_bzero(&first_path[occurrence], file[occurrence]);
			first_path[occurrence] = path[i];
			new_file_first[occurrence] = file[i];
			nb_new_path_second++;
		}
		else
		{
			second_path[nb_new_path_second] = ft_intdup(second_path[nb_new_path_second], path[i], file[i]);
			new_file_second[nb_new_path_second] = file[i];
			nb_new_path_second++;
		}
		i++;
	}
	printf("%d-%d-%d-%d-%d\n", second_path[1][0], second_path[1][1], second_path[1][2], second_path[1][3], second_path[1][4]);
	printf("%d-%d-%d-%d-%d-%d\n\n", second_path[0][0], second_path[0][1], second_path[0][2], second_path[0][3], second_path[0][4], second_path[0][5]);
	return (first_path);
}

int 	path_line_ant(int	**first_path, int **second_path, int start, int end, int nb_ant, int nb_first_path, int nb_second_path, int *first_file, int *second_file)
{
	int 	i;
	int 	j;
	int 	k;
	int 	l;
	int		m;
	int     x;
	int 	ant_finish;
	int 	*status_ant;
	int 	nb_ant_cross;
	int     ant_num;
	int     path_size;

    i = 0;
	if (!(status_ant = malloc(sizeof(int) * nb_ant)))
		return (0);
	ant_num = 0;
	path_size = 3;//tab_len(first_file);
	while (++ant_num < nb_ant + 1)
	{
		status_ant[i] = start;
		//printf("[%d]", status_ant[i
	}
	ant_finish = 0;
	nb_ant_cross = 0;
    ant_num = 1;
	while (ant_finish < nb_ant)
	{
		i = 0;
		while (i < nb_first_path)
		{
			j = 0;
			k = 0;
			while (j < (nb_first_path + nb_ant_cross))
			{
				l = 1;
				m = 0;
				x = 0;
				//printf("ici [%d] == [%d]\n", first_path[k][l], status_ant[m]);
				while (m <= first_file[x])
			    {
                    //printf("m = %d\n k = %d\n l = %d\n", m, k, l);
//                    if (first_path[k][l] != )
//                    if (ant_num == 5)
//                        printf("WTF");
                    if (ant_num > nb_ant)
                        break;
                    //printf("first_path[%d][%d] = %d\n", k, l, first_path[k][l]);
                    printf("L%d-%d ", ant_num, first_path[k][l]);
                    if (first_path[k][l] == end && ant_num <= nb_ant)
                    {
                        //ant_num++;
//                        if (ant_num == nb_ant)
//                            printf("\nL%d-%d ", ant_num, first_path[k][l]);
                        x++;
                        m = 0;
                        ant_finish++;
                        break;
                    }
                    ant_num++;
                    if (first_path[k][l] == end && ant_num >= nb_ant)
                    {
                        //printf("L%d-%d ", ant_num, first_path[k][l]);
                        break;
                    }
                    //else if ()
                    l++;
                    m++;
				}
				/*if (first_path[k][l] == end && ant_num == nb_ant)
                    break;*/
				k++;
				j++;
				printf("\n");
			}
			i++;
		}
		ant_finish++;
		//ant_num++;
	}
	return (0);
}

int 	main(void)
{
	int **path;
	char **copy_path;
	int **new_path;
	int **new_copy_path;
	int file[4] = {8, 4, 5, 5};
	int file2[2] = {4, 5};

	if (!(path = malloc(sizeof(int*) * 4)))
		return (0);
	if (!(path[1] = malloc(sizeof(int) * 4)))
		return (0);
	path[1][0] = 1;
	path[1][1] = 3;
	path[1][2] = 6;
	path[1][3] = 8;
	if (!(path[3] = malloc(sizeof(int) * 5)))
		return (0);
	path[3][0] = 1;
	path[3][1] = 2;
	path[3][2] = 5;
	path[3][3] = 6;
	path[3][4] = 8;
	if (!(path[2] = malloc(sizeof(int) * 5)))
		return (0);
	path[2][0] = 1;
	path[2][1] = 3;
	path[2][2] = 4;
	path[2][3] = 7;
	path[2][4] = 8;
	if (!(path[0] = malloc(sizeof(int) * 8)))
		return (0);
	path[0][0] = 1;
	path[0][1] = 2;
	path[0][2] = 5;
	path[0][3] = 6;
	path[0][4] = 3;
	path[0][5] = 4;
	path[0][6] = 7;
	path[0][7] = 8;

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

	if (!(new_copy_path = malloc(sizeof(int*) * 2)))
		return (0);
	if (!(new_copy_path[0] = malloc(sizeof(int) * 3)))
		return (0);
	new_copy_path[0][0] = '1';
	new_copy_path[0][1] = '2';
	new_copy_path[0][2] = '7';
	if (!(new_copy_path[1] = malloc(sizeof(int) * 4)))
		return (0);
	new_copy_path[1][0] = '1';
	new_copy_path[1][1] = '3';
	new_copy_path[1][2] = '5';
	new_copy_path[1][3] = '7';



	new_path = clear_path(path, 4, 10, 1, 7, file);
	printf("%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2]);
	//printf("%d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	printf("%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3]);
	printf("\n\n");
	path_line_ant(new_path, new_copy_path, 1, 8, 10, 2, 1, file, file2);
	return (0);
}