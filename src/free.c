/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicn <danicn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:22:49 by dcruz-na          #+#    #+#             */
/*   Updated: 2022/09/03 16:31:58 by danicn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(char **path, char **arr)
{
	char	**a;
	char	**b;

	a = path;
	b = arr;
	while (*path != NULL)
	{
		free(*path);
		path++;
	}
	free(a);
	while (*arr != NULL)
	{
		free(*arr);
		arr++;
	}
	free(b);
}

void	close_parent(int *pipex, int *fd1, int *fd2)
{
	if (pipex != NULL)
		close(pipex[0]);
	if (fd1 != NULL)
		close(*fd1);
	if (fd2 != NULL)
		close(*fd2);
}

void	close_child(int *pipex, int *fd1, int *fd2)
{
	if (pipex != NULL)
		close(pipex[1]);
	if (fd1 != NULL)
		close(*fd1);
	if (fd2 != NULL)
		close(*fd2);
}

void	exit_program(int *pipex, int *fds, char **arr, char **path)
{
	close(pipex[0]);
	close(pipex[1]);
	close(fds[0]);
	close(fds[1]);
	if (arr != NULL || path != NULL)
		free_path(path, arr);
	exit(EXIT_FAILURE);
}