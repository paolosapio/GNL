char	*get_next_line(int fd)
{
	/* Declaramos la variable estatica donde se guarda el sobrante */
	static char *platform;

	/* Vamos a ver si existe una linea ya en platform */
	if (existe_linea(platform))
	{
		char *side = extraer_linea(platform);
		platform = eliminar_linea(platform);
		return side;
	}

	/* Vamos a leer del archivo fd. Así, guardo en la estatica lo que tenía antes + lo que acabo de leer. Leemos hasta \n o hasta llegar al final del archivo que acaba siempre con un 'read 0' */
	platform = leer_archivo(fd, platform);

	/* En platform tenemos el sobrante de lo anteior + todo lo que acabamos de leer. Ahora extremos la linea */
	char *side = extraer_linea(platform);

	/* Eliminar la linea que hemos extraido */
	platform = eiminar_linea(platform);

	/* Devolvemos la linea */
	return side;
}
/*come risevare memoria per magazzinare dati del BUFFER_SIZE*/
char aux[BUFFER_SIZE + 1];
int length = read(fd, aux, BUFFER_SIZE);
aux[length] = '\0';
