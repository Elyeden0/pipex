/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:29:45 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/12 12:30:16 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	cmd_not_found(char *cmd)
{
    pipex_perror(cmd, CMD_NOT_FOUND);
    exit(127);
}

void	pipex_perror(char *param, int err)
{
    ft_putstr_fd("pipex: ", 2);
    if (err == CMD_NOT_FOUND)
        ft_putstr_fd("command not found: ", 2);
    if (err == NO_FILE)
        ft_putstr_fd("no such file or directory: ", 2);
    if (err == NO_PERM)
        ft_putstr_fd("permission denied: ", 2);
    if (err == CMD_FAIL)
        ft_putstr_fd("command failed: ", 2);
    if (err == INV_ARGS)
        ft_putstr_fd("invalid number of arguments", 2);
    if (err == NO_MEMORY)
        ft_putstr_fd("no memory left on device", 2);
    if (err == DUP_ERR)
        ft_putstr_fd("could not dup fd", 2);
    if (err == PIPE_ERR)
        ft_putstr_fd("could not create pipe", 2);
    if (err == FORK_ERR)
        ft_putstr_fd("could not fork process", 2);
    if (err == NO_PATH)
        ft_putstr_fd("PATH variable is not set", 2);
    if (param && (err == CMD_NOT_FOUND || err == NO_FILE \
            || err == NO_PERM || err == CMD_FAIL))
        ft_putstr_fd(param, 2);
    ft_putstr_fd("\n", 2);
}

char	*find_path(char **envp)
{
    int		i;
    char	*path;

    i = 0;
    while (envp && envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
        {
            path = envp[i] + 5;
            if (*path)
                return (path);
        }
        i++;
    }
    return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
    char	*tmp;
    char	*command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        if (!tmp)
            return (NULL);
        command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!command)
            return (NULL);
        if (access(command, F_OK | X_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

