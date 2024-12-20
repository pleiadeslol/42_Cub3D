/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:14 by root              #+#    #+#             */
/*   Updated: 2024/12/18 18:36:21 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (check_args(ac, av))
		return (1);
	mlx = init_struct(ac, av);
	if (!mlx)
		return (err("Error\n"), 1);
	init_game(mlx);
}
