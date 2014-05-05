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




typedef
struct node{
    char* data;
    struct node* pNext;
}node;

typedef
struct list{
    node* start;
    node* end;
}list;

node* addNode(list* linkedList){ //funkcia prida novy uzol
    node* newe= NULL;
    newe= malloc(sizeof(node));
    newe->pNext=NULL;
    newe->data= NULL;
    if(linkedList->start==NULL){
        linkedList->start= newe;
    }else{
        linkedList->end->pNext= newe;
    }
    linkedList->end= newe;
    return newe;
}


/**
 * Funkcia ktora nacitava riadky do spojeneho zoznamu
 * @brief readLinesToLinkedList
 * @param f subor z ktoreho nacitava
 * @param linkedList zoznam do ktoreho ma nacitavat
 * @return pocet riadkov ktore nacitala
 */
int readLinesToLinkedList(FILE* f, list* linkedList){
    char* read=NULL;

    node* newe= NULL;
    int i=0;
    while((read=getLine(f))!=NULL){
        newe= addNode(linkedList);
        newe->data= malloc(strlen(read)+1);
        strcpy(newe->data,read);
        free(read);
        i++;
    }
    free(read);
    return i;
}

void freeArray(char** ar, int num){
    for(int i=0;i<num;i++){
        free(ar[i]);
    }
    free(ar);
}

void freeLinkedList(list* linkedList){
    node* current= linkedList->start;
        node* before;
        free(current->data);
        before= current;
        while(current->pNext != NULL){
            current= current->pNext;
            free(current->data);
            free(before);
            before= current;
        }
        free(before);
        free(linkedList);
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

    /*Nacitavanie cez zoznam aj s vypisom a mazanim pamate*//*
    list* records= NULL;
    records= malloc(sizeof(list));
    if(records == NULL){
        fprintf(stderr,"Nedostatok pamate!\n");
        return 0;
    }
    records->end= NULL;
    records->start= NULL;
    int lines=0;
    if((lines=readLinesToLinkedList(f,records))==0){
        printf("ziadnny riadok\n");
        return 1;
    }
    node* current= records->start;
    printf("%s\n",current->data);
    while(current->pNext!=NULL){
        current=current->pNext;
        printf("%s\n",current->data);
    }
    freeLinkedList(records);*/

    /*nacitavanie cez pole aj s vypisom a mazanim pamate*/
    char** records= NULL;
    int lines=0;
    if((lines=readLinesToArray(f,&records))==0){
        printf("ziadnny riadok\n");
        return 1;
    }

    for(int i=0;i<lines;i++){
        printf("%s\n",records[i]);
    }
    freeArray(records,lines);
    return 0;
}
