/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psapio <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:01 by psapio            #+#    #+#             */
/*   Updated: 2024/01/11 13:48:23 by psapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// no hacer lectura extra al final del archivo
// proteciones de el archivo vacio y fd incorecto
// si el BS es <= 0 protejer
// si 
//
#include "get_next_line.h"

#define IMMIGRANTS	BUFFER_SIZE

typedef struct s_data
{
	char sicily[IMMIGRANTS];
	char *aux;
	char *new_york;
} 	t_data;

void leaks()
{
	system("leaks -q a.out");
}

int counter_n0_str(char *str)
{
	int i;

	i = 0;
	while((str[i] != '\n') && (str[i] != '\0'))
		i++;
	return (i);
}

void	trip_to_NY(t_data *data, char **ellis_island)
{
	char *aux;
	int start_position;

	aux = *ellis_island;
	data->new_york = ft_substr(*ellis_island, 0, (counter_n0_str(*ellis_island) + 1));
	start_position = counter_n0_str(*ellis_island) + 1;	
//	*ellis_island = ft_strdup(&(*ellis_island)[start_position]);
	*ellis_island = ft_substr(*ellis_island, start_position, ft_strlen(*ellis_island));
	free(aux);
}

char *get_next_line(int fd)
{
	t_data 		data;
    static char *ellis_island;
    int         boat_captain_report;

    if (fd < 0 || (boat_captain_report = read(fd, NULL, 0) == -1))
	{
		free(ellis_island);
		ellis_island = NULL;
        return (NULL);
	}
    boat_captain_report = 1;
    if (ellis_island == NULL)
        ellis_island = ft_strdup("");
    while (boat_captain_report > 0)
    {
        boat_captain_report = read(fd, data.sicily, IMMIGRANTS);
		data.sicily[boat_captain_report] = '\0';
        data.aux = ellis_island;
        ellis_island = ft_strjoin(ellis_island, data.sicily);
        free(data.aux);
        if ((ft_strchr(ellis_island, '\n')) || (boat_captain_report == 0))
        {
            trip_to_NY(&data, &ellis_island);
			if (data.new_york[0] == '\0')
			{
				free(ellis_island);
				ellis_island = NULL;
                return (free(data.new_york), NULL); //no hay mas lineas
			}
            return (data.new_york); //lineas
        }
    }
	printf("exit3\n");
    return (NULL);
}

#ifdef MAIN
int main (int argc, char **argv)
{
	int fd;
	char *line;
	int i;

	atexit(leaks);

	if (argc < 2)
	{
		printf("Error!\n");
		return 1;
	}
	++argv;
	while (*argv)
	{
		fd = open(*argv, O_RDONLY);
		printf("\nOpen '%s' file\n", *argv);
		i = 0;
		while ((line = get_next_line(fd)))
		{
			printf("%i, line: '%s'", i, line);
			free(line);
			i++;
		}
		close(fd);
		printf("\nClose '%s' file\n", *argv);
		++argv;
	}
}
#endif
/*	
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
*/
/*
	close(fd);
	//getchar(); //mi blocca l'esecuzione peer fare un debug con "leack a.aut"
	//system("leaks a.out");
	return (0);
}*/
