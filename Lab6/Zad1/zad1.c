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

//dlugosc mapowanego pliku
int length;
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
		fprintf(stderr, "Blad otwarcia dzielonego pliku\n");
	}
	while(1)
	{
		printf("Podaj nazwe pliku: ");
		scanf("%s", f_name);

		//otwieranie pliku do odczytu
		if((file = open(f_name, O_RDONLY)) <= 0 )
		{
			fprintf(stderr, "Blad otwarcia pliku\n");
		}
		else
		{
			//dlugosc plikow
            		fstat(file, &stat_struct);
			f_length = stat_struct.st_size;
			fstat(fmap, &stat_struct);
			length = stat_struct.st_size;

			//pusty plik
			if(f_length == 0)
			{
				printf("Plik jest pusty\n");
			}
			//plik ma cos w srodku
			else if(f_length > 0)
			{
				printf("Dlugosc pliku: %d \n", f_length);

				//mapowanie (to co juz jest plus nowe)
				ftruncate(fmap, stat_struct.st_size + f_length);
				ptr_memory = mmap(NULL, stat_struct.st_size + f_length, PROT_READ | PROT_WRITE, MAP_SHARED, fmap, 0);

                		int i = 0;
				//wpisanie do wspodzielonego pliku
				while(read(file,bufor,1) > 0)
				{
					ptr_memory[length + i] = bufor[0];
                    			i++;
               			}
				printf("Koniec mapowania\n");
			}
			close(file);
		}	
		printf("\n");
	}
	close(fmap);
	return 0;
}
