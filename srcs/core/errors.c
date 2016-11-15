/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:54 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 08:59:58 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_shname_or_file(char *name)
{
	static char	*errn = SHNAME;

	if (name)
		errn = name;
	return (errn);
}

size_t		ft_script_line(int mode)
{
	static size_t	script_line = 0;

	if (mode < 0)
		script_line = 0;
	else if (mode)
		script_line += mode;
	return (script_line);
}

static void	ft_last_exit_fail(void)
{
	t_stream	*stream;

	stream = ft_save_stream(NULL);
	if (stream && stream->config)
		stream->config->last_exit = 3;
}

int			ft_error(char *name, char *other, char *mess, int mode)
{
	if (mode & FCR_ERROR)
		ft_putchar_fd('\n', 2);
	if (name)
	{
		if (strcmp(name, SHNAME))
			ft_putstr_fd(name, 2);
		else
			ft_putstr_fd(ft_shname_or_file(NULL), 2);
		ft_putstr_fd(": ", 2);
	}
	if (ft_script_line(0) && !strcmp(SHNAME, name))
		FT_PUTSTRFD("ligne ", ft_st_itoa((int)ft_script_line(0)), ": ", 2);
	if (other)
	{
		ft_putstr_fd(other, 2);
		ft_putstr_fd(": ", 2);
	}
	if (mess)
		ft_putstr_fd(mess, 2);
	if (mode & CR_ERROR)
		ft_putchar_fd('\n', 2);
	if (mode & SERROR)
		ft_status(1);
	ft_last_exit_fail();
	return (true);
}

int			ft_initerror(t_config *config)
{
	ft_error(SHNAME, NULL, "init error", CR_ERROR);
	ft_free_config(config);
	return (1);
}
