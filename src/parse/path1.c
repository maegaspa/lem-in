/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path1.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 12:38:33 by maegaspa     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 06:16:34 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int            path_1(t_map *map)
{
    int x;
    int num;

    x = 0;
    num = 0;
    while (x < map->inf.size_name)
    {
        if (!(map->path.n_path = malloc (sizeof(int) * x)))
            return (0);
        if (map->matrix[map->inf.start][x] == 1)
            {
            map->path.n_path[num] = num + 1;
            map->path.next_room = x;
            //printf("map->inf.start = %d\n", map->inf.start);
            printf("map->path.n_path[%d] = %d \n", num, map->path.n_path[num]);
            printf("next_room = %d\n", map->path.next_room);
            // path_2(map, num);
            num++;
        }
        x++;
    }
    return (1);
}

/*int            path_2(t_map *map, int num)
{
    int x;

    x = 0;
    map->path.next_room2 = map->path.next_room;
    while (x < map->inf.size_name) //&& path_2(map, num))
    {
       if (map->matrix[map->path.next_room2][x] == 1)// && map->path.next_room2 != map->inf.start)
       {
            //map->path.next_room2 != map->inf.start
            //map->path.n_path[num] = num;
            map->path.next_room2 = x;
            printf("PATH 2 : next_room2 = %d\n", map->path.next_room2);
           // printf("PATH 2 : next_room = %d\n", map->path.next_room);
            printf("PATH 2 : map->path.n_path[%d] = %d \n", num, map->path.n_path[num]);
            //path_2(map, num);
            //num++;
       }
       x++;
    }
    return (1);
}*/
