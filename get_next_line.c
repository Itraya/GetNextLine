/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:37:27 by mlagrang          #+#    #+#             */
/*   Updated: 2021/11/12 13:53:54 by mlagrang         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *a)
{
	free(a);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*txt;
	int			i;

	i = 1;
	txt = NULL;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	if (ft_search(buff, '\n') != -1)
	{
		ft_cut(buff);
		txt = ft_join(txt, buff);
		if (txt[0] == '\0')
				txt = ft_free(txt);
	}
	while (ft_search(buff, '\n') == -1 && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			return (txt);
		buff[i] = '\0';
		txt = ft_join(txt, buff);
	}
	return (txt);
}

int	main(void)
{
	int	fd = open("41_with_nl", O_RDONLY);
	char	*a;
	for (int i = 0; i < 3; i++)
	{
		a = get_next_line(fd);
		printf("==%s\n", a);
		free(a);
	}
	close(fd);
}
