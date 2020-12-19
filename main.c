

/*
 [Copyright Notice]
 	Copyright© 2020 Qayin
 
 [license notice]
 	This file is part of getZip.

    getZip is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    getZip is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>6.
 :)



[NOTES]
	this program use libzip library. see https://libzip.org/

	for install by apt:
		sudo apt install libzip-dev

*/
//=============================
// --- header ---			//
#include <stdio.h>			//
#include <stdlib.h>			//
#include <time.h>			//
#include <string.h>			//
#include <math.h>			//
#include <zip.h> 			//
//-----------------------------



//===================================================================================================================
/* 
--- calcT ---
function for convert (time_t) 'y' (contains seconds) in format hours, minutes and seconds into var (struct tm) 'x'
see the documentation of time.h library for more information about the types and structures (time_t, struct tm) 
*/
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
//------------------------------------------------------------------------------------------------------------------




//===================================================================================================================
/*
--- getAlphaNumber --- 
*/
int getAlphaNumber(int n){
	char *key, comand[100];
	char caracters[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int control[n], i, x, j, length = strlen(caracters), progress = 0;

	for(i=0; i < n; i++){ 

		key = (char*)malloc((i+2)*sizeof(char));
		key[i+1] = '\0';

		//init parameters
		for(j = 0; j <= i; j++){
			key[j] = caracters[0];
		}
		for(j=0; j < n; j++){
			control[j] = 0;
		}


		while(control[0] < length){ //enquanto o primeiro caractere da key não chegar no último caractere de teste

			//for para mudar o ultimo caractere com todas as possibilidades
			for(j=0; j < length; j++){
				key[i] = caracters[j];
				printf("%s\t", key);
				//sprintf(comand, "unzip -P %s -B -qq teste1.zip\n", key);
				//system(comand);
				progress++;
			}

			control[i] = j;

			for(j = i; j > 0 ; j--){
				if(control[j] >= length){
					control[j] = 0;
					control[j-1]+=1;
				}
				key[j] = caracters[control[j]];
			}
			key[0] = caracters[control[0]];
			system("clear");
			printf("%.2f \%\n", (float) (progress*100)/pow(length, n));

		}

	}
}
//------------------------------------------------------------------------------------------------------------------




//===================================================================================================================
/*
--- MAIN ---
*/
int main(int argc, char const *argv[]){
	

	//verify argv, if empty, the show the comand for help (--help) 
	if(argc < 2){
		printf("\n[!] Sintaxe error! usage %s --help for more information\n\n", argv[0]);
		exit(1);
	}


	/*
	help page by comand [--help]
	*/
	if(argc == 2 && !strcmp(argv[1], "--help")){
		printf("\nPage Help\n");
		//****** need write
		return 0;
	}

	/*
	validation of the argvs
	*/

	//begin validation

		//code here

	//end validação

	//vars
	int caracters;
	struct tm *tempExec;
	time_t sec_ini, sec_end;


	

	//standart
	printf("Numbers of caracteres:\n");
	scanf("%d", &caracters);

	time(&sec_ini);

	getAlphaNumber(caracters);
	
	time(&sec_end);


	//calc the execution time of the program
	time_t dif = difftime(sec_end, sec_ini);
	calcT(tempExec, dif);

	//SHOW, finish 
	printf("\n[+]Sucess!\nAll keys in %d hours, %d min and %d sec\n\n", (*tempExec).tm_hour, (*tempExec).tm_min, (*tempExec).tm_sec);
	return 0;
}
