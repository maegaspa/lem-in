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

int 	**clear_path(t_map *map, /*t_display *display,*/ t_path *path, t_bfs *bfs)
{
	int 	i;
	int 	j;
	int     k;

	i = 1;
	//changement de i = 1 à i = 0;
	path->occur = 0;
	if  (!(path->new_file_first = malloc(sizeof(int) * path->nb_path)))
		return (0);
	if (!(path->new_file_second = malloc(sizeof(int) * path->nb_path)))
		return (0);
	if (!(path->first_path = malloc(sizeof(int*) * path->nb_path)))
		return (0);
	if (!(path->second_path = malloc(sizeof(int*) * path->nb_path)))
		return (0);
	path->nb_newfirst = 1;
	path->nb_newsecond = 0;
	dprintf(1, "PTDR1\n");
    //path->first_path[0] = bfs->paths[0];
    dprintf(1, "PTDR2\n");
    printf("path->nb_path = %d\n", path->nb_path);
	while (i < path->nb_path)
	{
		j = -1;
		path->error = 0;
        dprintf(1, "PTDR2/3\n");
		k = bfs->distance[i];
		while (++j < bfs->distance[i] && k-- > 0)
		{
			path->count = -1;
			if ((bfs->paths[i][k] == map->inf.start) && (bfs->paths[i][k] != map->inf.end))
				while (++path->count < path->nb_newfirst && j < bfs->distance[i] - 1)
					if (bfs->paths[i][k] == path->first_path[path->count][k])
					{
						path->occur = path->count;
						path->error++;
					}
		}
		dprintf(1, "PTDR3\n");
		//printf("%d\n", error);
		/*if (path->error > 1)
		{
			printf("%d-%d-%d-%d-%d\n", bfs->paths[0][], bfs->paths[0][], bfs->paths[i][2], bfs->paths[i][3], bfs->paths[i][4]);
		}*/
		if (path->error == 1)
		{
			path->first_path[path->nb_newfirst] = ft_intdup(path->first_path[path->nb_newfirst], bfs->paths[i], path->file[i]);
			path->new_file_first[path->nb_newfirst] = bfs->distance[i];
			path->nb_newfirst++;
		}
		else if ((path->file[path->occur] > bfs->distance[i]))
		{
            dprintf(1, "PTDR4\n");
			path->second_path[path->nb_newsecond] = ft_intdup(path->second_path[path->nb_newsecond], path->first_path[path->occur], path->file[path->occur]);
			path->new_file_second[path->nb_newsecond] = bfs->distance[path->occur];
			ft_bzero(&path->first_path[path->occur], bfs->distance[path->occur]);
			path->first_path[path->occur] = bfs->paths[i];
			path->new_file_first[path->occur] = bfs->distance[i];
			path->nb_newsecond++;
		}
		else if (path->new_file_first[path->occur] > bfs->distance[i])
		{
		    dprintf(1, "PTDR5\n");
			path->second_path[path->nb_newsecond] = ft_intdup(path->second_path[path->nb_newsecond], path->first_path[path->occur], path->new_file_first[path->occur]);
			path->new_file_second[path->nb_newsecond] = bfs->distance[path->occur];
			ft_bzero(&path->first_path[path->occur], bfs->distance[path->occur]);
			path->first_path[path->occur] = bfs->paths[i];
			path->new_file_first[path->occur] = bfs->distance[i];
			path->nb_newsecond++;
		}
		else
		{
		    dprintf(1, "PTDR6\n");
			path->second_path[path->nb_newsecond] = ft_intdup(path->second_path[path->nb_newsecond], bfs->paths[i], path->file[i]);
			path->new_file_second[path->nb_newsecond] = bfs->distance[i];
			path->nb_newsecond++;
		}
		i++;
	}
	printf("%d-%d-%d-%d-%d\n", path->second_path[1][0], path->second_path[1][1], path->second_path[1][2], path->second_path[1][3], path->second_path[1][4]);
	printf("%d-%d-%d-%d-%d-%d\n\n", path->second_path[0][0], path->second_path[0][1], path->second_path[0][2], path->second_path[0][3], path->second_path[0][4], path->second_path[0][5]);
	return (path->first_path);
}

/*int 	path_line_ant(t_map *map, t_display *display, t_cpt *cpt, t_path *path)
{
	int 	i;
	int 	j;

    i = 0;
	if (!(display->status_ant = malloc(sizeof(int) * map->inf.nb_fourmi)))
		return (0);
	display->ant_num = 0;
	display->path_size = 3;
	while (++display->ant_num < nb_ant + 1)
	{
		display->status_ant[i] = map->inf.start;
	}
	display->ant_finish = 0;
	display->nb_ant_cross = 0;
    display->ant_num = 1;
	while (display->ant_finish < map->inf.nb_fourmi)
	{
		i = 0;
		while (i < path->nb_first_path)
		{
			j = 0;
			cpt->p = 0;
			while (j < (path->nb_first_path + display->nb_ant_cross))
			{
				cpt->l = 1;
				cpt->m = 0;
				cpt->x = 0;
				while (cpt->m <= path->first_file[cpt->x])
			    {
                    if (display->ant_num > map->inf.nb_fourmi)
                        break;
                    printf("L%d-%d ", display->ant_num, path->first_path[cpt->p][cpt->l]);
                    if (first_path[cpt->p][cpt->l] == map->inf.end && display->ant_num <= map->inf.nb_fourmi)
                    {
                        cpt->x++;
                        cpt->m = 0;
                        display->ant_finish++;
                        break;
                    }
                    display->ant_num++;
                    if (path->first_path[cpt->p][cpt->l] == map->inf.end && display->ant_num >= map->inf.nb_fourmi)
                        break;
                    cpt->l++;
                    cpt->m++;
				}
				cpt->p++;
				j++;
				printf("\n");
			}
			i++;
		}
		display->ant_finish++;
	}
	return (0);
}*/

/*
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



	//new_path = clear_path(&map, &display, &path, &bfs);
	printf("%d-%d-%d\n", new_path[0][0], new_path[0][1], new_path[0][2]);
	//printf("%d-%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3], new_path[1][4]);
	printf("%d-%d-%d-%d\n", new_path[1][0], new_path[1][1], new_path[1][2], new_path[1][3]);
	printf("\n\n");
	//path_line_ant(new_path, new_copy_path, 1, 8, 10, 2, 1, file, file2);
	return (0);
}*/
