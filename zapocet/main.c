#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef
struct keyword{
    char* data;
    int pocet;
}keyword;

int findKeywordId(keyword** DB,int num,char* search){
    for(int i=0;i<num;i++){
        if(strcmp(search,DB[i]->data)==0){
            return i;
        }
    }

    return -1;
}

char* getWord(FILE* f){
    int c;
    int i=0;
    char* buffer = NULL;
    int memSize= 2;
    buffer= malloc(memSize);
    if(buffer == NULL){
        fprintf(stderr,"Nedostatok pamate!\n");
        return NULL;
    }
    while((c=fgetc(f))!=' ' && c!=EOF && c!='\n' && isalpha(c)){
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

int compare (const void * a, const void * b)
{
    int first= (*(keyword*)b).pocet;
    int sec= (*(keyword*)a).pocet;
    printf("%d - %d\n",first,sec);
    return first - sec;
}

void freeMemory(keyword** DB, int num){
    for(int i=0;i<num;i++){
        free(DB[i]->data);
        free(DB[i]);
    }
    free(DB);
}

int main(int argc,char** argv)
{
    if(argc!=2){//osetrime argumenty
        fprintf(stderr, "Zly pocet vstupnych parametrov\n");
        return 1;
    }

    FILE* f= NULL;
    f= fopen(argv[1],"r");//otvorime subor
    if(f==NULL){//skontrolujeme ci sa nam podarilo otvorit subor
        fprintf(stderr,"Nepodarilo sa otvorit subor");
        return 1;
    }


    char* read= NULL;
    keyword** DB;
    int memSize=2;
    int i=0;
    int findNum=-1;
    DB= malloc(sizeof(keyword*)*memSize);
    if(DB == NULL){
            fprintf(stderr,"Nedostatok pamate!\n");
            return 0;
        }
    while((read=getWord(f))!=NULL){
        if(strlen(read)<3){
            free(read);
            continue;
        }
        if(i==memSize){
            memSize*=2;
            DB= realloc(DB,sizeof(keyword*)*memSize);
            if(DB == NULL){
                fprintf(stderr,"Nedostatok pamate!\n");
                return 0;
            }
        }

        if((findNum=findKeywordId(DB,i,read))!=-1){
            DB[findNum]->pocet+=1;
        }else{

            DB[i]=NULL;
            DB[i]= malloc(sizeof(keyword));
            if(DB[i] == NULL){
                fprintf(stderr,"Nedostatok pamate!\n");
                free(read);
                return 0;
            }
            DB[i]->data=NULL;
            DB[i]->data= malloc(strlen(read)+1);
            if(DB[i]->data == NULL){
                fprintf(stderr,"Nedostatok pamate!\n");
                free(read);
                return 0;
            }
            strcpy(DB[i]->data,read);
            DB[i]->pocet=1;
            i++;
        }
        free(read);
    }
    DB= realloc(DB,sizeof(keyword*)*i);
    if(DB == NULL){
        fprintf(stderr,"Nedostatok pamate!\n");
        free(read);
        freeMemory(DB,i);
        return 0;
    }


    //qsort(DB,3,sizeof(keyword**),compare);

    //compare((void*)DB[0],(void*)DB[1]);

    for(int j=0;j<i;j++){
        printf("%s = %d\n",DB[j]->data,DB[j]->pocet);
    }

    fclose(f);
    freeMemory(DB,i);
    return 0;
}

