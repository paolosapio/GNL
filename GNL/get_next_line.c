/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:01 by psapio            #+#    #+#             */
/*   Updated: 2023/12/14 16:17:44 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

#define BUFFER_SIZE	1
#define SIDE_A		0
#define AUX			1
#define SIDE_B		2

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*void leaks()
{
	system("leaks -q a.out");
}
*/
char    *ft_strdup(const char *s1)
{
    size_t  size_p;
    char    *s1double;
    size_t  i;

    i = 0;
    size_p = ft_strlen(s1);
    s1double = malloc(size_p + 1);
    if (s1double == NULL)
        return (NULL);
    while (s1[i] != '\0')
    {
        s1double[i] = s1[i];
        i++;
    }
    s1double[i] = '\0';
    return (s1double);
}

int counter_n0_str(char *str)
{
	int i;

	i = 0;
	while((str[i] != '\n') && (str[i] != '\0'))
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	char		*ps[3];
	static char *boat;
	int			read_check;

	if (fd < 0)
		return (NULL);
	ps[SIDE_A] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (ps[SIDE_A] == NULL)
        return (NULL);
	read_check = 1;
	while (read_check > 0)
	{
		read_check = read(fd, ps[SIDE_A], BUFFER_SIZE);
		ps[SIDE_A][read_check] = '\0';
		if (boat == NULL)
		{
			boat = ft_strdup(ps[SIDE_A]);
			free(ps[SIDE_A]);
		}
		else
		{
			ps[AUX] = boat;
			boat = ft_strjoin(boat, ps[SIDE_A]);
			free(ps[SIDE_A]);
			free(ps[AUX]);
		}
		if (ft_strchr(boat, '\n') || ft_strchr(boat, '\0'))
 		{
			ps[AUX] = boat;
			ps[SIDE_B] = ft_substr(boat, 0, (counter_n0_str(boat) + 1));	
			boat = ft_substr(boat, counter_n0_str(boat) + 1, (ft_strlen(boat)));
			free(ps[AUX]);
			return (ps[SIDE_B]);
		}
	//	leaks();
	}
	return (NULL);
}

#include <stdio.h>
int main (void)
{
	int fd;
	char *line;

	//atexit(leaks);
	//leaks();
	fd = open("poesia", O_RDONLY);
	
	while (1)
	{
//		printf("hola");
	//	usleep(100);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);

	//getchar(); //mi blocca l'esecuzione peer fare un debug con "leack a.aut"
	return (0);
}
