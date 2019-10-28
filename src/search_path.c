#include "../include/lemin.h"
#include <stdio.h>

int 	search_jonc(t_map	*map)
{
	int i;
	int j;
	int tmp;
	int prec;
	int tmp_j;
	int cont;
	int save1;
	int save2;
	int save3;
	int save4;
	int yes[9];
	int che[9];
	int no[9];
	int oui;

	i = 0;
	//t_bzero(yes, 9);
	yes[0] = 0;
	yes[1] = 0;
	yes[2] = 0;
	yes[3] = 0;
	yes[4] = 0;
	yes[5] = 0;
	yes[6] = 0;
	yes[7] = 0;
	yes[8] = 0;
	che[0] = 0;
	che[1] = 0;
	che[2] = 0;
	che[3] = 0;
	che[4] = 0;
	che[5] = 0;
	che[6] = 0;
	che[7] = 0;
	che[8] = 0;
	no[0] = 0;
	no[1] = 0;
	no[2] = 0;
	no[3] = 0;
	no[4] = 0;
	no[5] = 0;
	no[6] = 0;
	no[7] = 0;
	no[8] = 0;
	printf("%d\n", map->inf.size_name);
	printf("Start :%d\n", map->inf.start);
	printf("End : %d\n", map->inf.end);
	j = 0;
	tmp = map->inf.start;
	prec = -1;
	save1 = -1;
	save2 = -1;
	oui = 0;
	while (i < 150)
	{
		j = 0;
		while (j < map->inf.size_name)
		{
			//printf("|%d+%d+%d+%d|\n", yes[j], tmp, j, map->matrix[tmp][j]);
			/*int p = -1;
			while (++p < 9)
				printf("%d ", no[p]);
			printf("\n");*/
			if (map->matrix[tmp][j] == 1 && prec != j && yes[j] != 1 && no[tmp] != 1)
			{
				if (save3 == tmp && save4 == j && oui)
				{
					//printf("salut\n");
					j++;
					oui = 0;
				}
				else
				{
					tmp_j = j;
					cont = 0;
					while (tmp_j < map->inf.size_name)
					{
						if (map->matrix[tmp][tmp_j] == 1 && prec != tmp_j && yes[tmp_j] != 1)
						{
							cont++;
							//printf("|%d+%d+%d+%d==\n", yes[j], tmp, j, map->matrix[tmp][j]);
						}
						tmp_j++;
					}
					//printf("[%d]\n", cont);
					if (cont > 1)
					{
						save1 = tmp;
						save2 = j;
						che[0] = 0;
						che[1] = 0;
						che[2] = 0;
						che[3] = 0;
						che[4] = 0;
						che[5] = 0;
						che[6] = 0;
						che[7] = 0;
						che[8] = 0;
						//printf("[%d][%d][%d][%d]\n", save1, tmp, save2, j);
					}
					else
					{
						che[tmp] = 1;
					}
					//printf("|%d|\n", yes[tmp]);
					yes[tmp] = 1;
					printf(" %d-", tmp);
					prec = tmp;
					//ft_swap(&j, &tmp);
					tmp = j;
					if (tmp == map->inf.end)
					{
						printf(" %d-\n", tmp);
						int o = -1;
						while (++o < 9)
							printf("%d ", che[o]);
						printf("\n");
						//printf("[%d|%d]\n", save1, save2);
						yes[0] = 0;
						yes[1] = 0;
						yes[2] = 0;
						yes[3] = 0;
						yes[4] = 0;
						yes[5] = 0;
						yes[6] = 0;
						yes[7] = 0;
						yes[8] = 0;

						no[0] = che[0];
						no[1] = che[1];
						no[2] = che[2];
						no[3] = che[3];
						no[4] = che[4];
						no[5] = che[5];
						no[6] = che[6];
						no[7] = che[7];
						no[8] = che[8];
						//printf("[%d-%d-%d-%d-%d-%d-%d-%d-%d-]\n", yes[0], yes[1], yes[2], yes[3], yes[4], yes[5], yes[6], yes[7], yes[8]);
						tmp = map->inf.start;
						prec = -1;
						oui = 1;
						save3 = save1;
						save4 = save2;					
					}
					break;
				}
			}
			else
				j++;
		}
		i++;
	}
printf("\n");
	/*while (i < map->inf.size_name)
	{
			tmp_j = 0;
			tmp_i = i;
			k = 0;
			while (tmp_j < map->inf.size_name || tmp_i < map->inf.size_name)
			{
				if (tmp_j >= map->inf.size_name || tmp_i >= map->inf.size_name)
					break;
				//printf("|%d|\n", map->matrix[tmp_i][tmp_j]);
				//printf("}[%d][%d][%d]{\n", tmp_i, tmp_j, k);
				//printf("%d\n", map->matrix[tmp_i][tmp_j]);
				if (map->matrix[tmp_i][tmp_j] == 1 && (tmp_j < map->inf.size_name || tmp_i < map->inf.size_name))
				{
					printf("%s-%s | ", map->map_name[tmp_j], map->map_name[tmp_i]);
					k++;
				}
				tmp_j++;
				tmp_i++;
			}
			//printf("--[%d]--\n", tmp_j);
			printf("\nSize path [%d]\n", k);
		//printf("--[%d]\n", i);
		i++;
	}*/
	return (0);
}