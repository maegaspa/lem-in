#include "../include/lemin.h"
#include <stdio.h>

t_link		*insert_link(char *val, int i)
{
	t_link *elem;

	if (!(elem = malloc(sizeof(t_link *))))
		return (NULL);
	if (!(elem->link = ft_strdup(val)))
		return (NULL);
	elem->index = i;
	elem->next = NULL;
	return (elem);
}

int		insert_name(t_name **name, char *val, int i)
{
	t_name *tmp;
	t_name *cpy_name;
	t_name *elem;

	tmp = NULL;
	cpy_name = *name;
	if (!(elem = malloc(sizeof(t_link))))
		return (0);
	if (!(elem->name = ft_strdup(val)))
		return (0);
	elem->index = i;
	while(cpy_name && cpy_name->name < val && cpy_name->index < i)
	{
		tmp = cpy_name;
		cpy_name = cpy_name->next;
	}
	elem->next = cpy_name;
	if (tmp)
		tmp->next = elem;
	else
		*name = elem;
	return (0);
}

void	clear(t_name **name, t_link **link)
{
	while(*name)
	{
		*name = (*name)->next;
		free(*name);
	}
	while(*link)
	{
		*link = (*link)->next;
		free(*link);
	}
}

int		list_len(t_name *name, t_link *link, int chose)
{
	t_name	*tmp_name;
	t_link	*tmp_link;
	int		n;

	n = 0;
	tmp_name = name;
	tmp_link = link;
	if (chose == 1)
		n = 0;
	if (chose == 0 || chose == 2)
		while(tmp_name)
		{
			tmp_name = tmp_name->next;
			n++;
		}
	if (chose == 1 || chose == 2)
		while(tmp_link)
		{
			tmp_link = tmp_link->next;
			n++;
		}
	return (n);
}

void	print_list(t_name *name, t_link *link)
{
	t_name	*tmp_name;
	t_link	*tmp_link;

	tmp_name = name;
	tmp_link = link;
	while(tmp_name)
	{
		printf("%d : [%s]\n", tmp_name->index, tmp_name->name);
		tmp_name = tmp_name->next;
	}
	while(tmp_link)
	{
		printf("%d : [%s]\n", tmp_link->index, tmp_link->link);
		tmp_link = tmp_link->next;
	}
}