

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
//===============================
// --- header ---			//
#include <stdio.h>			//
#include <stdlib.h>			//
#include <time.h>			//
#include <string.h>			//
#include <math.h>			//
#include <zip.h> 			//
//-------------------------------



//===================================================================================================================
/* 
-- calcT --
function for convert (time_t) 'y' (contains seconds) in format hours, minutes and seconds into var (struct tm) 'x'
see the documentation of time.h library for more information about the types and structures (time_t, struct tm) 

	||
	||
	\/ 
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
-- descriptZip ---
	||
	||
	\/ 
*/
//int descriptZip(char *source, char *caracters, int n, char *key){
int descriptZip(int n, char *archive){

	//consts
	const char* numeric 		= "1234567890";
	const char* lowerAlpha 		= "abcdefghijklmnopqrstuvwxyz";
	const char* upperAlpha 		= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char caracters[37] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *key;

	//vars
	struct zip *za;
    struct zip_file *zf;
    struct zip_stat sb;
    char buf[100];
    int err, testeExtr;

	zip_file_t *archDescript;
	int control[n], i, x, j, length = strlen(caracters), progress = 0;

	//abrindo o arquivo zip
	if(strstr(get_ext(archive), "zip") == NULL)
    {
        return -1;
    }

    if ((za = zip_open(archive, 0, &err)) == NULL) {
        return -1;
    }

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
				//printf("%s\t", key);

				//testando a senha atual
				int testExtract(char *key, struct zip *za, struct zip_stat sb, char buf[100]){
				testeExtr = testExtract(key, za, &sb, buf);

				if(testeExtr)
					continue;
				else
					return 0;
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
			// system("clear");
			// printf("\n\n[%.2f \%]\n", (float) (progress*100)/pow(length, n));
		}

	}
}
//------------------------------------------------------------------------------------------------------------------




int testExtract(char *key, struct zip *za, struct zip_stat sb, char buf[100]){

    
    int i, len;
    int fd;
    long long sum;
    
        
    zip_set_default_password(za, key);

        for (i = 0; i < zip_get_num_entries(za, 0); i++) {
            if (zip_stat_index(za, i, 0, &sb) == 0) {
                printf("==================\n");
                len = strlen(sb.name);
                printf("Name: [%s], ", sb.name);
                printf("Size: [%llu], ", sb.size);
                printf("mtime: [%u]\n", (unsigned int)sb.mtime);
                if (sb.name[len - 1] == '/') {
                    safe_create_dir(sb.name);
                } else {
                    zf = zip_fopen_index(za, i, 0);
                    if (!zf) {
                        goto final;
                    }
     
                    fd = open(sb.name, O_RDWR | O_TRUNC | O_CREAT, 0644);
                    if (fd < 0) {
                        goto final;
                    }

                    sum = 0;
                    while (sum != sb.size) {
                        len = zip_fread(zf, buf, 100);
                        if (len < 0) {
                            goto final;
                        }
                        write(fd, buf, len);
                        sum += len;
                    }
                    close(fd);
                    zip_fclose(zf);
                }
            } else {
                printf("File[%s] Line[%d]\n", __FILE__, __LINE__);
            }
        }
    if (zip_close(za) == -1) {
        return -1;
    }
    printf("SUCESS!!\nkey: %s\n", key);
    return 0;
}




//===================================================================================================================
/*
-- verifyArgs --
this function search for index of 'const *args[]' with 'n' elements that have string of '*find'
and return -1 case have not found, or the index that have found
	||
	||
	\/ 
*/
int verifyArgs(char const *args[], char *find, int n){
	for(int i = 0; i < n; i++){
		if(!strcmp(args[i], find)){
			return i;
			break;
		}
	}
	return -1;
}
//------------------------------------------------------------------------------------------------------------------




//===================================================================================================================
/*
-- MAIN --
	||
	||
	\/ 
*/

int main(int argc, char const *argv[]){
		
	//VERIFY SINTAXE
	//verify argv, in case of incorrect sintaxe show the comand for get help page (--help) 
	if(argc != 2 && argc != 4 && argc != 6){
		printf("\n[!] Sintaxe error! usage %s --help for more information\n\n", argv[0]);
		exit(1);
	}





	/*
	--------------------------------------------------
	help page by comand [--help]
		||
		||
		\/ 	
	*/

	if(argc == 2 && !strcmp(argv[1], "--help")){
		printf("\nPage Help\n");
		//****** need write
		return 0;
	}
	//-----------------------------------------------

	

	//vars
	int length, keyParamters;
	char *specialCharacters;
	struct tm *tempExec;
	time_t sec_ini, sec_end;


	/*
	-------------------------------------------------------------
	set the characters that will be tested
		||
		||
		\/
	*/

	// switch(argc){
	// 	case 2:
	// 		length = 8;
	// 		keyParamters = 7;
	// 		specialCharacters = NULL;
	// 	break;

	// 	case 4:

	// 	break;

	// }


	//APAGAR, APENAS PARA TESTE:
	
	

	//================================================
	/*			
	DESCRIPTION AND COUNT TIME
		||
		||
		\/ 
	*/
	time(&sec_ini);
	descriptZip(8);
	time(&sec_end);
	
	time_t dif = difftime(sec_end, sec_ini);
	calcT(tempExec, dif);
	//------------------------------------------------


	//=============================================================
	// show result
	printf("\n[+]Sucess!\nAll keys in %d hours, %d min and %d sec\n\n", 
	(*tempExec).tm_hour, (*tempExec).tm_min, (*tempExec).tm_sec);
	return 0;
	//---------------------------------------------
}
