/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 15:48:05 by shedelin          #+#    #+#             */
/*   Updated: 2014/06/26 15:48:10 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <glob.h>
#include <libft.h>
#include "sh.h"

static int			errfunc(const char *epath, int errno)
{
	ft_putstr("Display of ");
	ft_putstr(epath);
	ft_putstr(" failed. Error code : ");
	ft_putnbr(errno);
	ft_putchar('\n');
	return (0);
}

static char			*sh_globline(char *line)
{
	glob_t			globline;
	char			*newl;
	int				csource;
	char			**p;
	char			*tmp;

	newl = NULL;
	csource = glob(line, GLOB_ERR | GLOB_MARK, errfunc, &globline);
	if (!csource)
	{
		p = globline.gl_pathv;
		while (*p)
		{
			tmp = ft_strjoin(newl, *p);
			p++;
			free(newl);
			newl = ft_strjoin(tmp, " ");
			free(tmp);
		}
		globfree(&globline);
		free(line);
		return (newl);
	}
	return (line);
}

static char			*sh_multijoin(char *begin, char *glob, char *end)
{
	char	*tmp;

	glob = sh_globline(glob);
	tmp = ft_strjoin(begin, glob);
	ft_bzero(begin, ft_strlen(begin));
	free(begin);
	begin = ft_strjoin(tmp, end);
	ft_bzero(tmp, ft_strlen(tmp));
	free(tmp);
	ft_bzero(glob, ft_strlen(glob));
	free(glob);
	ft_bzero(end, ft_strlen(end));
	free(end);
	return (begin);
}

static char			*sh_check_end(char *line, int i)
{
	if (line[i + 1] != '\0')
		return (ft_strdup(line + (i + 1)));
	else
		return (NULL);
}

char				*sh_test_glob(char *line)
{
	int		count[2];
	char	*begin;
	char	*glob;
	char	*end;

	count[0] = 0;
	count[1] = 0;
	while (line[count[0]] && line[count[0]] != '*')
		count[0]++;
	if (!line[count[0]])
		return (line);
	while (count[0] >= 0 && line[count[0]] != ' ')
		count[0]--;
	if (count[0] > 0)
		begin = ft_strndup(line, count[0]);
	else
		begin = NULL;
	count[1] = ++count[0];
	while (line[count[0]] && line[count[0]] != ' ')
		count[0]++;
	glob = ft_strndup(line + count[1], count[0] - count[1] - 1);
	end = sh_check_end(line, count[0]);
	free(line);
	return (sh_multijoin(begin, glob, end));
}
