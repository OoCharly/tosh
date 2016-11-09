/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2016/11/08 14:31:51 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_execve(char **argv, char **env, t_config *config)
{
	char	*path;
	char	*bin;

	path = argv[0];
	bin = ft_return_binpath(config, path);
	if (ft_access_exec(bin ? bin : path, argv, config))
	{
		if (-1 == execve(bin ? bin : path, argv, env))
			ft_error(SHNAME, "exec", "execve error", CR_ERROR);
	}
}

void		ft_launch_process(char **argv, t_config *config)
{
	if (ft_builtin(argv, config))
		return ;
	else
		ft_execve(argv, config->env, config);
}

void		ft_kill_father(t_config *config)
{
	ft_free_config(config);
	if (-1 == kill(getppid(), SIGKILL))
		ft_error(SHNAME, "SORRY", JEDI_ERR, CR_ERROR);
	exit(0);
}
