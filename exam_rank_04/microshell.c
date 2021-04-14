/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:23:36 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/11 15:48:02 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_shell
{
	char **argv;
	int	sem;
	int pipe;
	int fd[2];
	int stdin;
	int stdout;
}				t_shell;

int	g_res;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}

void init_struct(t_shell *shell)
{
	shell->argv = NULL;
	shell->pipe = 0;
	shell->sem = 0;
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	shell->stdin = dup(0);
	shell->stdout = dup(1);
	shell->stderr = dup(2);
}

void	data_clear(t_shell *shell)
{
	if (shell->argv)
		free(shell->argv);
	shell->argv = NULL;
	shell->pipe = 0;
	shell->sem = 0;
}

void error(t_shell *shell)
{
	data_clear(shell);
	if (shell->fd[0] >= 3)
		close(shell->fd[0]);
	if (shell->fd[1] >= 3)
		close(shell->fd[1]);
	ft_putendl_fd("error: fatal", 2);
	exit(1);
}

int		parse(t_shell *shell, char **argv, int i)
{
	int j;
	int start;

	j = 0;
	start = i;
	while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
		i++;
	if (!(shell->argv = (char **)malloc(sizeof(char *) * i + 1 - start)))
		error(shell);
	while (start != i)
		shell->argv[j++] = argv[start++];
	shell->argv[j] = NULL;
	return (i);
}

void	cmd_cd(t_shell *shell, char **argv)
{
	if ((argv[2] && argv[3]) || !argv[2])
	{
		ft_putendl_fd("error: cd: bad arguments", 2);
		g_res = 1;
	}
	else
	{
		if (chdir(argv[2]) == -1)
		{
			ft_putstr_fd("error: cd: cannot change directory ", 2);
			ft_putendl_fd(argv[2], 2);
			g_res = 1;
		}
	}
}

void	execve_cmd(t_shell *shell, char **env)
{
	pid_t pid;
	int status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (shell->fd[0] >= 3)
			close(shell->fd[0]);
		if (shell->pipe == 1)
			dup2(shell->fd[1], 1);
		if (shell->fd[1] >= 3)
			close(shell->fd[1]);
		if ((status = execve(shell->argv[0], shell->argv, env)) == -1)
		{
			ft_putstr_fd("error: cannot execute ", 2);
			ft_putendl_fd(shell->argv[0], 2);
			data_clear(shell);
			if (shell->fd[0] >= 3)
				close(shell->fd[0]);
			if (shell->fd[1] >= 3)
				close(shell->fd[1]);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		data_clear(shell);
		if (shell->fd[0] >= 3)
			close(shell->fd[0]);
		if (shell->fd[1] >= 3)
			close(shell->fd[1]);
		error(shell);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		g_res = WEXITSTATUS(status);
		if (shell->fd[1] >= 3)
			close(shell->fd[1]);
		if (shell->pipe == 1)
			dup2(shell->fd[0], 0);
		if (shell->fd[0] >= 3)
			close(shell->fd[0]);
		if (shell->pipe == 0)
		{
			dup2(shell->stdin, 0);
			dup2(shell->stdout, 1);
		}
	}
}

void 	all_proc(t_shell *shell, char **argv, char **env)
{
	int i;
	int status;

	i = 1;
	status = 1;
	init_struct(shell);
	while (status == 1)
	{
		i = parse(shell, argv, i);
		if (argv[i] && strcmp(argv[i], ";") == 0)
			shell->sem = 1;
		if (argv[i] && strcmp(argv[i], "|") == 0)
			shell->pipe = 1;
		if (shell->pipe == 1)
			pipe(shell->fd);
		if (shell->argv[0] && strcmp(shell->argv[0], "cd") == 0)
			cmd_cd(shell, argv);
		else if (shell->argv[0])
			execve_cmd(shell, env);
		if (shell->pipe == 0 && shell->sem == 0)
			status = 0;
		data_clear(shell);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_shell shell;

	g_res = 0;
	if (argc >= 2)
		all_proc(&shell, argv, env);
	close(shell.stdin);
	close(shell.stdout);
	return (g_res);
}
