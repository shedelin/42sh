/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetit <apetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 15:56:07 by apetit            #+#    #+#             */
/*   Updated: 2014/06/24 18:19:16 by apetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "sh.h"

t_hist		*sh_hist_lstnew(char *line)
{
	t_hist	*elem;

	if (!(elem = (t_hist *)sh_malloc(sizeof(t_hist))))
		return (NULL);
	if (!(elem->line = ft_strdup(line)))
	{
		free(elem);
		return (NULL);
	}
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		sh_hist_lstadd(t_hist **alst, t_hist *elem)
{
	t_hist	*tmp;

	tmp = *alst;
	if (!tmp)
	{
		*alst = elem;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	elem->next = NULL;
	elem->prev = tmp;
}

void		sh_hist_lstdel(t_hist **alst)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp = *alst;
	while (tmp)
	{
		ft_strdel(&tmp->line);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int			sh_hist_printall(char **args)
{
	t_hist		*p_hist;
	int			i;

	p_hist = g_hist;
	if (p_hist && !args[1])
	{
		i = 1;
		while (p_hist != NULL)
		{
			ft_putnbr(i);
			ft_putstr(". ");
			ft_putendl(p_hist->line);
			p_hist = p_hist->next;
			++i;
		}
	}
	return (0);
}
