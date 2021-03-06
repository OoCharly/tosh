/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:27:28 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 10:20:59 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_gomatch(t_stream *stream, unsigned int go)
{
	void			(*mv)(t_stream*);

	if (stream->pos > go)
		mv = ft_mvleft;
	else
		mv = ft_mvright;
	while (stream->pos != go)
		mv(stream);
}

int				ft_putcharint(int i)
{
	char			c;
	t_stream		*stream;

	stream = ft_save_stream(NULL);
	c = i;
	ft_putchar_fd(c, SFD);
	return (c);
}

void			ft_tputs(t_stream *stream)
{
	if (stream->config->term_state)
		tputs(tgetstr(stream->tput, NULL), stream->fd, &ft_putcharint);
	else if (stream->tput[0] == 'u')
		ft_putstr_fd(TUP, SFD);
	else if (stream->tput[0] == 'l')
		ft_putstr_fd(TLE, SFD);
	else if (stream->tput[0] == 'n')
		ft_putstr_fd(TND, SFD);
	else if (stream->tput[0] == 'c')
		ft_putstr_fd(TCD, SFD);
	else if (stream->tput[0] == 'd' && stream->tput[1] == 'o')
		ft_putstr_fd(TDO, SFD);
	else
		ft_putstr_fd(TDL, SFD);
}

/*
**If cursor isn't one EOF or on the last column, moves the cursors left one
**column. Otherwise moves cursor one the last column and moves vertically up one
**line.
*/

void			ft_mvleft(t_stream *stream)
{
	unsigned int	i;

	i = 0;
	if (stream->pos)
	{
	if (stream->command[stream->pos - 1] != '\n'
	&& (stream->cur_col = (stream->config->prompt_len + stream->pos) % stream->col))
	//if (stream->command[stream->pos - 1] != '\n' && (stream->cur_col = ft_get_cur_col(stream->command, stream->pos, stream)))
			ft_repeat_termcaps(1, "le", stream);
		else
		{
			stream->tput = "nd";
			while (++i <= stream->col)
				ft_tputs(stream);
			ft_repeat_termcaps(1, "up", stream);
		}
		stream->pos--;
		if (i)
			ft_checknewline(stream);
	}
}

void			ft_mvright(t_stream *stream)
{
	unsigned int	i;

	if (stream->command)
	{
		if (((stream->config->prompt_len + stream->pos) % stream->col)
			!= stream->col - 1 && stream->command[stream->pos] != '\n')
			ft_repeat_termcaps(1, "nd", stream);
		else
		{
			i = 0;
			stream->tput = "le";
			while (++i <= stream->col - 1)
				ft_tputs(stream);
			stream->tput = "do";
			ft_tputs(stream);
		}
		stream->pos++;
	}
}
