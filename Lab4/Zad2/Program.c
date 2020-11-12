#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int c = 0;

void sig_handler_A(int sig){
  if(sig == SIGALRM)
  printf("Sygnal SIGALRM\n");
  exit(0);
}

void sig_handler_B(int sig){
  printf("Sygnal SIGTERM\n");
}


void sig_handler_C(int sig){
  printf("Sygnal SIGUSR1\nWstrzymanie odbierania sygnalu na 1000 iteracji\n");
  c = 1000;
  signal(sig, SIG_IGN);
}


void sig_handler_D(int sig){
  printf("Sygnal SIGUSR2\nCalkowite ignorowanie sygnalu\n");
  signal(SIGUSR2, SIG_IGN);
}


int  main()
{
  struct timespec ts;
  ts.tv_sec = 1;
  ts.tv_nsec = 100*100000L;

  signal(SIGALRM, sig_handler_A);
  signal(SIGTERM, sig_handler_B);
  signal(SIGUSR1, sig_handler_C);
  signal(SIGUSR2, sig_handler_D);

  int i = 1;
  while(1){

	printf("%d\n",i);
	nanosleep(&ts,NULL);
    i++;

    if(c>0)
	{
	  c--;
      if(c == 0) 
	  	signal(SIGUSR1, sig_handler_C);
    }
  }
}
