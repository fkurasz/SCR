#include <stdio.h>
#include <unistd.h>

int main()
{
	int i=0;
	while(1)
	{
			i++;
			usleep(100000);	
			//1 000 000 - 1s
			//  100 000 - 0.1s (100ms)
			printf("%d\n",i);
	}	
}
