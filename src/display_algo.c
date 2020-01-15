#include "../include/lemin.h"
#include <stdio.h>

int 	clear_path2(t_res *res, t_bfs *bfs, t_sort *sort)
{
	int 	i;
	int 	j;
	int 	k;
	int		count;
	int 	error;
	int 	occurrence;

	i = 1;
	occurrence = 0;
	if (!(sort->new_size_first = malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	if (!(sort->new_size_second = malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	if (!(sort->first_path = malloc(sizeof(int*) * bfs->nb_paths)))
		return (0);
	if (!(sort->second_path = malloc(sizeof(int*) * bfs->nb_paths)))
		return (0);
	sort->nb_path_first = 1;
	sort->nb_path_second = 0;
	sort->first_path[0] = res->paths[0];
	sort->new_size_first[0] = res->size_paths[0];
	while (i < bfs->nb_paths)
	{
		count = -1;
		error = 1;
		while (++count < sort->nb_path_first/* && j < res->size_paths[i]*/)
		{
			j = 0;
				while (++j < res->size_paths[i] - 1)
				{
					k = -1;
					while (++k < sort->new_size_first[count] - 1)
					{
						if (res->paths[i][j] == sort->first_path[count][j])
						{
							//printf("[%d] == [%d]{%d|%d|%d}\n", res->paths[i][j], sort->first_path[count][j], i, j, count);
							occurrence = count;
							error++;
						}
					}
				}
		}
		printf("{%d}\n", error);
		if (error == 1)
		{
			printf("%d\n", res->size_paths[i]);
			sort->first_path[sort->nb_path_first] = res->paths[i];
			sort->new_size_first[sort->nb_path_first] = res->size_paths[i];
			sort->nb_path_first++;
		}
		else if ((res->size_paths[occurrence] > res->size_paths[i]))
		{
			sort->second_path[sort->nb_path_second] = sort->first_path[occurrence];
			sort->new_size_second[sort->nb_path_second] = res->size_paths[occurrence];
			ft_bzero(&sort->first_path[occurrence], res->size_paths[occurrence]);
			sort->first_path[occurrence] = res->paths[i];
			sort->new_size_first[occurrence] = res->size_paths[i];
			sort->nb_path_second++;
		}
		else if (sort->new_size_first[occurrence] > res->size_paths[i])
		{
			sort->second_path[sort->nb_path_second] = sort->first_path[occurrence];
			sort->new_size_second[sort->nb_path_second] = res->size_paths[occurrence];
			ft_bzero(&sort->first_path[occurrence], res->size_paths[occurrence]);
			sort->first_path[occurrence] = res->paths[i];
			sort->new_size_first[occurrence] = res->size_paths[i];
			sort->nb_path_second++;
		}
		else
		{
			sort->second_path[sort->nb_path_second] = res->paths[i];
			sort->new_size_second[sort->nb_path_second] = res->size_paths[i];
			sort->nb_path_second++;
		}
		i++;
	}
	printf("[%d|%d]\n", sort->nb_path_first, sort->nb_path_second);
	return (1);
}

int 	nb_ant_int_path(t_map map, t_sort *sort, int ant, int index)
{
	int i;

	i = 0;
	while (i < sort->nb_path_first)
	{
		if (index >= sort->new_size_first[i])
		{
			sort->dispache[i]++;
			ant++;
		}
		if (ant == map.inf.nb_fourmi)
		{
			printf("[%d]\n", sort->dispache[0]);
			printf("[%d]\n", sort->dispache[1]);
			//need return index
			//nombre de ligne
			//printf("%d\n", index - 1);
			return(index);
		}
		i++;
	}
	return(nb_ant_int_path(map, sort, ant, index + 1));
}

int 	dispache_ant(t_map map, t_sort *sort, int nb_ligne)
{
	int reste;
	int *status_ant;
	int ant_finish;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int p;
	int q;
	int space;
	int ant_cross;
	int tmp;
	int ant_cross_max;
	int *status_partion;
	int *start_path;
	int *status_path;

	if (!(status_path = malloc(sizeof(int) * map.inf.nb_fourmi)))
		return (0);
	i = 0;
	while (i < map.inf.nb_fourmi)
	{
		status_path[i] = -1;;
		i++;
	}
	if (!(start_path = malloc(sizeof(int) * sort->nb_path_first)))
		return (0);
	i = 0;
	while (i < sort->nb_path_first)
	{
		start_path[i] = 0;
		i++;
	}
	if (!(status_ant = malloc(sizeof(int) * map.inf.nb_fourmi)))
		return (0);
	i = 0;
	while (i < map.inf.nb_fourmi)
	{
		status_ant[i] = map.inf.start;
		i++;
	}
	if (!(status_partion = malloc(sizeof(int) * sort->nb_path_first)))
		return (0);
		i = 0;
	while (i < sort->nb_path_first)
	{
		status_partion[i] = 0;
		i++;
	}
	reste = map.inf.nb_fourmi % sort->nb_path_first;
	ant_finish = 0;
	ant_cross_max = sort->nb_path_first;
	l = 0;
	tmp = 1;
	ant_cross = 1;
	m = 0;
	n = 0;
	space = 1;
	while (l < nb_ligne)
	{
		i = 0;
		if ((tmp * sort->nb_path_first) <= map.inf.nb_fourmi)
			ant_cross_max = tmp * sort->nb_path_first;
		if (ant_cross + ant_finish == map.inf.nb_fourmi - reste + 1)
		{
			ant_cross_max += reste;
		}
		m = 0;
		while (i < ant_cross_max)
		{
			j = 0;
			n = 0;
			while (j < sort->nb_path_first)
			{
				if (status_partion[j] == sort->dispache[j])
				{
					if (i < map.inf.nb_fourmi && (!(status_ant[i] == map.inf.start)))
							j = status_path[i];
					else
					{
						q = 0;
						p = 0;
						while (q < sort->nb_path_first)
						{
							if (start_path[q] == 0 && j != q && status_partion[q] != sort->dispache[q])
							{
								p = 1;
								j = q;
								break;
							}
							q++;
						}
						if (p != 1)
						{
							m = 1;
							i++;
							break;
						}
					}
				}
				k = 0;
				while (k < sort->new_size_first[j])
				{
					if ((i < map.inf.nb_fourmi) && sort->first_path[j][k] == status_ant[i] && sort->first_path[j][k] != map.inf.end)
					{
						//ft_printf("[%d][%d][%d]", i, ant_finish, space);
						if (space == 1)
							space = 0;
						else
							ft_printf(" ");
						if (status_ant[i] == map.inf.start)
						{
							start_path[n] = 1;
							ant_cross++;
							n++;
						}
						if (status_ant[i] == map.inf.start)
							status_partion[j]++;
						status_ant[i] = sort->first_path[j][k + 1];
						status_path[i] = j;
						if (sort->first_path[j][k + 1] == map.inf.end)
						{
							ant_finish++;
							ant_cross--;
						}
						ft_printf("L%d-%s", i + 1, map.new_name[status_ant[i]]);
						break;
					}
					k++;
				}
				i++;
				j++;
			}
			if (i % sort->nb_path_first == 0)
			{
				if (i == sort->nb_path_first * tmp && tmp <= map.inf.nb_fourmi)
					tmp++;
			}
			if (m == 1)
			{
				break;
			}
		}
		p = 0;
		while (p < sort->nb_path_first)
		{
			start_path[p] = 0;
			p++;
		}
		printf("\n");
		space = 1;
		l++;
	}
	return (0);
}

int 	display_algo(t_map map, t_res *res, t_bfs *bfs)
{
	t_sort	sort;
	int 	i;
	int 	j;
	int 	nb_line;

	clear_path2(res, bfs, &sort);
	i = -1;
	printf("----------------------------------------------\n");
	while (++i < sort.nb_path_first)
	{
		j = -1;
		while (++j < sort.new_size_first[i] + 1)
		{
			printf("%s ", map.new_name[sort.first_path[i][j]]);
		}
		printf("\n");
	}
	printf("----------------------------------------------\n");
	i = -1;
	while (++i < sort.nb_path_second)
	{
		j = -1;
		while (++j < sort.new_size_second[i] + 1)
		{
			printf("%d ", sort.second_path[i][j]);
		}
		printf("\n");
	}
	printf("----------------------------------------------\n");
	i = -1;
	if (!(sort.dispache = malloc(sizeof(int) * sort.nb_path_first)))
		return (0);
	i = -1;
	while (++i < sort.nb_path_first)
		sort.dispache[i] = 0;
	nb_line = nb_ant_int_path(map, &sort, 0, 0);
	dispache_ant(map, &sort, nb_line);
	return (0);
}