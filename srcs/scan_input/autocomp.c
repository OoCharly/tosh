/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2016/10/17 16:46:05 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   static void	get_autocomp(t_stream *stream)
   {
   }

   static char	*ft_last_separators(const char *str, char c)
   {
   int i;
   char *ret;

   i = 0;
   if (!str || !*str)
   return (NULL);
   while (str[i])
   i++;
   if (str[--i] == c)
   return (NULL);
   if ((ret = ft_strrchr(str, c)))
   return (ret + 1);
   return (NULL);
   }
   */

char	*get_begin(t_stream *stream, int *len)
{
	int i;

	i = stream->pos - 1;
	ft_putnbr(i);
	while (i >= 0 && (stream->command)[i] != ' ')
	{
		if (i > 0)
			i -= 1;
		*len += 1;
	}
	return (&(stream->command[i]));
}

void	ft_autocomp(t_stream *stream)
{
	int		buf_pos;
	int		len;
	char	*begin;

	len = 0;
	buf_pos = stream->pos;
	if (stream->command)
	{
		while (stream->command[stream->pos] != ' ' && stream->command[stream->pos])
			ft_mvright(stream);
		begin = get_begin(stream, &len);
		if (!len)
			ft_underline_mess("standard", stream);
		else
		{
			ft_underline_mess(begin, stream);
		}
	}
}

