#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])

{
    int fd[2];

    //utworzenie potoku
    pipe(fd);

    //utworzenie potomka
    int id = fork();

    if (id == 0)    //dziecko
    {
        //zamkniecie potoku dla wpisywania
        close(fd[1]);

        char bufor[BUFFER_SIZE];

        //czytanie z potoku
        while (read(fd[0], bufor, BUFFER_SIZE))
        {
            printf("#%s#\n", bufor);
        }
    }
    else if(id > 0) //rodzic
    {
        //zamkniecie potoku dla czytania
        close(fd[0]);

        char bufor[BUFFER_SIZE];
        FILE *file;
        
        //otwarcie pliku
        if(!(file = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Blad odczytu pliku\n");
			exit(1);
        }

        //czytanie z pliku i wpisywanie do potoku
        while (fgets(bufor, BUFFER_SIZE, file))
		{	
			write(fd[1], bufor, BUFFER_SIZE);
		}

        //zamkniecie pliku
        fclose(file);
    }
    else
    {
        fprintf(stderr, "Blad funkcji fork()\n");
    }
    
}