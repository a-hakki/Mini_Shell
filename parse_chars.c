/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/21 18:43:43 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_vars;

void	throw_error(int error)
{
	if (error == SYNTAX)
		printf("Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == CHARS)
		printf("Invalid Character => ; or #\n");
}

int	ft_check(void)
{
	int		str_i;

	g_vars.tmp = g_vars.args;
	if ((g_vars.check.dquot % 2) || (g_vars.check.squot % 2) \
		|| (g_vars.check.par % 2))
		g_vars.check.special = 2;
	else
	{
		while (g_vars.tmp)
		{
			str_i = 0;
			while (((char *)g_vars.tmp->content)[str_i])
			{
				if (ft_strchr(";#", ((char *)g_vars.tmp->content)[str_i++]))
					g_vars.check.special = 1;
			}
			g_vars.tmp = g_vars.tmp->next;
		}
	}
	if (g_vars.check.special == 2 || g_vars.check.fpar == ')' \
		|| g_vars.check.lpar == '(')
		return (throw_error(SYNTAX), FALSE);
	if (g_vars.check.special == 1)
		return (throw_error(CHARS), FALSE);
	return (TRUE);
}

int	ft_isvalid(char c)
{
	if (c == '"')
		g_vars.check.dquot++;
	if (c == '\'')
		g_vars.check.squot++;
	if (c == '(')
	{
		g_vars.check.par++;
		g_vars.check.lpar = '(';
		if (g_vars.check.fpar == 0)
			g_vars.check.fpar = '(';
	}
	if (c == ')')
	{
		g_vars.check.par--;
		g_vars.check.lpar = ')';
		if (g_vars.check.fpar == 0)
			g_vars.check.fpar = ')';
	}
	return (TRUE);
}

void	add_node(char const *s, size_t n)
{
	ft_lstadd_back(&g_vars.args, ft_lstnew(ft_strndup(s, n)));
}

int	betweenquotes(char	*str, char c)
{
	int	i;
	int start;
	int end;

	ft_init("iiiiiiii", &g_vars.check.dquot, &g_vars.check.squot, \
		&g_vars.check.par, &g_vars.check.special, &g_vars.check.fpar, \
			&g_vars.check.lpar, &i, &start);
	if (!str)
		return 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		start = i + 1;
	end = ft_strlen(str);
	while (start && end > start && str[end] != c)
		end--;
	if (start != end)
	{
		while (str[start] && start < end)
			ft_isvalid(str[start++]);
		if ((g_vars.check.dquot % 2) || (g_vars.check.squot % 2) \
			|| (g_vars.check.par % 2))
			g_vars.check.special = 2;
	}
	return (g_vars.check.special);
}

int	fill_args(char *str)
{
	int		str_i;
	int		k;

	str_i = 0;
	while (str[str_i])
	{
		if (str[str_i] && (ft_isalnum(str[str_i]) || \
			!ft_strchr("\"\'()|&", str[str_i])))
		{
			k = str_i;
			while (str[str_i] && (ft_isalnum(str[str_i]) \
				|| !ft_strchr("\"\'()|&", str[str_i])))
				str_i++;
			if (str_i > k)
				add_node(str + k, str_i - k);
		}
		else if (str[str_i])
		{
			ft_isvalid(str[str_i]);
			add_node(&str[str_i], 1);
			str_i++;
		}
	}
	if (ft_check())
	{
		g_vars.tmp = g_vars.args;
		int i = betweenquotes(str, '\'');
		int j = betweenquotes(str, '\"');
		if (i == 2 || j == 2 || g_vars.check.fpar == ')' \
			|| g_vars.check.lpar == '(')
			return (throw_error(SYNTAX), 0);
	}
	return (ft_lstiter(g_vars.tmp, printf), 0);
}
