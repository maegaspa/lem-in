#include <stdio.h>
#include <stdlib.h>
#include "libft/includes/ft_printf.h"

int 	dispache_ant(int *files, int nb_file, int nb_ant, int **path, int end)
{
	int dispache;
	int reste;
	int *status_ant;
	int ant_finish;
	int i;
	int j;
	int k;
	int l;
	int tmp;
	int ant_cross;
	int start = 1;

	if (!(status_ant = malloc(sizeof(int) * nb_ant)))
		return (0);
		i = 0;
	while (i < nb_ant)
	{
		status_ant[i] = start;
		//printf("[%d]", status_ant[i]);
		i++;
	}
	dispache = nb_ant / nb_file;
	reste = nb_ant % nb_file;
	printf("%d/-/%d\n", dispache, reste);
	ant_finish = 0;
	ant_cross = nb_file;
	l = 0;
	tmp = 1;
	while (l < nb_ant / nb_file + nb_file)
	{
		i = 0;
		if ((tmp * nb_file) <= nb_ant)
			ant_cross = tmp * nb_file;
		while (i < ant_cross)
		{
			//printf(" 2 \n");
			//printf("%d++%d\n", i, ant_cross);
			j = 0;
			while (j < nb_file)
			{
				k = 0;
				while (k < files[j])
				{
					//printf("%d--%d\n", path[j][k], i);
					if (path[j][k] == status_ant[i] && path[j][k] != end)
					{
						status_ant[i] = path[j][k + 1];
						ft_printf("L%d-%d ", i + 1, status_ant[i]);
						//printf("L%d-%d ", i, status_ant[i]);
						break;
					}
					k++;
				}
				i++;
				//contions qui check le status de la fourmie si elle est pas en movement
				//sinon le j ne dois pas etre incrementer pour pouvoir faire le plus rapide
				//ducoup mettre une tmp++ au temps ecoule pour le j (et dissocier le j avec j1 et j2 pour le surplus)
				//et add le reste tout en faisant un calcul avec le nombre de fourmie restante et le chemin le plus court pour pouvoir dispache plus opti
				j++;
			}
			if (i % nb_file == 0)
			{
				if (i == nb_file * tmp && tmp <= nb_ant)
					tmp++;
				//printf(" 1 \n");
				//ant_cross = ;
				//printf("%d/%d\n", i, dispache);
			}
			//i++;
		}
		printf("\n");
		l++;
	}
	return (0);
}


int 	main(void)
{
	int nb_ant = 10658;
	int nb_file = 4;
	int file[4] = {3, 5, 5, 6};
	int file2[2] = {5, 5};
	int i = 0;
	int tmp = 2147483647;
	int nb_same_path = 1;
	int **path;

	if (!(path = malloc(sizeof(int*) * 4)))
		return (0);
	if (!(path[0] = malloc(sizeof(int) * 3)))
		return (0);
	path[0][0] = 1;
	path[0][1] = 5;
	path[0][2] = 6;
	if (!(path[1] = malloc(sizeof(int) * 5)))
		return (0);
	path[1][0] = 1;
	path[1][1] = 2;
	path[1][2] = 3;
	path[1][3] = 4;
	path[1][4] = 6;
	if (!(path[2] = malloc(sizeof(int) * 5)))
		return (0);
	path[2][0] = 1;
	path[2][1] = 7;
	path[2][2] = 8;
	path[2][3] = 9;
	path[2][4] = 6;
	if (!(path[3] = malloc(sizeof(int) * 6)))
		return (0);
	path[3][0] = 1;
	path[3][1] = 10;
	path[3][2] = 11;
	path[3][3] = 12;
	path[3][4] = 13;
	path[3][5] = 6;

	while (i < nb_file)
	{
		if (file[i] <= tmp)
		{
			if (file[i] == tmp)
				nb_same_path++;
			else
				nb_same_path = 1;
			tmp = file[i];
		}
		i++;
	}
	tmp = (tmp - 2) * nb_same_path;
	if (nb_ant <= tmp)
		//mettres les chemins les plus court
		dispache_ant(file2, 2, nb_ant, path, 6);
		//printf("%d|*|*|%d\n", nb_ant, tmp);
	else
		//mettres les tout les chemin de l'algo
		dispache_ant(file, nb_file, nb_ant, path, 6);
		//dispache_ant(file, 3);
	return (0);
}
