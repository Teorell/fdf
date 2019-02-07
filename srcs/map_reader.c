/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 23:22:38 by lsandor-          #+#    #+#             */
/*   Updated: 2019/02/07 14:12:09 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	ft_save_coordinats(char **args, t_list **lst, int y, t_fdf *fdf)
{
	int x;
	t_pixel pixel;
	t_list *tmp;
	size_t struct_size;

	struct_size = sizeof(t_pixel);
	x = -1;
	while (args[++x])
	{
		pixel.x = x;
		pixel.y = y;
		pixel.z = ft_atoi(args[x]);
		if (pixel.z > fdf->options->max)
			fdf->options->max = pixel.z;
		if (pixel.z < fdf->options->min)
			fdf->options->min = pixel.z;
		ft_display_error(!(tmp = ft_lstnew(&pixel, struct_size)), MlcErr);
		ft_lstadd(lst, tmp);
	}
}

static	int	ft_count_width(char **line_args)
{
	int i;

	while (line_args[i])
		i++;
	return (i);
}

void	ft_read_map(int fd, t_list **lst, t_fdf *fdf)
{
	char *gnl;
	char **line_args;

	while (get_next_line(fd, gnl) > 0)
	{
		ft_display_error(!(line_args = ft_strsplit(gnl, ' ')), MlcErr);
		if (fdf->col == -1)
			fdf->col = ft_count_width(line_args);
		ft_display_error((fdf->col != ft_count_width(line_args)), MapError);
		ft_save_coordinats(line_args, lst, fdf->row, fdf);
		ft_free_args(&line_args, fdf->col);
		fdf->row++;
	}
}
