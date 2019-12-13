#include <stdio.h>
#include <stdlib.h>

//ancien com peut peut etre d'aider meme si c'est fais a moitier
//contions qui check le status de la fourmie si elle est pas en movement
//sinon le j ne dois pas etre incrementer pour pouvoir faire le plus rapide
//ducoup mettre une tmp++ au temps ecoule pour le j (et dissocier le j avec j1 et j2 pour le surplus)
//et add le reste tout en faisant un calcul avec le nombre de fourmie restante et le chemin le plus court pour pouvoir dispache plus opti

//les 2 fonctions serve a calculer la partition des chemin type (ex: 4chemin[7][5][5][3]) et le nombre de ligne)

int 	nb_ant_int_path2(int *files, int nb_file, int nb_ant, int *dispache, int ant, int index)
{
	int i;
	int j;


	i = 0;
	while (i < nb_file)
	{
		if (index >= files[i])
		{
			dispache[i]++;
			ant++;
		}
		if (ant == nb_ant)
		{
			//need return index
			//nombre de ligne
			printf("%d\n", index - 1);
			return(index);
		}
		i++;
	}
	return(nb_ant_int_path2(files, nb_file, nb_ant, dispache, ant, index + 1));
}

int 	*nb_ant_int_path(int *files, int nb_file, int nb_ant, int *dispache, int ant, int index)
{
	int i;
	int j;


	i = 0;
	while (i < nb_file)
	{
		if (index >= files[i])
		{
			dispache[i]++;
			ant++;
		}
		if (ant == nb_ant)
		{
			//need return index
			//printf("%d\n", index - 1);
			//partition
			return(dispache);
		}
		i++;
	}
	return(nb_ant_int_path(files, nb_file, nb_ant, dispache, ant, index + 1));
}

int 	dispache_ant(int *files, int nb_file, int nb_ant, int **path, int end, int nb_ligne, int *partition)
{
	int dispache;
	int reste;
	int *status_ant;
	int ant_finish;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int ant_cross;
	int tmp;
	int ant_cross_max;
	int start = 1;
	int *status_partion;
	int ptdr;

	//status_ant sert a voir la position des fourmies
	if (!(status_ant = malloc(sizeof(int) * nb_ant)))
		return (0);
		i = 0;
	while (i < nb_ant)
	{
		status_ant[i] = start;
		//printf("[%d]", status_ant[i]);
		i++;
	}
	//status_partion sert a savoir la partition actuelle des fourmies
	if (!(status_partion = malloc(sizeof(int) * nb_file)))
		return (0);
		i = 0;
	while (i < nb_file)
	{
		status_partion[i] = 0;
		//printf("[%d]", status_ant[i]);
		i++;
	}
	printf("[%d][%d][%d][%d]\n", partition[0], partition[1], partition[2], partition[3]);
	dispache = nb_ant / nb_file;
	reste = nb_ant % nb_file;
	printf("%d/-/%d\n", dispache, reste);
	ant_finish = 0;
	ant_cross_max = nb_file;
	l = 0;
	tmp = 1;
	ant_cross = 1;
	m = 0;
	n = -1;
	ptdr = 0;
	//de l a nombre de ligne calculer
	while (l < nb_ligne)
	{
		// printf("LIGNE MAX %d\n", nb_ligne);
		i = 0;
		// calcul pour ant_cross_max dynamique
		if ((tmp * nb_file) <= nb_ant)
			ant_cross_max = tmp * nb_file;
		if (ant_cross + ant_finish == nb_ant - reste + 1)
		{
			ant_cross_max += reste;
		}
		//m = 0;
		//printf("i = %d\n", i);
		//ant_cross_max sert a faire a deplace un nombre de fourmie dynamique le i change et le ant_cross_max change aussi ****
		while (i < ant_cross_max)
		{
			j = 0;
			//printf("\n\tant_cross_max = %d\n", ant_cross_max);
            //printf("status_ant[%d] = %d\n", i, status_ant[i]);
//		    if (partition[j] == status_partion[j])
//		        i--;
			//nb nombre de chemin
			//m = 0;
			if (i + 1 == nb_ant)
			{
//			    if (status_ant[i] == start)
//			    {
//			        m = 1;
//			        break;
//			    }
                m++;
                ptdr = i;
			    if (m == 2)
			    {
			        printf("L%d-%d ", ptdr, path[0][1]);
			    }
			    if (m == 3)
			    {
			        printf("L%d-%d L%d-%d ", ptdr, end, ptdr + 1, path[0][1]);
			    }
			    if (m == 4)
			        printf("L%d-%d ", ptdr + 1, end);
			    break;
			}
			if (i == nb_ant - nb_file)
			{
			    i--;
			}
			while (j < nb_file)
			{

				//pour optimiser le nombre de ligne LE PROBLEME EST ICI
				//je pense que la condition est un peut zobé mais trouver equivalent ou je sais pas
				//if (status_partion[j] == partition[j] && status_ant[i] == start)
				//printf("nb_ant - i == %d et nb_file == %d\n", nb_ant - i, nb_file);
				//if (status_partion[j] == partition[j] && status_ant[i] == start)
				//printf("nb_ant - (i + 1) = %d\n", (nb_ant - (i + 1)));
				// printf("PART[j] [%d] - STAT PART[j] [%d]\n",partition[j], status_partion[j]);

//				if (partition[j] == status_partion[j] && status_ant[i] == start)
//				{
//				    //printf("partition[%d] = %d\n status_partion[%d] = %d\n", j, partition[j], j, status_partion[j]);
//				    //printf("status_ant[%d] = %d\n", i, status_ant[i]);
//					//printf("BREAK GO TO \\ n \n");
//				    //printf("\n");
//				    m = 1;
//				    //break;
//				}
				/*if (files[0] < (nb_ant - (i + 1)) && nb_file == (nb_ant - (i + 1)))
				{
				    j = 0;
					m = 1;
				    break;
				}*/
				k = 0;
				/*if (i == 15)
				    printf("oui ?\n");*/
				//parcour dans la size d'un chemin
				while (k < files[j])
				{
//				    if (i == 15)
//				        printf("files[%d] = %d\n", j, files[j]);
				    if (partition[j] == status_partion[j] && status_ant[i] == start)
				    {
				        //m = 1;
				        //i--;
				        break;
					}
					//nombre de fourmis qui sont en mouvement dans les chemin
					if (status_ant[i] == start)
					{
						ant_cross++;
					}
					//stockage de la position de la fourmie
					if (path[j][k] == status_ant[i] && path[j][k] != end)
					{
						//printf("\n\tpath[j][k] = %d -- status[i] = %d\n", path[j][k], status_ant[i]);
						//stock le nombre de fourmie dans chaque chemin (peut etre en mouvement ou en arriver sert ici ****)
						if (status_ant[i] == start)
							status_partion[j]++;
					    //printf("status_partion[%d] = %d\n", j, status_partion[j]);
						//stockage de la position de la fourmie
						status_ant[i] = path[j][k + 1];
						//met de position en mouvement a terminer
						if (path[j][k + 1] == end)
						{
							ant_finish++;
							ant_cross--;
						}
						printf("L%d-%d ", i + 1, status_ant[i]);
						break;
					}
					k++;
				}

				i++;
				j++;
			}
			//calcul qui sert a savoir le ant_cross_max
			if (i % nb_file == 0)
			{
				if (i == nb_file * tmp && tmp <= nb_ant)
					tmp++;
			}
//			if (m == 1)
//			{
//				break;
//			}
		}
        if (m != 4)
		    printf("\n");
		l++;
	}
	return (0);
}

int 	main(void)
{
	//Le nombre de fourmie dois toujours superieur a la size du plus petit chemin sinon marche pas ici mais marche bien sinon
	int nb_ant = 200;
	int nb_file = 4;
	int file[4] = {3, 5, 5, 6};
	int file2[2] = {5, 5};
	int i = 0;
	int tmp = 2147483647;
	int nb_same_path = 1;
	int **path;
	int *test;
	int *dispache;
	int *dispache2;
	int index;

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
	if (!(dispache = malloc(sizeof(int) * nb_file)))
		return (0);

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
	//NE FAIS PAS ATTENTION A CA !
	//c'est chelou mais c'est des condition test avant !
	tmp = (tmp - 2) * nb_same_path;
	if (nb_ant <= tmp)
		//mettres les chemins les plus court
		dispache_ant(file2, 2, nb_ant, path, 6, index, test);
		//printf("%d|*|*|%d\n", nb_ant, tmp);
	else
		//mettres les tout les chemin de l'algo
		dispache[0] = 0;
		dispache[1] = 0;
		dispache[2] = 0;
		dispache[3] = 0;
		dispache2[0] = 0;
		dispache2[1] = 0;
		dispache2[2] = 0;
		dispache2[3] = 0;
		test = nb_ant_int_path(file, nb_file, nb_ant, dispache, 0, 0);
		printf("[%d][%d][%d][%d]\n", test[0],test[1],test[2],test[3]);
		index = nb_ant_int_path2(file, nb_file, nb_ant, dispache2, 0, 0);
		//printf("[%d][%d][%d][%d]\n", test[0],test[1],test[2],test[3]);
		dispache_ant(file, nb_file, nb_ant, path, 6, index, test);
		//dispache_ant(file, 3);
	return (0);
}