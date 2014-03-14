/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 13:28:40 by mmartin           #+#    #+#             */
/*   Updated: 2014/03/03 15:41:49 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "ft_rt.h"

static t_file	*ft_new_line(char *line)
{
	t_file	*new;
	char	*tmp;

	new = (t_file *)malloc(sizeof(t_file));
	new->next = NULL;
	tmp = line;
	while (ft_isprint(*tmp) == 0)
		tmp++;
	new->line = ft_strdup(tmp);
	free(line);
	return (new);
}

void			ft_add_file(t_file **file, char *line)
{
	if (*file == NULL)
		*file = ft_new_line(line);
	else
		ft_add_file(&((*file)->next), line);
}
