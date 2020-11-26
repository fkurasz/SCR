#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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

        //zamkniecie deskryptora 0
        close(0);

        //duplikowanie potoku na deskryptor 0
        dup(fd[0]);

        //zamkniecie potoku dla czytania
        close(fd[0]);

        //wyswietlenie w nowym procesie
        execlp("display","display",NULL);

        
    }
    else if(id > 0) //rodzic
    {   
        int file;
        int length;
        char bufor[BUFFER_SIZE];

        //otwarcie pliku
        if(!(file = open(argv[1], O_RDONLY)))
        {
            fprintf(stderr, "Blad odczytu pliku\n");
			exit(1);
        }

        //zamkniecie potoku dla czytania
        close(fd[0]);

        //czytanie z pliku i wpisywanie do potoku
        while (length = read(file,bufor,BUFFER_SIZE))
		{	
			write(fd[1], bufor, length);
		}

        //zamkniecie pliku
        close(file);
    }
    else
    {
        fprintf(stderr, "Blad funkcji fork()\n");
    }
    
}