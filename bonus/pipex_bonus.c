/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:11:24 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/12 12:25:08 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

static void	initialize_pipex(t_pipex *pipex, char **argv, char **envp, int argc)
{
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        char *line;
        int tmp_fd;

        pipex->here_doc = 1;
        tmp_fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (tmp_fd < 0)
        {
            pipex_perror(".here_doc_tmp", NO_FILE);
            exit(1);
        }
        while ((line = get_next_line(STDIN_FILENO)))
        {
            if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0 && line[ft_strlen(argv[2])] == '\n')
            {
                free(line);
                break;
            }
            write(tmp_fd, line, ft_strlen(line));
            free(line);
        }
        close(tmp_fd);
        pipex->infile = open(".here_doc_tmp", O_RDONLY);
        pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        pipex->here_doc = 0;
        pipex->infile = open(argv[1], O_RDONLY);
        pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    if (pipex->infile < 0 || pipex->outfile < 0)
    {
        pipex_perror(argv[1], NO_FILE);
        exit(1);
    }
    init_pipex_again(pipex, envp);
}

static void	fork_processes(t_pipex *pipex, char **argv, char **envp, int argc)
{
    int i;
    int pipes[2 * (argc - 4)];
    int j;

    i = 0;
    while (i < argc - 4)
    {
        if (pipe(pipes + i * 2) < 0)
        {
            pipex_perror(NULL, PIPE_ERR);
            exit(1);
        }
        i++;
    }

    i = 0;
    while (i < argc - 3)
    {
        if (i == 0)
            pipex->pid1 = fork();
        else
            pipex->pid2 = fork();

        if ((i == 0 && pipex->pid1 < 0) || (i != 0 && pipex->pid2 < 0))
        {
            pipex_perror(NULL, FORK_ERR);
            exit(1);
        }

        if ((i == 0 && pipex->pid1 == 0) || (i != 0 && pipex->pid2 == 0))
        {
            if (i == 0)
                dup2(pipex->infile, STDIN_FILENO);
            else
                dup2(pipes[(i - 1) * 2], STDIN_FILENO);

            if (i == argc - 4)
                dup2(pipex->outfile, STDOUT_FILENO);
            else
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);

            j = 0;
            while (j < 2 * (argc - 4))
            {
                close(pipes[j]);
                j++;
            }

            execute_cmd(argv + 2 + i + pipex->here_doc, envp, pipex);
        }
        i++;
    }

    j = 0;
    while (j < 2 * (argc - 4))
    {
        close(pipes[j]);
        j++;
    }

    j = 0;
    while (j < argc - 3)
    {
        waitpid(pipex->pid2, NULL, 0);
        j++;
    }
}

int	main(int argc, char **argv, char **envp)
{
    t_pipex	pipex;
    int		status;

    check_arguments(argc, argv, envp);
    initialize_pipex(&pipex, argv, envp, argc);
    fork_processes(&pipex, argv, envp, argc);
    close_pipes(&pipex);
    free_parent(&pipex);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (127);
}
