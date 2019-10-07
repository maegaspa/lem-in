/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 12:57:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 12:58:07 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "../include/lemin.h"
#include <stdio.h>

void insert_link(slist1 **sl, char *Val, int i)
{
       	slist1 *tmp = NULL;
        slist1 *csl = *sl;
        slist1 *elem1 = malloc(sizeof(slist1));
        if(!elem1) exit(EXIT_FAILURE);
        elem1->link = Val;
        elem1->compt = i;
        while(csl && csl->link < Val && csl->compt < i)
        {
            tmp = csl;
            csl = csl->suiv;
        }
        elem1->suiv = csl;
        if(tmp) tmp->suiv = elem1;
        else *sl = elem1;
}

void insert_name(slist **sl, char *Val, int i)
{
        slist *tmp = NULL;
        slist *csl = *sl;
        slist *elem = malloc(sizeof(slist));
        if(!elem) exit(EXIT_FAILURE);
        elem->valeur = Val;
        elem->compt = i;
        while(csl && csl->valeur < Val && csl->compt < i)
        {
            tmp = csl;
            csl = csl->suiv;
        }
        elem->suiv = csl;
        if(tmp) tmp->suiv = elem;
        else *sl = elem;
}

void Clear(slist **sl, slist1 **sl1)
{
        slist *tmp;
        while(*sl)
          {
             tmp = (*sl)->suiv;
             free(*sl);
             *sl = tmp;
          }
    slist1 *tmp1;
        while(*sl1)
          {
             tmp1 = (*sl1)->suiv;
             free(*sl1);
             *sl1 = tmp1;
          }
}

int Length(slist *sl, slist1 *sl1, int i)
{
        int n = 0;
   if (i == 0 || i == 2)
   {
        while(sl)
          {
              n++;
              sl = sl->suiv;
          }
   }
   if (i == 1)
   	n = 0;
    if (i == 1 || i == 2)
    {
         while(sl1)
          {
              n++;
              sl1 = sl1->suiv;
          }
      }
        return n;
}

void View(slist *sl, slist1 *sl1)
{
       while(sl)
          {
             printf("%d : [%s]\n", sl->compt, sl->valeur);
             sl = sl->suiv;
          }
       while(sl1)
          {
            printf("%d : [%s]\n", sl1->compt, sl1->link);
            sl1 = sl1->suiv;
          }
}

unsigned int	count_word(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

int	parser(slist **list, slist1 **list1, t_info *inf)
{
	char	*line;
	int		info;
	int		nb_fourmie;
	int 	i;
	char	**split;

	line = NULL;
	nb_fourmie = -1;
	info = 0;
	i = 1;
	while (get_next_line(0, &line))
	{
		if (line[0] != '#' && line[0] != 'L' && !info)
		{
			if (count_word(line, ' ') && !(ft_strchr(line, '-')))
			{
				nb_fourmie = ft_atoi(line);
				info++;
			}
		}
		//printf("[%s]\n", line);
		if (ft_strstr(line, "##start"))
			inf->start = i;
		if (ft_strstr(line, "##end"))
			inf->end = i;
		if (line[0] != '#' && line[0] != 'L' && info > 1 && (count_word(line, '-') == 1 && !(ft_strchr(line, '-'))))
		{
			//printf("1 [%s]\n", line);
			split = ft_strsplit(line, ' ');
			insert_name(list, split[0], i);
			i++;
		}
		if (line[0] != '#' && line[0] != 'L' && count_word(line, '-') == 2 && ft_strchr(line, '-'))
		{
			//printf("2 [%s]\n", line);
			split = ft_strsplit(line, ' ');
			insert_link(list1, split[0], i);
			i++;
		}
		info++;
		ft_strdel(&line);
	}
	printf("FOURMIE : [%d]\n", nb_fourmie);
	printf("Nb d'elements 1 list : [%d]\n", Length(*list, *list1, 0));
	printf("Nb d'elements 2 list : [%d]\n", Length(*list, *list1, 1));
	printf("Nb d'elements totals : [%d]\n", Length(*list, *list1, 2));
    View(*list, *list1);
    printf("------------------\n");
    printf("Start : [%d] | End : [%d]\n", inf->start, inf->end);
	return (0);
}

int	main(void)
{
	slist *list;
	slist1 *list1;
	t_info info;

	list = NULL;
	list1 = NULL;
	info.start = 0;
	info.end = 0;

	parser(&list, &list1, &info);
	Clear(&list, &list1);
	return (0);
}