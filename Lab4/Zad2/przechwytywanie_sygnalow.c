#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <unistd.h>
#include <stdlib.h>


void sig_handler_A(int sig)
{
	switch(sig)
	{
		//SIGALRM
		case 14: 
		{puts("Sygnal SIGALRM");
			exit(0);}
		break;
		//SIGTERM
		case 15:
		{puts("Sygnal SIGTERM");
			exit(0);}
		break;
		//SIGUSR1
		case 10:
		{puts("Sygnal SIGUSR1");
			exit(0);}
		break;
		//SIGUSR2
		case 12:
		{puts("Sygnal SIGUSR2");
			exit(0);}
		break;
	}
}

int main()
{
	// sigset_t signal_set; //zbiory sygnałów
	// sigemptyset(&signal_set); //inicjalizacja na pusty
	// sigaddset(&signal_set,SIGALRM); // dodanie sygnału
	// sigaddset(&signal_set,SIGTERM); // dodanie sygnału
	// sigaddset(&signal_set,SIGUSR1); // dodanie sygnału
	// sigaddset(&signal_set,SIGUSR2); // dodanie sygnału
	// sigprocmask(SIG_BLOCK,&signal_set,NULL); // blokowanie sygnałów
	//w tym zbiorze sygnałów (signal_set)
	
	// sigprocmask(SIG_UNBLOCK,&signal_set,NULL); // odblokowanie
	// tego sygnału

	struct sigaction act;
	act.sa_handler = sig_handler_A;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGALRM,&act,NULL);
	sigaction(SIGTERM,&act,NULL);
	sigaction(SIGUSR1,&act,NULL);
	sigaction(SIGUSR2,&act,NULL);
	

	int i = 1;
	while(1)
	{
		printf("%d\n",i);
		sleep(1);
		i++;
	}

}

