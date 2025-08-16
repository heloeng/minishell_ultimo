/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06.2-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:53:14 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:22:11 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Frees a linked list of redirection structures.
 *   - Frees the filename string for each redirection
 *   - Frees each redirection node
 */
void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

/*
 * Allocates and initializes a new command structure.
 *   - Sets argv and redirects to NULL
 *   - Returns a pointer to the new command, or NULL on failure
 */
static t_command	*new_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Frees a linked list of command structures.
 *   - Frees argv array and its contents
 *   - Frees redirection list (if present)
 *   - Frees each command node
 */
void	free_cmds(t_command *cmd_head)
{
	t_command	*tmp;
	int			i;

	while (cmd_head)
	{
		tmp = cmd_head;
		cmd_head = cmd_head->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		if (tmp->redirects)
			free_redirects(tmp->redirects);
		free(tmp);
	}
}

/*
 * Adds a new command to the end of the command list.
 *   - If the list is empty, sets the new command as the head
 *   - Otherwise, traverses to the end and appends the new command
 */
static void	add_cmd_back(t_command **cmd_head, t_command *new)
{
	t_command	*tmp;

	if (!*cmd_head)
	{
		*cmd_head = new;
		return ;
	}
	tmp = *cmd_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
 * Initializes a new command and appends it to the command list.
 *   - On allocation failure, frees the entire command list
 * Returns:
 *   - Pointer to the newly created command
 *   - NULL on allocation failure
 */
t_command	*init_command(t_command **cmd_head)
{
	t_command	*new;

	new = new_cmd();
	if (!new)
	{
		free_cmds(*cmd_head);
		return (NULL);
	}
	add_cmd_back(cmd_head, new);
	return (new);
}
