/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_rld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:09:46 by cdesvern          #+#    #+#             */
/*   Updated: 2016/11/25 19:27:51 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"



void	add_path_to_hash(char *path, t_config *conf)
{
	DIR			*dir;
	t_dirent	*dirent;
	t_st		*st;

	if ((dir = opendir(path)))
		while ((dirent = readdir(dir)) && !stat(path, st) &&
				S_ISREG(st->st_mode) && access(path, X_OK | R_OK))
				add_bin(dirent->d_name, path, conf);
}

int		crehash(char *path, t_config *conf)
{
	char		*dirpath;
	char		*kill;
	DIR			*dir;
	t_dirent	*dirent;

	if (!(path = ft_strchr(path, '=')) || !*(++path)
		|| !(path = ft_strdup(path)))
		return (0);
	kill = path;
	while ((dirpath = path))
	{
		path = ft_strchr(path, ':');
		*path++ = 0;
		if (access(path, R_OK | X_OK) && (dir = opendir(path)))
		{
			ft_bin_insert(dir, dirpath, conf);
			closedir(dir);
		}
	}
	free(kill);
	return (0);
}

