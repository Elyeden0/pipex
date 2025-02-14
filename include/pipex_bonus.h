/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:38:29 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/14 16:57:59 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# define CMD_NOT_FOUND 1
# define NO_FILE 2
# define NO_PERM 3
# define CMD_FAIL 4
# define INV_ARGS 5
# define NO_MEMORY 6
# define DUP_ERR 7
# define PIPE_ERR 8
# define FORK_ERR 9
# define NO_PATH 10

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		here_doc;
}			t_pipex;

// Structure to hold parameters for fork_and_execute
typedef struct s_fork_exec_params
{
	t_pipex	*pipex;
	char	**argv;
	char	**envp;
	int		*pipes;
	int		i;
	int		argc;
}			t_fork_exec_params;

/* Error handling */
void	pipex_perror(char *param, int err);
void	cmd_not_found(char *cmd);

/* Command execution */
char	*get_cmd(char **paths, char *cmd);
void	execute_cmd(char **argv, char **envp, t_pipex *pipex);
void	handle_here_doc(t_pipex *pipex, char **argv, int argc);

/* Path handling */
char	*find_path(char **envp);

/* Process handling */
void	child_process(char **argv, char **envp, t_pipex *pipex);
void	parent_process(char **argv, char **envp, t_pipex *pipex);
void	fork_processes(t_pipex *pipex, char **argv, char **envp, int argc);

/* Process mess */
void	create_pipe(int *pipe_fd);
void	close_pipe(int fd);
void	wait_for_child(pid_t pid);
void	dup_fds(int fd1, int fd2);
void	close_all_pipes(int *pipes, int count);
void	create_pipes_recursive(int *pipes, int argc, int index);
void	wait_for_children_recursive(t_pipex *pipex, int argc, int index);

/* Cleanup */
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);

#endif
