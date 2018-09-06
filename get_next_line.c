/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:16:10 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/04 21:19:20 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** free_list
** Function frees element from linked list when related file is done reading.
** Frees the fixed size char buffer.  Updates the head of the list if the first
** element has been deleted.
*/

void	free_list(t_bufs *list, t_bufs **head)
{
	if (list->prev)
		list->prev->next = list->next;
	else
		*head = list->next;
	if (list->next)
		list->next->prev = list->prev;
	free(list->buf);
	free(list);
}

/*
** check_for_nl
** Helper function checks for a newline in the fixed size buffer.
** Any remaining charactars after the newline get moved to the beginning of
** the buffer so the next call to get_next_line can process characters
** already existing in the buffer before attempting to read more from the file
** descriptor.  Returns 0 if no newline is found so the read_line function knows
** to continue reading.
*/

int		check_for_nl(char *buf, char **line)
{
	char		*nl;
	char		*tmp;
	char		*tmp2;
	int			i;

	i = -1;
	if ((nl = ft_strchr(buf, '\n')))
	{
		tmp = (char *)ft_memalloc((int)(nl - buf + 1));
		while (++i < BUFF_SIZE && buf[i] != '\n')
			tmp[i] = buf[i];
		ft_memmove(buf, buf + i + 1, (int)(buf + BUFF_SIZE + 1 - nl));
		tmp2 = ft_strjoin(*line, tmp);
		free(tmp);
		free(*line);
		*line = tmp2;
		return (1);
	}
	tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = tmp;
	buf[0] = '\0';
	return (0);
}

/*
** read_line
** Helper function that reads from file descriptor into fixed size buffer.
** Allocates non-fixed size space to store entire line and stores address in
** *line.  Calls check_for_nl to check for a newline and determine if more 
** characters need to be read.
*/

int		read_line(int fd, t_bufs *list, char **line, t_bufs **head)
{
	int			bytes_read;
	char		*buf;

	buf = list->buf;
	*line = (char *)ft_memalloc(1);
	if (buf[0] && check_for_nl(buf, line))
		return (1);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		if (bytes_read == -1)
			return (-1);
		buf[bytes_read] = '\0';
		if (check_for_nl(buf, line))
			return (1);
	}
	if (line[0][0])
		return (1);
	free_list(list, head);
	free(*line);
	*line = NULL;
	return (0);
}

/*
** get_next_line
** Function uses static linked list to support multiple file descriptors.
** First call to function allocates head t_buffs element of linked list.
** File descriptor passed into the function gets stored in fd2 and incremented
** by one so stdin does not get confused as an unpopulated element in the list.
** While loop tries to locate an element corresponding to the file descriptor
** passed into the function.  If element does not exist then a new elem is
** created.
*/

int		get_next_line(const int fd, char **line)
{
	static t_bufs	*head = NULL;
	t_bufs			*tmp;
	int				fd2;

	if (line == NULL || fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	if (head == NULL)
		head = (t_bufs *)ft_memalloc(sizeof(t_bufs));
	tmp = head;
	fd2 = fd + 1;
	while (tmp->fd && tmp->fd != fd2)
	{
		if (!tmp->next)
			tmp->next = (t_bufs *)ft_memalloc(sizeof(t_bufs));
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp->fd)
	{
		tmp->fd = fd2;
		tmp->buf = (char *)ft_memalloc(BUFF_SIZE + 1);
	}
	return (read_line(fd, tmp, line, &head));
}
