/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:28 by root              #+#    #+#             */
/*   Updated: 2025/01/03 20:06:54 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_identifier(char **file, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], str, ft_strlen(file[i])))
		{
			if (ft_strncmp(file[i], str, ft_strlen(str)))
				err("Error\nIdentifier and path order is invalid\n"), exit(1);
			count++;
		}
		i++;
	}
	if (count == 0)
		return (err("Error\n"), err(str), err(" identifier doesnt exist\n"), 0);
	else if (count > 1)
		return (err("Error\n"), err(str),
			err(" identifier is set more than one time\n"), 0);
	else
		return (1);
}

int	check_order(char **file)
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
	int	i;

	no = 0;
	so = 0;
	we = 0;
	ea = 0;
	f = 0;
	c = 0;
	i = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], "NO", ft_strlen(file[i])))
			no = i;
		else if (ft_strnstr(file[i], "SO", ft_strlen(file[i])))
			so = i;
		else if (ft_strnstr(file[i], "WE", ft_strlen(file[i])))
			we = i;
		else if (ft_strnstr(file[i], "EA", ft_strlen(file[i])))
			ea = i;
		else if (ft_strnstr(file[i], "F", ft_strlen(file[i])))
			f = i;
		else if (ft_strnstr(file[i], "C", ft_strlen(file[i])))
			c = i;
		i++;
	}
	if (no > so || no > we || no > ea || no > f || no > c || so > we || so > ea
		|| so > f || so > c || we > ea || we > f || we > c || ea > f || ea > c
		|| f > c)
		return (err("Error\nIdentifiers arent in right order\n"), 1);
	return (0);
}

char	*get_path(char **file, char *str)
{
	int		i;
	char	*s;
	char	**split;

	i = 0;
	while (file[i])
	{
		s = ft_strnstr(file[i], str, ft_strlen(file[i]));
		if (s)
			break ;
		i++;
	}
	if (s)
		s = ft_strtrim(s, "\n");
	split = ft_split(s, ' ');
	if (!split)
		return (NULL);
	free(s);
	s = ft_strdup(split[1]);
	free_matrix(split);
	return (s);
}

int	is_xpm_png_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if ((file[len - 4] == '.' && file[len - 3] == 'x' && file[len - 2] == 'p'
			&& file[len - 1] == 'm') || (file[len - 4] == '.' && file[len
			- 3] == 'p' && file[len - 2] == 'n' && file[len - 1] == 'g'))
		return (1);
	return (0);
}

int	check_path_file(t_path *path)
{
	int	fd;

	fd = open(path->NO, O_RDONLY);
	if (fd < 0)
		return (err("Error\nNO texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->SO, O_RDONLY);
	if (fd < 0)
		return (err("Error\nSO texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->WE, O_RDONLY);
	if (fd < 0)
		return (err("Error\nWE texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->EA, O_RDONLY);
	if (fd < 0)
		return (err("Error\nEA texture file doesnt exist\n"), 1);
	close(fd);
	if (!is_xpm_png_file(path->NO))
		return (err("Error\nNO texture file have to be a .xpm or .png file\n"),
			1);
	if (!is_xpm_png_file(path->SO))
		return (err("Error\nSO texture file have to be a .xpm or .png file\n"),
			1);
	if (!is_xpm_png_file(path->WE))
		return (err("Error\nWE texture file have to be a .xpm or .png file\n"),
			1);
	if (!is_xpm_png_file(path->EA))
		return (err("Error\nEA texture file have to be a .xpm or .png file\n"),
			1);
	return (0);
}

int	check_rgb(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((mlx->floor[i] < 0 || mlx->floor[i] > 255) || (mlx->ceiling[i] < 0
				|| mlx->ceiling[i] > 255))
			return (err("Error\nInvalid rgb color\n"), 1);
		i++;
	}
	return (0);
}

int	*convert_char_int(char **str)
{
	int	i;
	int	*res;

	i = 0;
	res = malloc(sizeof(int) * 4);
	while (i < 3)
	{
		res[i] = ft_atoi(str[i]);
		free(str[i]);
		i++;
	}
	free(str);
	return (res);
}

int	check_path(t_mlx *mlx, t_path **path)
{
	char	**floor;
	char	**ceiling;

	*path = malloc(sizeof(t_path));
	if (!*path)
		return (1);
	(*path)->NO = get_path(mlx->file, "NO");
	if (!(*path)->NO)
		return (err("Error\nNO path is missing\n"), 1);
	(*path)->SO = get_path(mlx->file, "SO");
	if (!(*path)->SO)
		return (err("Error\nSO path is missing\n"), 1);
	(*path)->WE = get_path(mlx->file, "WE");
	if (!(*path)->WE)
		return (err("Error\nWE path is missing\n"), 1);
	(*path)->EA = get_path(mlx->file, "EA");
	if (!(*path)->EA)
		return (err("Error\nEA path is missing\n"), 1);
	if (check_path_file(*path))
		return (1);
	floor = ft_split(get_path(mlx->file, "F"), ',');
	ceiling = ft_split(get_path(mlx->file, "C"), ',');
	if (!floor)
		return (err("Error\nFloor color is missing\n"), 1);
	if (!ceiling)
		return (err("Error\nCeiling color is missing\n"), 1);
	mlx->floor = convert_char_int(floor);
	mlx->ceiling = convert_char_int(ceiling);
	if (check_rgb(mlx))
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "C", 1) || !ft_strncmp(line, "F", 1))
		return (0);
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_is_at_end(char **file)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (file[i])
	{
		if (is_map_line(file[i]))
		{
			map_start = i;
			break ;
		}
		i++;
	}
	if (map_start == -1)
		return (1);
	while (file[i])
	{
		if (!is_map_line(file[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_file(t_mlx *mlx)
{
	if (!check_identifier(mlx->file, "NO") || !check_identifier(mlx->file, "SO")
		|| !check_identifier(mlx->file, "WE") || !check_identifier(mlx->file,
			"EA") || !check_identifier(mlx->file, "F")
		|| !check_identifier(mlx->file, "C"))
		return (1);
	if (check_order(mlx->file))
		return (1);
	if (check_path(mlx, &mlx->path))
		return (1);
	if (check_map_is_at_end(mlx->file))
		return (err("Error\nMap is not at the end of file\n"), 1);
	return (0);
}

int	check_map_borders(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (map[i][len - 1] == ' ')
			len--;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if (map[i][j] != '1' || map[i][len - 1] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	return (0);
}

int	check_map_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[0][i])
	{
		while (map->map[0][i] == ' ' || map->map[0][i] == '\t')
			i++;
		if (map->map[0][i] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	i = 0;
	while (map->map[map->height - 1][i])
	{
		while (map->map[map->height - 1][i] == ' ' || map->map[map->height
			- 1][i] == '\t')
			i++;
		if (map->map[map->height - 1][i] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
			{
				if (i > 0 && map->map[i - 1][j] != '1' && map->map[i
					- 1][j] != ' ' && ft_isalnum(map->map[i - 1][j]))
					return (err("Error\nMap should be surrounded by walls\n"),
						1);
				if (i < map->height - 1 && map->map[i + 1][j] != '1'
					&& map->map[i + 1][j] != ' ' && ft_isalnum(map->map[i
						+ 1][j]))
					return (err("Error\nMap should be surrounded by walls\n"),
						1);
				if (j > 0 && map->map[i][j - 1] != '1' && map->map[i][j
					- 1] != ' ' && ft_isalnum(map->map[i][j - 1]))
					return (err("Error\nMap should be surrounded by walls\n"),
						1);
				if (map->map[i][j + 1] && map->map[i][j + 1] != '1'
					&& map->map[i][j + 1] != ' ' && ft_isalnum(map->map[i][j
						+ 1]))
					return (err("Error\nMap should be surrounded by walls\n"),
						1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_elements(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'W' && map->map[i][j] != 'E'
				&& map->map[i][j] != ' ' && map->map[i][j] != '\t'
				&& map->map[i][j] != 'D')
				return (err("Error\nMap contains invalid elements\n"), 1);
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count == 0)
		return (err("Error\nMap doesnt contain a starting position\n"), 1);
	else if (count > 1)
		return (err("Error\nMap contains more than one starting position\n"),
			1);
	return (0);
}

int	check_map_path(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				if (map->map[i][j + 1] == '1' && map->map[i][j - 1] == '1'
					&& map->map[i + 1][j] == '1' && map->map[i - 1][j] == '1')
					return (err("Error\nPlayer cannot move\n"), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	if (check_map_borders(map->map))
		return (1);
	if (check_map_walls(map))
		return (1);
	if (check_map_elements(map))
		return (1);
	if (check_map_path(map))
		return (1);
	return (0);
}
