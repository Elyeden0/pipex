/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:26:44 by abonnard          #+#    #+#             */
/*   Updated: 2025/01/20 14:51:16 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		error_msg("Error: cannot open input file");
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->outfile < 0)
		error_msg("Error: cannot open/create output file");
	if (pipe(pipex->pipe) < 0)
		error_msg("Error: pipe failed");
	pipex->paths = find_path(envp);
	if (!pipex->paths)
		error_msg("Error: PATH not found");
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	if (!pipex->cmd_paths)
		error_msg("Error: split failed");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg("Error: invalid number of arguments");
	if (!envp || !*envp)
		error_msg("Error: empty environment");
	init_pipex(&pipex, argv, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_process(argv, envp, &pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		parent_process(argv, envp, &pipex);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
