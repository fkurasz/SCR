#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

//deskryptory
int file;
int fmap;

//struktur rozmiaru pliku
struct stat stat_struct;

//dlugosc pliku czytanego
int f_length;
char f_name[100];
char bufor[1];
char *ptr_memory;

int main()
{
	//otwarcie pliku do mapowania
	if((fmap=open("shared_memory.txt",O_RDWR)) <= 0)
	{
		//jak nie ma to stworz
		fmap = open("shared_memory.txt", O_CREAT);
	}

	int pid = fork();

	//rodzic
	if(pid > 0)
	{
		while (1)
		{
			printf("Podaj nazwe obrazka: ");
			scanf("%s", f_name);

			//otwieranie pliku do odczytu
			if((file = open(f_name, O_RDONLY)) <= 0 )
			{
				fprintf(stderr, "Blad otwarcia pliku\n");
			}
			else
			{
				//dlugosc pliku png
				fstat(file, &stat_struct);

				//pusty plik
				if(stat_struct.st_size <= 0)
				{
					fprintf(stderr, "Blad w dlugosci pliku\n");
				}
				//plik ma cos w srodku
				else if(stat_struct.st_size > 0)
				{
					//mapowanie
					ftruncate(fmap, stat_struct.st_size);

					//bez tego nie ma gwarancji ze zmiany zostana zapisane przed wywolaniem munmap()
					msync(ptr_memory,stat_struct.st_size,MS_SYNC);
					munmap(ptr_memory,stat_struct.st_size);

					ptr_memory = mmap(NULL, stat_struct.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fmap, 0);
					read(file,ptr_memory,stat_struct.st_size);

				}
				close(file);
			}	
			printf("\n");
		}
	}
	//dziecko
	else if(pid == 0)
	{
		//0.1s
		usleep(100000);
        execlp("display", "display", "-update", "1", "shared_memory.txt", NULL);
	}
	else
	{
		fprintf(stderr, "Blad funkcji fork\n");
	}
	
	close(fmap);
	return 0;
}