/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:20:20 by dchen             #+#    #+#             */
/*   Updated: 2019/03/07 16:25:19 by dchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		count_line(const int fd, char **str)
{
	int i;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	return (i);
}

int		read_new_line(const int fd, char **line, char **str, int bytes_read)
{
	char	*temp;
	int		len;

	len = count_line(fd, str);
	if (str[fd][len] == '\n')
	{
		*line = ft_strsub(str[fd], 0, len);
		temp = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = temp;
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (str[fd][len] == '\0')
	{
		if (bytes_read == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strsub(str[fd], 0, len);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	int			bytes_read;
	char		*temp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		temp = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (-1);
	else if (bytes_read == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	return (read_new_line(fd, line, str, bytes_read));
}
