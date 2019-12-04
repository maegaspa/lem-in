int 	path_line_ant(int	**first_path, int **second_path, int start, int end, int nb_ant, int nb_first_path, int nb_second_path, int *first_file, int *second_file)
{
	int 	i;
	int 	j;
	int 	k;
	int 	l;
	int		m;
	int 	tmp;
	int 	ant_finish;
	int 	*status_ant;
	int 	nb_ant_cross;

	if (!(status_ant = malloc(sizeof(int) * nb_ant)))
		return (0);
	i = 0;
	while (i < nb_ant)
	{
		status_ant[i] = start;
		//printf("[%d]", status_ant[i]);
		i++;
	}
	ant_finish = 0;
	nb_ant_cross = 0;
	while (ant_finish < nb_ant)
	{
		i = 0;
		while (i < nb_first_path)
		{
			j = 0;
			k = 0;
			while (j < (nb_first_path + nb_ant_cross))
			{
				l = 0;
				//printf("[%d] == [%d]\n", path[k][l], status_ant[m]);
				while (l < first_file[j])
				{
					m = 0;
					while (m < nb_ant)
					{
						if (first_path[j][l] == status_ant[m])
						{
							if (l < first_file[j])
							{
								printf("%d || %d || %d\n", first_path[j][l + 1], l, l + 1);
								status_ant[m] = first_path[j][l + 1];
								//break;
								l++;
								
							}
							//l++;
						}
						//l++;
						//tmp = -1;
						//while (++tmp < nb_ant)
							//printf("L%d-%d\n", tmp, status_ant[tmp]);
						//printf("%d\n", status_ant[m]);
						//l++;
						m++;
					}
					//printf("%d\n", status_ant[m]);
					//printf("[%d]-[%d]\n", m, l);
					//printf("[%d] == [%d]\n", path[k][l], status_ant[m]);
					l++;
				}
				//status_ant[m] = first_path[k][l];
				j++;
			}
			i++;
		}
		ant_finish++;
	}
	return (0);
}