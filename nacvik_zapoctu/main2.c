#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getLine(FILE* f){
    int c;
    int i=0;
    char* buffer = NULL;
    int memSize= 2;
    buffer= malloc(memSize);
    if(buffer == NULL){
        fprintf(stderr,"Nedostatok pamate!\n");
        return NULL;
    }
    while((c=fgetc(f))!='\n' && c!=EOF){
        if(i==memSize){
            memSize*= 2;
            buffer= realloc(buffer,memSize);
            if(buffer == NULL){
                fprintf(stderr,"Nedostatok pamate!\n");
                free(buffer);
                return NULL;
            }
        }
        buffer[i]=c;
        i++;
    }
    if(c==EOF){
        free(buffer);
        return NULL;
    }
    buffer= realloc(buffer, i+1);
    buffer[i]='\0';
    return buffer;
}
/**
 * Funkcia ktora nacitava riadky do dvojrozmerneho nepravouhleho pola
 * @brief readLinesToArray
 * @param f subor z ktoreho nacitavat
 * @param records pole do ktoreho zapisujeme
 * @return pocet nacitanych riadkov
 */
int readLinesToArray(FILE* f,char*** records){
    /*FUNKCNY READ RIADKU, KTORY ZAPISUJE DO DVOJROZMERNEHO NEPRAVOUHLEHO POLA*/
    int memSize= 2;
    *records= malloc(memSize*sizeof(char*));
    if(*records == NULL){
        fprintf(stderr,"Nedostatok pamate!\n");
        return 0;
    }
    char* read=NULL;
    int i=0;
    while((read=getLine(f))!=NULL){
        if(i==memSize){
            memSize*=2;
            *records= realloc(*records,memSize*sizeof(char*));
        }
        (*records)[i]= malloc(strlen(read)+1);
        strcpy((*records)[i],read);
        free(read);
        i++;
    }
    free(read);
    *records= realloc(*records,i*sizeof(char*));
    return i;
}

int main(int argc, char** argv){
    if(argc!=3){//skontrolujeme vstupny pocet argumentov
        fprintf(stderr,"Zly pocet argumentov");
        return 1;
    }

    FILE* f= NULL;
    f= fopen(argv[1],"r");//otvorime subor
    if(f==NULL){//skontrolujeme ci sa nam podarilo otvorit subor
        fprintf(stderr,"Nepodarilo sa otvorit subor");
        return 1;
    }
    char** records= NULL;
    int lines=0;
    if((lines=readLinesToArray(stdin,&records))==0){
        return 1;
    }
    for(int i=0;i<lines;i++){
        printf("%s\n",records[i]);
    }
    for(int i=0;i<lines;i++){
        free(records[i]);
    }
    free(records);
    return 0;
}
