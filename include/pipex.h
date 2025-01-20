/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:25:50 by abonnard          #+#    #+#             */
/*   Updated: 2025/01/17 16:34:23 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}	t_pipex;

/* Error handling */
void	error_msg(char *error);
void	cmd_not_found(char *cmd);

/* Command execution */
char	*get_cmd(char **paths, char *cmd);
void	execute_cmd(char **argv, char **envp, t_pipex *pipex);

/* Path handling */
char	*find_path(char **envp);

/* Process handling */
void	child_process(char **argv, char **envp, t_pipex *pipex);
void	parent_process(char **argv, char **envp, t_pipex *pipex);

/* Cleanup */
void	close_pipes(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);

#endif
