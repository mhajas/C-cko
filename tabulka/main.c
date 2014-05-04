/**
Váš program dostane jeden textový argument na příkazové řádce – název vstupního souboru.
Tento soubor obsahuje předem neznámý počet řádků (UNIXový textový soubor, každý řádek končí znakem LF), a tyto řádky mají předem neznámou délku.
Řádky jsou rozděleny určitým počtem čárek – tento počet je pro všechny řádky stejný.
Mezi dvěma čárkami ale nemusí být žádný text.
Řádky jsou řádky v tabulce, čárky oddělují jednotlivé sloupce.
Vaším úkolem bude načíst položky tabulky do vhodné struktury, a následně ji na standardní výstup naformátovat tak, že každý sloupec má velikost nejdelší položky ve sloupci (s vhodným ohraničením buňek).

Příklad, vstup:
SKUPINA,,,
ovoce,jablko,hruška,slivovice
zelenina,mrkev,zelí,paprika
operační systém,DOS,Linux,BSD


Výstup:
    ukazka.png

Poznámky
Program nemusí brát v úvahu ne-ASCII znaky. Můžete předpokládat, že každý bajt řetězce zabere stejné místo na výstupu. (Můžete zkusit správně zpracovat UTF-8.)
Můžete předpokládat maximální délku řádku 1024 bajtů. (Měli byste zvládnout i pro libovolnou délku.)
Můžete předpokládat maximum 64 sloupců. (Měli byste zvládnout i pro libovolný počet.)
Pište program už od začátku rozdělený na vhodné funkce. První by měl být napsaný několikařádkový main().
Jednotlivé řádky tabulky je vhodné ukládat do spojovaného seznamu. Vzhledem k formě výpisu je nutné načíst celý soubor před výpisem.
*/

/**
 * autor: Michal Hajas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char** data;
    struct node* pNext;
};

struct list{
    struct node* start;
    struct node* end;
    int* width;
};

struct node* addNode(struct list* zoznam){ //funkcia pridava novy uzol na koniec listu a vracia pointer na neho
    struct node* novy= NULL;
    novy = malloc(sizeof(struct node));
    if(novy == NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return NULL;
    }
    if(zoznam->end != NULL){
        zoznam->end->pNext= novy;
    }
    zoznam->end= novy;
    if(zoznam->start == NULL){
        zoznam->start= novy;
    }
    novy->data= NULL;
    novy->pNext= NULL;
    return novy;
}

int getAndStoreLine(FILE* f,struct list* zoznam){
    int c;
    int i=0;
    char buffer[1025];
    while((c=fgetc(f))!=10 && c!=EOF){
        buffer[i]=c;
        i++;
    }
    buffer[i]='\0';
    if(i==0){
        return 0;
    }
    if(*zoznam->width==0){
        for(int j=0;j<i;j++){
            if(buffer[j]==','){
                *zoznam->width=*zoznam->width+1;
            }
        }
        *zoznam->width=*zoznam->width+1;
    }


    struct node* novy= addNode(zoznam);
    char* pch= strtok(buffer,",");
    novy->data=NULL;
    novy->data= malloc(sizeof(char*)*(*zoznam->width));
    if(novy->data==NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return 0;
    }
    int num=0;
    for(int j=0;j<*zoznam->width;j++){
        novy->data[j]= NULL;
        num= (pch == NULL) ? 0 : (int) strlen(pch);
        novy->data[j]= malloc(sizeof(char)*num+1);
        if(novy->data[j] == NULL){
            fprintf(stderr,"Nedostatok pamate\n");
            return 0;
        }
        if(pch!=NULL){
            strcpy(novy->data[j],pch);
            pch= strtok(NULL,",");
        }else{
            novy->data[j][0]='\0';
        }
    }
    return 1;
}

void nullWidth(int* ar, int width){
    for(int i = 0;i < width; i++){
        ar[i] = 0;
    }
}

void getMaxWidth(int * ar,struct list* zoznam){
    struct node* current= zoznam->start;
    int p=0;
    while(current->pNext!=NULL){
        if(p){
            current= current->pNext;
        }
        p=1;
        for(int i=0;i<(*zoznam->width);i++){
            if(ar[i] < (int) strlen(current->data[i])){
                ar[i]= (int) strlen(current->data[i]);
            }
        }
    }
}

void printLine(int* width,int w){
    printf("o");
    for(int i=0;i<w;i++){
        for(int j=0;j<width[i]+2;j++){
            printf("-");
        }
        printf("o");
    }
    printf("\n");

}

void writeTable(struct list* zoznam, int* width){
    struct node* current= zoznam->start;
    int p=0;
    while(current->pNext!=NULL){
        if(p){
            current= current->pNext;
        }
        p=1;
        printLine(width,*zoznam->width);
        printf("%c",124);
        for(int i=0;i<(*zoznam->width);i++){
            printf(" %s ",current->data[i]);
            for(unsigned int j=0;j<width[i]-strlen(current->data[i]);j++){
                printf(" ");
            }
            printf("%c",124);
        }
        printf("\n");
    }
    printLine(width,*zoznam->width);
}

void freeMemory(struct list* zoznam, FILE* f){
    struct node* current= zoznam->start;
    int p=0;
    struct node* before;
    while(current->pNext!=NULL){
        if(p){
            current= current->pNext;
        }
        for(int i=0;i<(*zoznam->width);i++){
            free(current->data[i]);
        }
        free(current->data);
        if(p){
            free(before);
        }
	before= current;
        p=1;
    }
    free(before);
    free(zoznam->width);
    free(zoznam);
    fclose(f);
}

int main(int argc, char** argv)
{
    if(argc!=2){
        fprintf(stderr,"Prilis malo argumentov\n");
        return 1;
    }

    FILE* f= NULL;
    f= fopen(argv[1],"r");

    struct list* zoznam=NULL;
    zoznam=malloc(sizeof(struct list));
    if(zoznam==NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return 1;
    }
    zoznam->start= NULL;
    zoznam->end= NULL;
    zoznam->width= malloc(sizeof(int));
    *zoznam->width=0;

    while(getAndStoreLine(f,zoznam));
    int width[*zoznam->width];
    nullWidth(width,*zoznam->width);
    getMaxWidth(width,zoznam);

    writeTable(zoznam,width);
    freeMemory(zoznam,f);
    return 0;
}

