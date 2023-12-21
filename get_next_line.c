/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:01 by psapio            #+#    #+#             */
/*   Updated: 2023/12/21 10:44:52 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// no hacer lectura extra al final del archivo
// proteciones de el archivo vacio y fd incorecto
// si el BS es <= 0 protejer
// si 
//
#include "get_next_line.h"

#define SICILY		0
#define AUX			1
#define NEW_YORK	2
#define IMMIGRANTS	BUFFER_SIZE

void leaks()
{
	system("leaks -q a.out");
}


char	*ft_strdup(const char *s1)
{
    size_t	size_p;
    char	*s1double;
    size_t	i;

    i =	0;
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

void	trip_to_NY(char **ps, char **ellis_island)
{
	free(ps[SICILY]);
	ps[AUX] = *ellis_island;
	ps[NEW_YORK] = ft_substr(*ellis_island, 0, (counter_n0_str(*ellis_island) + 1));
	*ellis_island = ft_substr(*ellis_island,
			counter_n0_str(*ellis_island) + 1, (ft_strlen(*ellis_island)));
	free(ps[AUX]);
}

char *get_next_line(int fd)
{
	char		*ps[3];
	static char *ellis_island;
	int			boat_captain_report;

	if (fd < 0)
		return (NULL);
	ps[SICILY] = malloc(sizeof(char) * (IMMIGRANTS + 1));
	if (ps[SICILY] == NULL)
        return (NULL);
	boat_captain_report = 1;
	while (boat_captain_report> 0)
	{
		boat_captain_report = read(fd, ps[SICILY], IMMIGRANTS);
		if (boat_captain_report == 0)
		{
			trip_to_NY(ps, &ellis_island);
			if (ps[NEW_YORK][0] == '\0')
			{
				free (ps[NEW_YORK]);
				return (NULL);
			}
			return (ps[NEW_YORK]);
		}
		ps[SICILY][boat_captain_report] = '\0';
		if (ellis_island == NULL)
			ellis_island = ft_strdup(ps[SICILY]);
		else
		{
			ps[AUX] = ellis_island;
			ellis_island = ft_strjoin(ellis_island, ps[SICILY]);
			free(ps[AUX]);
		}
		if (ft_strchr(ellis_island, '\n')) 
 		{
			trip_to_NY(ps, &ellis_island);
			return (ps[NEW_YORK]);
		}
	}
	return (NULL);
}

int main (void)
{
	int fd;
	char *line;

	atexit(leaks);
//	leaks();
	fd = open("poesia", O_RDONLY);
	
	do
	{
	//	usleep(1000);
		line = get_next_line(fd);
		if (line != NULL)
		{
			printf("line: %s", line);
			free(line);
		}
		if (line == NULL)
			free(line);
	} while (line);
	close(fd);
	//getchar(); //mi blocca l'esecuzione peer fare un debug con "leack a.aut"
	//system("leaks a.out");
	return (0);
}
