/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2024/12/08 00:00:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_file(char **av)
{
	int		count;
	char	**file;

	count = count_lines(av[1]);
	file = malloc(sizeof(char *) * (count + 1));
	if (!file)
		return (NULL);
	get_file(av[1], file);
	return (file);
}
