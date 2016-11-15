/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:42 by tboos             #+#    #+#             */
/*   Updated: 2016/10/14 18:13:36 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/autocomp.h"
/*
** Fixe le nouveau COMP_CURRENT pour flèche gauche.
*/
void		ft_comp_get_left(t_stream *stream)
{
	if (COMP_CURRENT >= COMP_IN_COL)
		COMP_CURRENT -= COMP_IN_COL;
}
/*
** Fixe le nouveau COMP_CURRENT pour flèche droite.
*/
void		ft_comp_get_right(t_stream *stream)
{
	size_t	min;

	min = (COMP_SIZE_LIST % COMP_IN_COL == 0) ? COMP_SIZE_LIST - COMP_IN_COL :
		COMP_SIZE_LIST - (COMP_SIZE_LIST % COMP_IN_COL);
	if ((COMP_CURRENT < COMP_SIZE_LIST && COMP_CURRENT >= min) || (COMP_CURRENT
		+ COMP_IN_COL >= COMP_SIZE_LIST))
		;
	else
		COMP_CURRENT += COMP_IN_COL;
}
/*
** Fixe le nouveau COMP_CURRENT pour flèche du haut.
*/
void		ft_comp_get_up(t_stream *stream)
{
	if (COMP_CURRENT == 0)
		COMP_CURRENT = COMP_SIZE_LIST - 1;
	else
		COMP_CURRENT -= 1;
}
/*
** Fixe le nouveau COMP_CURRENT pour flèche du bas.
*/
void		ft_comp_get_down(t_stream *stream)
{
	if (COMP_CURRENT == COMP_SIZE_LIST - 1)
		COMP_CURRENT = 0;
	else
		COMP_CURRENT += 1;
}
/*
** Sélectionne ou désélectionne l'élément numéroté.
*/
void		ft_comp_select_current(size_t current, t_stream *stream, char mode)
{
	t_list	*list;
	size_t	i;

	list = COMP_BEGIN_LIST;
	i = -1;
	while (++i < current && list)
		list = list->next;
	if (mode == 'S')
	{
		bzero(COMP_BUF, 256);
		ft_strcpy(COMP_BUF, &(((char *)list->data)[ft_strlen(COMP_BEGIN)]));
		list->data_size |= 1; // met le dernier bit à 1.
	}
	else
		list->data_size  ^= 1; // si le dernier bit est à 1, le met à 0.
}
