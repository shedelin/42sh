/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetit <apetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/09 22:02:11 by shedelin          #+#    #+#             */
/*   Updated: 2014/06/25 14:48:38 by apetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <libft.h>
#include "sh.h"

void	sh_execkey(char	*key, t_cursor *cursor)
{
	if (K1 == 0 && K2 == 0 && K3 == 0 && ft_isprint(K0))
		sh_insert_char(cursor, K0);
	else if (K0 == 27 && K1 == 91 && K2 == 65 && K3 == 0)
		sh_hist_move(cursor, 1);
	else if (K0 == 27 && K1 == 91 && K2 == 66 && K3 == 0)
		sh_hist_move(cursor, 0);
	else if (K0 == 27 && K1 == 91 && K2 == 72 && K3 == 0)
		sh_move_home(cursor);
	else if (K0 == 27 && K1 == 91 && K2 == 70 && K3 == 0)
		sh_move_end(cursor);
	else if (K0 == -61 && K1 == -91 && K2 == 0 && K3 == 0)
		sh_move_left(cursor);
	else if (K0 == -30 && K1 == -120 && K2 == -126 && K3 == 0)
		sh_move_right(cursor);
	else if (K0 == 27 && K1 == 91 && (K2 <= 68 || K2 >= 67) && K3 == 0)
		sh_movecursor(cursor, key);
	else if (K0 == 127 && K1 == 0 && K2 == 0 && K3 == 0)
		sh_backspace(cursor);
	else if (K0 == 27 && K1 == 91 && K2 == 51 && K3 == 126)
		sh_delete(cursor);
	else if (K0 == 4 && K1 == 0 && K2 == 0 && K3 == 0)
		sh_eof();
}

void	sh_backspace(t_cursor *cursor)
{
	t_char	*todel;

	if (!cursor->current->prev)
		return ;
	tputs(tgetstr("dm", NULL), 1, &sh_putchar);
	tputs(tgetstr("le", NULL), 1, &sh_putchar);
	tputs(tgetstr("cd", NULL), 1, &sh_putchar);
	tputs(tgetstr("dc", NULL), 1, &sh_putchar);
	tputs(tgetstr("ed", NULL), 1, &sh_putchar);
	todel = cursor->current->prev;
	cursor->current->prev = todel->prev;
	if (todel->prev)
		todel->prev->next = cursor->current;
	else
		cursor->start = cursor->current;
	free(todel);
	sh_printlst(cursor);
}

void	sh_delete(t_cursor *cursor)
{
	t_char	*todel;

	if (cursor->current == cursor->end)
		return ;
	tputs(tgetstr("dm", NULL), 1, &sh_putchar);
	tputs(tgetstr("dc", NULL), 1, &sh_putchar);
	tputs(tgetstr("cd", NULL), 1, &sh_putchar);
	tputs(tgetstr("ed", NULL), 1, &sh_putchar);
	todel = cursor->current;
	todel->next->prev = todel->prev;
	if (todel != cursor->start)
		todel->prev->next = todel->next;
	else
		cursor->start = todel->next;
	if (todel != cursor->start)
		cursor->current = todel->next;
	cursor->pos_col -= 1;
	free(todel);
	sh_printlst(cursor);
}

void	sh_eof(void)
{
	static char key[4];

	key[0] = 4;
	key[1] = 0;
	key[2] = 0;
	key[3] = 0;
	if (g_fork)
		ioctl(0, TIOCSTI, key);
	else
		sh_exitshell(0);
}
