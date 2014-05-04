#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct person{
    char * name;
    int pocet;
    char **priatelia;
}Person;

void tlac(Person *DB,int pocet);
int highest(Person *DB,int pocet);
void tlacO(Person *person);
void freeD(Person *DB,int pocet);

int main(int argc, char **argv)
    {
        if(argc!=3){
            printf("Chybny pocet argumentov \n");
            return 1;
        }
        int pocet=atoi(argv[2]);
        FILE *input=fopen(argv[1],"r");
        Person DB[pocet];
        int pocetO=0; //budeme si pametat pocet osob aby sme nemali jednu osobu viacej krat
        for(int j=0;j<pocet;j++){ //jeden cyklus = jeden riadok
            char c;
            int i=0; //pocitadlo
            int memSize=1; //velkost pamete
            char *buffer=malloc(sizeof(char)); //tu ulozime retazec
            while((c=fgetc(input))!='\n'&&c!=EOF){
                if(i==memSize){
                    memSize*=2;
                    buffer=realloc(buffer,memSize);
                }
                buffer[i]=c;
                i++;
            }
            buffer=realloc(buffer,i+1);
            buffer[i]='\0';
            //parsovanie
            char *pch; //pomocny pointer
            pch=strtok(buffer,":");
            int flag=0; //kontrola ci meno uz neexistuje
            int konO=0; //cislo osoby kde uz je zaznam
            for(int k=0;k<pocetO;k++){
                if((strcmp(DB[k].name,pch))==0){  //porovname mena
                    flag=1; //ak sa meno uz nachadza v zozname
                    konO=k;
                }
            }
            if(flag==0){ //nova osoba
                DB[pocetO].name=malloc(sizeof(char)*(strlen(pch)+1));
                DB[pocetO].pocet=0;
                DB[pocetO].priatelia=(char**)malloc(sizeof(char*)); //alokujeme miesto na pole priatelov
                strcpy(DB[pocetO].name,pch);
                pch=strtok(NULL,":");
                DB[pocetO].priatelia[0]=malloc(sizeof(char)*(strlen(pch)+1)); //alokujeme miesto pre prveho priatela do pola priatelov
                strcpy(DB[pocetO].priatelia[DB[pocetO].pocet],pch);
                DB[pocetO].pocet++;
                pocetO++;
            }else{
                pch=strtok(NULL,":");
                DB[konO].priatelia=(char**)realloc(DB[konO].priatelia,sizeof(char*)*((DB[konO].pocet)+1)); //zvetsime pole priatelov o novu polozku
                DB[konO].priatelia[DB[konO].pocet]=malloc(sizeof(char)*(strlen(pch)+1)); //alokujeme miesto konkretnej Osoby v jeho poly priatelov
                strcpy(DB[konO].priatelia[DB[konO].pocet],pch);
                DB[konO].pocet++;
            }
            free(buffer);
    }
    tlac(DB,pocetO); //vytlacime osoby
    int hight=highest(DB,pocetO); //najdenie osoby s najvetsim poctom priatelov
    tlacO(&DB[hight]);
    freeD(DB,pocetO);
    return 0;
}
void tlac(Person *DB,int pocet){ //tlac priatelov
        for(int j=0;j<pocet;j++){
            printf("Osoba %s ma %d priatelov, su to:",DB[j].name,DB[j].pocet);
            for(int k=0;k<DB[j].pocet;k++){ //vypis jednotlivych priatelov
                printf(" %s ",DB[j].priatelia[k]);
            }
            printf("\n");
        }
}
int highest(Person *DB,int pocet){ //najde uzivatela co ma najviac priatelov, vrati jeho poradie v DB
    int hight=0;
    for(int j=0;j<pocet;j++){
        if(DB->pocet>hight)
            hight=j; //cislo osoby
    }
    return hight;
}
void tlacO(Person *person){ //tlac konkretnej osoby
    printf("%s %d (",person->name,person->pocet);
    for(int k=0;k<person->pocet;k++){ //vypis jednotlivych priatelov
        printf(" %s ",person->priatelia[k]);
    }
    printf(" )\n");
}
void freeD(Person *DB,int pocet){
    for(int j=0;j<pocet;j++){
        for(int k=0;k<DB[j].pocet;k++){ //postupne uvolnovanie priatelov
            free(DB[j].priatelia[k]); //uvolnenie jedneho priatela
        }
        free(DB[j].priatelia);
        free(DB[j].name);
    }
}
