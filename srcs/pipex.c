/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:26:44 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/02 15:46:11 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_pipex_again(t_pipex *pipex, char **envp)
{
	pipex->paths = find_path(envp);
	if (!pipex->paths)
	{
		pipex_perror(NULL, NO_PATH);
		exit(127);
	}
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	if (!pipex->cmd_paths)
	{
		pipex_perror(NULL, NO_MEMORY);
		exit(1);
	}
}

static void	check_arguments(int argc, char **envp)
{
	if (argc != 5)
	{
		pipex_perror(NULL, INV_ARGS);
		exit(1);
	}
	if (!envp || !*envp)
	{
		pipex_perror(NULL, NO_PATH);
		exit(1);
	}
}

static void	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		pipex_perror(argv[1], NO_FILE);
		exit(1);
	}
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
	{
		pipex_perror(argv[4], NO_PERM);
		exit(1);
	}
	if (pipe(pipex->pipe) < 0)
	{
		pipex_perror(NULL, PIPE_ERR);
		exit(1);
	}
	init_pipex_again(pipex, envp);
}

static void	fork_processes(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
	{
		pipex_perror(NULL, FORK_ERR);
		exit(1);
	}
	if (pipex->pid1 == 0)
		child_process(argv, envp, pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
	{
		pipex_perror(NULL, FORK_ERR);
		exit(1);
	}
	if (pipex->pid2 == 0)
		parent_process(argv, envp, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	check_arguments(argc, envp);
	initialize_pipex(&pipex, argv, envp);
	fork_processes(&pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &status, 0);
	free_parent(&pipex);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}
