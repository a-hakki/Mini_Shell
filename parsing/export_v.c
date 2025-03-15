/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:04:41 by ahakki            #+#    #+#             */
/*   Updated: 2025/03/15 20:17:59 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_v(char *s)
{
	char	*value;

	if (!s)
		return (NULL);
	value = getenv(s);
	return (value);
}
char *expand(char *str, char *var, int i)
{
    int len = ft_strlen(str) + ft_strlen(var);
    char *new = (char *)malloc(sizeof(char) * (len + 1));
    int j = 0;
    int k = 0;

    while (j < i)
    {
        new[j] = str[j];
        j++;
    }
    i += 2;
    while (var[k])
    {
        new[j] = var[k];
        j++;
        k++;
    }
    while (str[i])
    {
        new[j] = str[i];
        j++;
        i++;
    }
    new[j] = '\0';
    return (free(str), free(var), new);
}


int main(int ac, char **av)
{
    char *str = ft_strdup(av[1]);
    char *var = export_v(ft_strdup(av[2]));
	int i = ft_strchr_index(str, '$');
	printf("%s\n", expand(str, var, i));
}
