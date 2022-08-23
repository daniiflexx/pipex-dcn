# ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

void    child_process(int *pipex, char**envp, int *fdinit, char **argv);
void    parent_process(int *pipex, char **envp, int *fdfinal, char **argv);
char	*find_path(char **envp);
char	*find_cmd_path(char **path, char *cmd);
void	close_child(int *pipex, int *fd1, int *fd2);
void	close_parent(int *pipex, int *fd1, int *fd2);
void	free_path(char **path, char **arr);
#endif