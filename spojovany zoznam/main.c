/**
Úkol na cvičení: Převod pole záznamů jmen studentů (5. cvičení) do varianty s využitím jednostranně spojovaného seznamu, načítání ze souboru
pro každého studenta jeden záznam
na začátku není znám celkový počet záznamů
program načte ze souboru postupně jednotlivé řetězce (oddělené novým řádkem), načte je pomocí fscanf(file,"%s", jmeno);
Varianta 1: pomocí strlen zjistíme délku jména a dále budeme pracovat pouze s touto délkou (hodnoty ve spojovaném seznamu jsou typu int)
Varianta 2: pracujeme přímo ukazatelem na jméno (hodnoty ve spojovaném seznamu jsou typu char*), vytváříme si jeho kopii stejně jako v předchozím cvičení
postupně vytváříme dynamicky spojovaný seznam. Při každém zadání nové položky celý seznam vypíšeme
vyzkoušíme detekce memory leaks v programu pomocí Valgrindu nebo Visual Studia
ukázka vzhledu dynamicky alokované struktury v debuggeru
Rozšíření: Upravte spojovaný seznam na oboustranně spojovaný
Rozšíření: Vkládejte položky tak, aby byl seznam seřazený podle položek (délka, lexikograficky)
Rozšíření: Odeberte položku ze seznamu, jejíž hodnotu zadá uživatel
Diskuze typických problémů/přístupů
signalizace poslední (a první) položky pomocí NULL
uvolnění všech položek na konci
správné udržování ukazatele na další/předchozí položku
procházení seznamu pomocí while (currentNode→pNext != NULL)
doporučená vizualizace tužka/papír
Pomocná funkce - načtení celého řádku s dynamickou alokací
vytvořte si funkci char* mygetline(FILE* soubor);
funkce předpokládá otevřený soubor pro čtení. Soubor není po konci uzavírán.
tato funkce načte ze zadaného vstupního souboru jeden řádek a vytvoří pro něj dostatečně dlouhý, dynamicky alokovaný řetězec
interní implementace bude používat getc(soubor) pro čtení vstupu po jednotlivých znacích a zvětšení interního řetězce, pokud dříve alokovaný nestačil
tj. ve funkci mygetline může dojít k několika malloc a free, nebo realloc
nezapomeňte uvolnit ve vašem programu řetězec vrácený funkcí mygetline
Problematika testování konce souboru
lze použít funkci feof(FILE*) na otestování (true/false), zda poskytnutý ukazatel FILE již přečetl konec souboru
většina funkcí pro čtení ze souboru vrací konstantu EOF, pokud dojde na konec souboru (vždy je nutné se dobře podívat na chování do dokumentace - např. cplusplus.com)
při použití feof() nestačí testovat pouze před použitím např. fscanf - na konci souboru může být třeba jen nový řádek, tedy feof() vrací FALSE, ale zároveň selže následné fscanf
funkce načítající znak ze souboru vrací int. Pokud se znak v pořádku načte, je char zvětšen na int a vrácen. Pokud ne, může být vrácen EOF (http://stackoverflow.com/questions/1561770/c-programming-eof-as-a-character)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef
struct node {
   struct node* pNext;  // pointer to next node in dynamically allocated list
   struct node* pPrev;
   char *data;            // data carried by this item
} zoznam;

void addStudent(zoznam** end, char* text){
    zoznam* temp=malloc(sizeof(zoznam));
    zoznam* temp2=NULL;
    if(*end!=NULL){
        (*end)->pNext=temp;
        temp2=(*end);
    }
    (*end)= temp;
    (*end)->data= malloc(strlen(text)+1);
    strcpy((*end)->data,text);
    (*end)->pNext=NULL;
    (*end)->pPrev=temp2;
}

void writeList(zoznam* start){
    zoznam* temp=start;
    do{
        printf("%s\n",temp->data);
        temp=temp->pNext;
    }while(temp->pNext!=NULL);
    printf("%s\n",temp->data);
}

void freeList(zoznam* start){
    zoznam* next=0;
    do{free(start->data);
        next=start->pNext;
        free(start);
        start=next;
    }while(next!=NULL);
}

char* myGetLine(FILE* subor){
    int size=0;
    char* buffer=NULL;
    int c=0;
    int i=0;
    while((c=getc(subor))!='\n' && c!=EOF){
        if(i==size){
            size+=5;
            buffer= realloc(buffer,size+1);
        }
        if(buffer==NULL){
            return 0;
        }
        *(buffer+i)=c;
        i++;
    }
    if(buffer==NULL){
        return 0;
    }
    *(buffer+i)='\0';
    return buffer;
}

void swap(zoznam** first, zoznam** sec){
    zoznam* temp1=(*first)->pPrev;
    zoznam* temp2=(*sec)->pNext;
    temp1->pNext=*sec;
    temp2->pPrev= *first;
    (*sec)->pPrev=temp1;
    (*sec)->pNext=*first;
    (*first)->pNext=temp2;
    (*first)->pPrev=*sec;
}

int main(void) {
    char* buffer=0;
    zoznam* start=0;
    zoznam* end=0;
    int i=0;
    FILE* f=NULL;
    f=fopen("vstup.txt","r");
    if(f==NULL)
        return 1;
    /*while(fscanf(f,"%99s",buffer)!=EOF){
        addStudent(&end,buffer);
        if(i==0){
            start=end;
            i=1;
        }
    }*/
    while((buffer=myGetLine(f))!=0){
        addStudent(&end,buffer);
        if(i==0){
            start=end;
            i=1;
        }
        free(buffer);
    }

    zoznam* p=start;
    zoznam* k=start;
    while(p->pNext!=NULL){
        while(k->pNext==NULL){
            if(strlen(k->data)<strlen((k->pNext)->data)){
                swap(&k,&k->pNext);
            }
            k++;
        }
        p++;
    }
    fclose(f);
    printf("vypis\n");
    writeList(start);

    freeList(start);
    return 0;
}
