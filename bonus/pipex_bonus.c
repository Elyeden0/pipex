/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:11:24 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/13 15:15:21 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../libft/get_next_line.h"  // Include the header for get_next_line

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

static void	check_arguments(int argc, char **argv, char **envp)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
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

static void	handle_files(t_pipex *pipex, char **argv, int argc)
{
	pipex->here_doc = 0;
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
	{
		pipex_perror(argv[1], NO_FILE);
		exit(1);
	}
}

static void	initialize_pipex(t_pipex *pipex, char **argv, char **envp, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		handle_here_doc(pipex, argv, argc);
	}
	else
	{
		handle_files(pipex, argv, argc);
	}
	init_pipex_again(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	check_arguments(argc, argv, envp);
	initialize_pipex(&pipex, argv, envp, argc);
	fork_processes(&pipex, argv, envp, argc);
	free_parent(&pipex);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}
