#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void calcT(struct tm *x, time_t y){
	x->tm_hour = 0;
	x->tm_min = 0;
	x->tm_sec = 0;
	if(y < 60){
		x->tm_sec = (int)y;
		return;
	}
	if((x->tm_min = (int)y/60) < 60){
		x->tm_sec = (int)y%60;
		return;
	}
	x->tm_hour = (int)x->tm_min/60;
	x->tm_min %= 60;
	x->tm_sec = y%60;

}


int main()
{
	struct tm *tempExec;
	time_t sec_ini, sec_end;
	time(&sec_ini);

	int i;
	char comand[100];

	i = 0;
	while(i < 10000){

		for (int j = 0; j < 100; j++, i++){
			sprintf(comand, "unzip -t -qq -P %d facil.zip\n", i);
			system(comand);
		}
		system("clear");
		printf("%d \%\n", (i*100)/10000);
	}

	time(&sec_end);
	time_t dif = difftime(sec_end, sec_ini);
	calcT(tempExec, dif);
	printf("\nCompleto!\nTodas as senhas foram testadas em %d horas, %d min e %d sec", (*tempExec).tm_hour, (*tempExec).tm_min, (*tempExec).tm_sec);
	return 0;
}