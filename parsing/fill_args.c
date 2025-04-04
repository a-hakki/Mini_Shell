/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/05 09:23:22 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

void	throw_error(int error)
{
	if (g_vars.exit != 0)
		return ;
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
		printfd(2, "Command not found : %s\n", g_vars.cmd_not_found);
	g_vars.exit = 127;
}

int	ft_nodejoin(void)
{
	char *(new_content), *(tmp_content);
	t_list *(to_delete), *(tmp) = g_vars.args;
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	while (tmp && tmp->next)
	{
		tmp_content = (char *)tmp->content;
		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
			if (!new_content)
				return (FALSE);
			free(tmp->content);
			tmp->content = new_content;
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(to_delete, free);
		}
		else
			tmp = tmp->next;
	}
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	return (TRUE);
}

void	print_array(char **arr)
{
	int (i) = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("words %d : #%s#\n", i, arr[i]);
		i++;
	}
}

void	split_cmds_args(void)
{
	g_vars.tmp = g_vars.args;
	while (g_vars.tmp)
	{
		g_vars.tmp->arr = _ft_split(g_vars.tmp->content, ' ');
		if (!g_vars.tmp->arr)
			return ;
		int (i) = 0;
		// print_array(g_vars.tmp->arr);
		while (g_vars.tmp->arr[i])
		{
			g_vars.tmp->arr[i] = removequotes(g_vars.tmp->arr[i]);
			i++;
		}
		// print_array(g_vars.tmp->arr);
		g_vars.tmp = g_vars.tmp->next;
	}
}

int	fill_args(void)
{
	char	*token;

	if (!g_vars.cmd || !*(g_vars.cmd) || ft_iswhitespace(g_vars.cmd))
		return (FALSE);
	token = ft_strtok(g_vars.cmd, "'\"()|&><");
	while (token)
	{
		ft_lstadd_back(&g_vars.args, ft_lstnew(token));
		g_vars.args->arr = NULL;
		if (!ft_iswhitespace(token))
			ft_lstadd_back(&g_vars._args, ft_lstnew(token));
		token = ft_strtok(NULL, "'\"()|&><");
	}
	if (!ft_check())
		return (FALSE);
	split_cmds_args();
	return (TRUE);
}

//we shoud implement the fct that parses the peripheric of the paranthesis
// () )(  &(&)  ()|  ()a : nooooo
// >> << ()
//  (ls )(cat -e M)
