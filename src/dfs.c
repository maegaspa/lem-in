/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dfs.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 11:22:21 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 13:21:55 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	add_node_to_q(int node, t_map *map)
{
	map->dfs.queue[map->dfs.q_size] = node;
	map->dfs.q_size++;
}

void	add_node_to_v(int node, t_map *map)
{
	map->dfs.visited[map->dfs.v_size] = node;
	map->dfs.v_size++;
}

void	remove_node_q(t_map *map)
{
	map->dfs.queue[map->dfs.q_size - 1] = -1;
	map->dfs.q_size--;
}
void	remove_node_v(t_map *map)
{
	map->dfs.visited[map->dfs.v_size - 1] = -1;
	map->dfs.v_size--;
}

void	print_q_v(t_map *map)
{
	int i;
	//	printf("queue-size : [%d]\n", map->bfs.q_size);
	i = 0;
	printf("queue : ");
	while (i != map->dfs.q_size)
	{
		printf("[%d]", map->dfs.queue[i]);
		i++;
	}
	printf("\n");

	//	printf("visited-size : [%d]\n", map->bfs.v_size);
	i = 0;
	printf("visited : ");
	while (i != map->dfs.v_size)
	{
		printf("[%d]", map->dfs.visited[i]);
		i++;
	}
	printf("\n");
}

int		not_visited(int i, t_map *map)
{
	int x;

	x = 0;
	while (x != map->dfs.v_size)
	{
		if (map->dfs.visited[x] == i)
			return (0);
		x++;
	}
	return (1);
}

void	print_visited(t_map *map)
{
	int x = 0;

	while (x != map->dfs.v_size)
	{
		printf("%d-", map->dfs.visited[x]);
		x++;
	}
}

void	refresh_q_v(t_map *map)
{
	int		prev_node;
	int		node;
	int		x;

	x = 0;
	prev_node = map->dfs.queue[map->dfs.q_size - 1];
node = map->dfs.queue[map->dfs.q_size - 2];
	remove_node_q(map);
	print_q_v(map);
	
	if (prev_node == map->inf.end)
	{
		if (map->matrix[node][prev_node] == 1)
			remove_node_v(map);
	}
	else
	{
		x = map->dfs.v_size;
		while (x > map->dfs.q_size)
		{
			if (map->matrix[node][map->dfs.visited[x - 1]] == 0)
				remove_node_v(map);
			x--;
		}
	}
	if (map->dfs.q_size == 1)
	{
		x = map->dfs.v_size;
		while (x != 1)
		{
			remove_node_v(map);
			x--;
		}
	}
}

void	dfs(t_map *map, int node)
{
	int i;
	int dead_end;
	

	dead_end = 1;
	print_q_v(map);

	i = 0;
	if (node != map->inf.end)
	{
		while (i != map->inf.size_name)
		{
			if (map->matrix[node][i] == 1 && not_visited(i, map))
			{
				//printf("node %d is connected to node %d\n", node, i);
				add_node_to_q(i, map);
				add_node_to_v(i, map);
				//printf("\n\nNEW BFS : node %d\n\n", i);
				dfs(map, i);
				printf("reprise DFS node%d\n", node);
				dead_end = 0;
			}
			i++;
		}
	}
	refresh_q_v(map);
}


int		*malloc_int_tab(int size)
{
	int	*tab;
	if (!(tab = (int *)malloc(sizeof(int) * size)))
		return (0);
	return (tab);
}

void	init_dfs(t_map *map)
{
	map->dfs.queue = malloc_int_tab(map->inf.size_name);
	map->dfs.visited = malloc_int_tab(map->inf.size_link);
	map->dfs.v_size = 0;
	map->dfs.v_size = 0;
}

void	begin_dfs(t_map *map, int start_node)
{
	init_dfs(map);
	add_node_to_v(start_node - 1, map);
	add_node_to_q(start_node - 1, map);

	dfs(map, start_node - 1);
}

