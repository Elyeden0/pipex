/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:29:28 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/14 16:57:51 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	handle_child_process(t_pipex *pipex, int *pipes, int i, int argc)
{
	if (i == 0)
		dup_fds(pipex->infile, STDIN_FILENO);
	else
		dup_fds(pipes[(i - 1) * 2], STDIN_FILENO);
	if (i == argc - 4)
		dup_fds(pipex->outfile, STDOUT_FILENO);
	else
		dup_fds(pipes[i * 2 + 1], STDOUT_FILENO);
	close_all_pipes(pipes, 2 * (argc - 4));
}

static void	fork_and_execute(t_fork_exec_params *params)
{
	pid_t	pid;

	if (params->i == 0)
	{
		pid = fork();
		params->pipex->pid1 = pid;
	}
	else
	{
		pid = fork();
		params->pipex->pid2 = pid;
	}
	if (pid < 0)
	{
		pipex_perror(NULL, FORK_ERR);
		exit(1);
	}
	if (pid == 0)
	{
		handle_child_process(params->pipex, params->pipes,
			params->i, params->argc);
		execute_cmd(params->argv + 2 + params->i + params->pipex->here_doc,
			params->envp, params->pipex);
	}
}

static void	fork_and_execute_recursive(t_fork_exec_params *params)
{
	if (params->i >= params->argc - 3)
		return ;
	fork_and_execute(params);
	params->i++;
	fork_and_execute_recursive(params);
}

void	fork_processes(t_pipex *pipex, char **argv, char **envp, int argc)
{
	int					*pipes;
	t_fork_exec_params	params;

	pipes = malloc(sizeof(int) * 2 * (argc - 4));
	if (!pipes)
	{
		pipex_perror(NULL, NO_MEMORY);
		exit(1);
	}
	create_pipes_recursive(pipes, argc, 0);
	params.pipex = pipex;
	params.argv = argv;
	params.envp = envp;
	params.pipes = pipes;
	params.i = 0;
	params.argc = argc;
	fork_and_execute_recursive(&params);
	close_all_pipes(pipes, 2 * (argc - 4));
	wait_for_children_recursive(pipex, argc, 0);
	free(pipes);
}
