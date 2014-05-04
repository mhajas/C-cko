/**
Zadání nácvikového příkladu (bez hodnocení, zkuste si celý příklad ve vlastním zájmu vypracovat kompletně až na cvičení)
(zadání příkladu „naostro“ bude mít podobný styl zadání, ale samotný příklad bude jiný)
program načte data po řádcích z textového souboru (např. data.txt, stahněte zde: data_test1_2011.zip)
cesta k načítanému souboru je uvedena v prvním argumentu příkazového řádku
počet řádků v souboru je uveden jako druhý argument příkazového řádku
program se tedy spouští jako 'program data.dat 4'
každý řádek souboru obsahuje data ve formátu jmeno:prijmeni:vek (formát nemusíte kontrolovat)
řádek rozdělte dle symbolu : a naplňte jím dynamicky alokovanou položku typu 'struct Person', kterou vhodně zadeklarujte
(jméno a příjmení může být libovolně dlouhé, pro jejich uchování využijte dynamickou alokaci)
vytvořte samostatnou funkci, která bude přijímat jako argument jednu položku typu 'ukazatel na struct Person', převede jméno a příjmení na velká písmena a věk zvýší o 1
funkci zavolejte postupně nad všemi načtenými položkami
program uloží zpracovaná data do souboru se stejným jménem jako vstupní, ale s dodatečnou příponou .tmp (např. data.txt.tmp)
program bude udržovat v paměti všechny načtené položky ve vhodné datové struktuře (pole, list) - nelze tedy zpracovávat položky po jedné a ihned vypisovat do výstupního souboru
zdrojový kód bude dodržovat dobré programovací návyky, nebude obsahovat memory leaks a bude přiměřeně komentovaný
při vypracování příkladu můžete používat své vlastní kódy a dokumentaci nalezenou na internetu. Není povoleno spolupracovat s někým dalším
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Person{
    char* name;
    char* surname;
    int old;
};

void change(struct Person * x){
    for(unsigned int i=0;i<strlen(x->name);i++){ //zvacsime meno
        x->name[i]= toupper(x->name[i]);
    }
    for(unsigned int i=0;i<strlen(x->surname);i++){//zvacsime priezvisko
        x->surname[i]= toupper(x->surname[i]);
    }
    x->old++;
}

int main(int argc, char **argv)
{
    if(argc!=3){
        fprintf(stderr,"Zly pocet argumentov\n");
        return 1;
    }


    FILE* f=NULL;
    f= fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Nepodarilo sa nacitat subor\n");
        return 1;
    }
    int num= atoi(argv[2]);
    struct Person DB[num];

    int c;
    int size;
    int j;
    char* buffer=NULL;
    for(int i=0;i<num;i++){
        size=5;
        buffer=malloc(size);
        j=0;
        /*NACITAVANIE RIADKU*/
        while((c=fgetc(f))!='\n'){
            if(j==size){
                size*=2;
                buffer=realloc(buffer,size);
            }
            buffer[j]=c;
            j++;
        }
        buffer=realloc(buffer,j+1);
        buffer[j]='\0';
        /*KONIEC NACITAVANIA RIADKU*/
        /*PARSOVANIE*/
        char* pch=NULL;
        pch = strtok (buffer,":");
        DB[i].name= malloc(strlen(pch)+1);
        memset(DB[i].name,'\0',strlen(pch)+1);
        strcpy(DB[i].name,pch);
        pch = strtok (NULL,":");
        DB[i].surname= malloc(strlen(pch)+1);
        memset(DB[i].surname,'\0',strlen(pch)+1);
        strcpy(DB[i].surname,pch);
        pch = strtok (NULL,":");
        DB[i].old= atoi(pch);

        free(buffer);//upratanie
    }

    for(int i=0;i<num;i++){
        change(&DB[i]);
    }
    char asd[strlen(argv[1])+4+1];

    strcat(asd,argv[1]);
    strcat(asd+strlen(argv[1]),".tmp");
    FILE * vystup= fopen(asd,"w");
    for(int i=0;i<num;i++){
        fprintf(vystup,"%s:%s:%d\n",DB[i].name,DB[i].surname,DB[i].old);
    }

    fclose(vystup);

    for(int i=0;i<num;i++){
        free(DB[i].name);
        free(DB[i].surname);
    }
    fclose(f);
    return 0;
}

