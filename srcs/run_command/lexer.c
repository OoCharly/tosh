/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:05:45 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 09:05:46 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_next_op(char *cmd, size_t i)
{
	while (cmd[i] && !ft_strchr("><|&;()#", cmd[i]))
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			i = ft_dodge_quote(cmd, i);
		else
			++i;
	}
	if (cmd[i] == '#' && i && cmd[i - 1] != ' ')
		ft_next_op(cmd, i);
	return (i);
}

static int		ft_test_emptysshell(char *cmd, size_t i)
{
	while (ft_isspace(cmd[i]))
		++i;
	if (cmd[i] == ')')
		return (ft_error(SHNAME, "parse error", "empty sshell", CR_ERROR));
	return (0);
}

static t_list	*ft_op_handle(char *cmd, size_t *i)
{
	t_list	*next;
	t_list	*op;

	if (!(next = ft_av_handle(cmd, *i)))
		return (NULL);
	else if (cmd[*i] == '(' && ft_test_emptysshell(cmd, *i + 1))
		return (NULL);
	else if (cmd[*i] == '(' && ++(*i))
		return (ft_lexer_sshell_on(cmd, i, next));
	else if (cmd[*i] == ')')
		return (next);
	else if (cmd[*i])
	{
		if (!(next->next = (t_list *)ft_memalloc(sizeof(t_list)))
				&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR))
			return (ft_freelist(&next));
		op = next->next;
		op->data_size = 1;
		if (!(op->data = (void*)ft_match_op(cmd, i)))
			return (ft_freelist(&next));
		if (!ft_strcmp(op->data, "<<"))
			op->data_size = HEREDOC;
	}
	return (next);
}

t_list			*ft_built_couple(char *cmd, size_t *i)
{
	t_list	*next;

	*i = ft_next_op(cmd, *i);
	if (*i && (cmd[*i] == '>' || cmd[*i] == '<'))
		while (*i && ft_isdigit(cmd[*i - 1]))
			(*i)--;
	if (!(next = ft_op_handle(cmd, i)))
		return (ft_freelist(&next));
	return (next);
}

t_list			*ft_lexer(char *cmd)
{
	size_t	i;
	t_list	*begin;
	t_list	*next;

	begin = NULL;
	i = 0;
	while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
		++cmd;
	while ((cmd = cmd + i)
		&& !(i = 0) && *cmd && *cmd != ')')
	{
		while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
			++cmd;
		if (!(next = ft_built_couple(cmd, &i)))
			return (ft_freelist(&begin));
		ft_list_push_back(&begin, next);
	}
	ft_lexer_sshell_off(cmd, i);
	return (begin);
}
