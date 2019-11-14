/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: maegaspa <maegaspa@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 15:36:20 by maegaspa     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 15:36:20 by maegaspa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int    init_bfs(t_map *map)
{
    int i;
    int n;

    i = 0;
    n = 0;
    if (!(map->queue = malloc(sizeof(int) * map->inf.size_name)))
        return (0);
    if (!(map->visited = malloc(sizeof(int) * map->inf.size_name)))
        return (0);
    map->visited[0] = map->inf.start;
    while (i < map->inf.size_name)
    {
        if (map->matrix[map->inf.start][i] == 1)
        {
            printf("i = %d\n", i);
            map->queue[n] = map->matrix[map->inf.start][i];
            n++;
        }
        i++;
    }
    return (1);
}

void    bfs(t_map *map)
{
    int n;
    int p;

    n = 0;
    p = 0;
    map->i = map->i + 1;
    if (map->first == 0)
        init_bfs(map);
    while (map->queue && map->i++ < map->inf.size_name)
    {
        while (n < map->inf.size_name)
        {
            if (map->matrix[0][map->i] == 1 && map->i != map->visited[n])
            {
                printf("map->i = %d\n", map->i);
                map->queue[++map->front] = map->matrix[0][map->i];
                while (p < map->inf.size_name)
                {
                    printf("p = %d\n", p);
                    printf("queue[%d] = %d\n", p, map->queue[p]);
                    printf("visited[%d] = %d\n", p, map->visited[p]);
                    p++;
                }
                map->first = 1;
                bfs(map);
            }
            n++;
        }
    }
}

/*struct      vertex
{
    char    label;
    int     visited;
}

struct  vertex* lstvertices[map->inf.size_name];

void    addvertex(char label)
{
    struct vertex* vertex = (struct Vertex*) malloc(sizeof(struct vertex));

    vertex->label = label;
    vertex->visited = 0;
    lstvertices[vertexcount++] = vertex;
}

void    insert(int data)
{
    queue[++rear] = data;
    queueitemcount++;
}

void        bfs(int vert, t_map *map)
{
	int **tab;
	int *queue;
	int *visited;
	int front;
	int rear;
	int n;

	if (!(tab = malloc(sizeof(int *) * map->inf.size_name)))
		return (0);
	if (!(queue = malloc(sizeof(int) * map->inf.size_name)))
	    return (0);
	i = 1;
	rear = -1;
	front = 0;
	while (i++ <= n)
	{
		if (!(tab[vert] = malloc(sizeof(int) * map->inf.size_name)))
			return (0);
		if (tab[vert][i] && !visited[i])
			queue[++rear] = i;
	}
	if (front <= rear)
	{
		visited[queue[front]] = 1;
		bfs(queue[front++], map);
	}
}*/


/*
int         isEmpty(t_queue *q)
{
    if (q->rear == -1)
        return (1);
    else
        return (0);
}

struct node;

struct queue* createQueue();

void        bfs(t_map *map, int startvertex)
{
    int currentvertex;
    int *tmp;
    int adjvertex;
    struct queue* q = createQueue();
    struct node* tmp = map->matrix[currentvertex];

    q = createQueue();
    map->visited[startvertex] = 1;
    enqueue(q, startvertex);
    while (!isEmpty(q))
    {
        currentvertex = dequeue(q);
        printf("visited %d\n", currentvertex);
        //TROUVER CONDITION POUR BOUCLER SUR TMP
        while (tmp)
        {
            adjvertex = tmp->vertex;
            if (map->visited[][] == 0)
            {
                map->visited[] = 1;
                enqueue(q, adjvertex);
            }
            tmp = tmp->next;
            //ICI TMP PASSE AU NOEUD SUIVANT
        }
    }

}

struct node
{
    int vertex;
    struct node* next;
}

struct queue* createQueue()
{
    struct queue* q = malloc(sizeof(struct queue));

    q->front = -1;
    q->rear = -1;
    return (q);
}

void        enqueue(t_queue *q, int value)
{
    if (q->rear == map->inf.size_name - 1)
        printf("\nQueue is Full!!");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}


int         dequeue(t_queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return (item);
}*/
