/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:16 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 13:29:36 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goend(t_stream *stream)
{
	if (stream->command)
		while (stream->command[stream->pos])
			ft_mvright(stream);
}

/*
** JORDAN YOU HAVE TO WRITE IN ENGLISH BETWEEN FUNCTION !!
*/

void	ft_gohome(t_stream *stream)
{
	while (stream->pos)
		ft_mvleft(stream);
}

void	ft_ctrlup(t_stream *stream)
{
	size_t		col;

	if (stream->search)
		ft_searchengine(stream);
	col = stream->col;
	while (col--)
		ft_left(stream);
}

void	ft_ctrldown(t_stream *stream)
{
	size_t		col;

	if (stream->search)
		ft_searchengine(stream);
	col = stream->col;
	while (col--)
		ft_right(stream);
}
