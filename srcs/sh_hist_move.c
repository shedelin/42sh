/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetit <apetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 16:16:44 by apetit            #+#    #+#             */
/*   Updated: 2014/06/24 18:21:08 by apetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "sh.h"

static int	sh_hist_getlength(void)
{
	t_hist		*p_hist;
	int			i;

	i = 0;
	p_hist = g_hist;
	if (p_hist != NULL)
	{
		++i;
		while (p_hist && p_hist->next != NULL)
		{
			p_hist = p_hist->next;
			i++;
		}
	}
	return (i);
}

void		sh_hist_print(t_cursor *cursor, int pos)
{
	t_hist		*p_hist;
	int			i;

	p_hist = g_hist;
	if (p_hist)
	{
		i = 1;
		while (p_hist && p_hist->next != NULL && i++ < pos)
			p_hist = p_hist->next;
		if (p_hist && p_hist->line)
		{
			i = 0;
			while ((p_hist->line)[i])
				sh_insert_char(cursor, (p_hist->line)[i++]);
		}
	}
}

void		sh_hist_move(t_cursor *cursor, int order)
{
	static int	current = -1;

	if (order == 3)
		current = -1;
	if (current == -1)
	{
		if (sh_hist_getlength() > 0)
			current = sh_hist_getlength() + 1;
		else
			current = 0;
	}
	if (cursor != NULL)
	{
		while (cursor->current != cursor->start)
			sh_backspace(cursor);
	}
	if (order == 0 && current < sh_hist_getlength())
		++current;
	else if (order == 1 && current > 1)
		--current;
	if (order != 3)
		sh_hist_print(cursor, current);
}

void		sh_hist_update(void)
{
	t_cursor	*cursor;

	cursor = NULL;
	sh_hist_move(cursor, 3);
}
