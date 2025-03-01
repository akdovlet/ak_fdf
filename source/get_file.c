/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:01:13 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/01 11:28:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*get_file(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	node = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		node = ft_lstnew(ft_strdup(line));
		if (!node || !node->content)
			return (ft_lstclear(&lst, free), free(line), NULL);
		ft_lstadd_back(&lst, node);
		free(line);
	}
	return (lst);
}
