/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcruz-na <dcruz-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:22:49 by dcruz-na          #+#    #+#             */
/*   Updated: 2022/08/23 20:52:55 by dcruz-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(char **path, char **arr)
{
	while (*path)
	{
		free(*path);
		path++;
	}
	free(path);
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
}

void	close_parent(int *pipex, int *fd1, int *fd2)
{
	close(pipex[0]);
	close(*fd1);
	close(*fd2);
}

void	close_child(int *pipex, int *fd1, int *fd2)
{
	close(pipex[1]);
	close(*fd1);
	close(*fd2);
}
