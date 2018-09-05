/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:16:26 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/04 01:41:23 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# define BUFF_SIZE 32

int					get_next_line(const int fd, char **line);

typedef struct		s_bufs
{
	int				fd;
	char			*buf;
	struct s_bufs	*prev;
	struct s_bufs	*next;
}					t_bufs;

#endif
