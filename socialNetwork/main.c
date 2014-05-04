/**
Program provádí analýzu struktury sociální sítě.

Program dostane na příkazové řádce dva argumenty: vstupní soubor a maximální počet načítaných řádků
Pokud nejsou zadány korektně data na příkazovém řádku, program vypíše nápovědu a skončí
Vstupní soubor obsahuje seznam přátel na sociální síti ve formátu osoba:přítel (obě položky jsou jména z tisknutelných znaků)
Každý řádek obsahuje právě jeden záznam
Můžete předpokládat korektní formát vstupního souboru
Jedna osoba může mít více přátel, jejich celkový počet není omezen
Zadefinujte si vhodně strukturu pro každou osobu.
Tato struktura bude v sobě obsahovat jméno osoby, počet přátel a dynamicky alokované pole nebo seznam se jmény všech přátel.
Pole nebo seznam bude právě tak velký, kolik má osoba přátel (tj. žádná nadbytečná alokace)
Všechny načtené osoby (struktury) uložte do vhodného pole nebo seznamu
Po načtení všech osob nalezněte a vypište osobu s největším počtem přátel ve formátu jméno_osoby = počet_přátel (jména přátel)
Nápověda: Vstupní soubor můžete projít a zpracovat vícekrát
Program nebude obsahovat memory leaky, neuzavřené soubory, zápis mimo alokovanou pamět a bude dodržovat konvence programování běžně používané v předmětu
Pro vstupní data:

Tomas Jedno: Michal Blazek
Roman Havran:Misa Rychtarova
Tomas Jedno:Martin Smrk
Vypíše:

Tomas Jedno = 2 (Michal Blazek, Martin Smrk)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
struct friendNode{
    char* data;
    struct friendNode* pNext;
}friendNode;

typedef
struct friendList{
    friendNode* start;
    friendNode* end;
}friendList;

typedef
struct personNode{
    char* data;
    int numOfFriends;
    friendList* friends;
    struct personNode* pNext;
}personNode;

typedef
struct personList{
    personNode* start;
    personNode* end;
}personList;

personNode* searchPerson(char* person, personList* persons){
    personNode* current= persons->start;
    while(current->pNext != NULL){
        if(strcmp(person,current->data)==0){
            return current;
        }
        current= current->pNext;
    }
    if(strcmp(person,current->data)==0){
        return current;
    }
    return NULL;
}

personNode* addPersonNode(personList* persons){
    personNode* newe= NULL;
    newe= malloc(sizeof(personNode));
    newe->pNext=NULL;
    newe->friends= NULL;
    newe->friends= malloc(sizeof(friendList));
    if(newe->friends == NULL){
        fprintf(stderr,"Nedostatok pamate\n");
    }
    newe->friends->start= NULL;
    newe->friends->end= NULL;
    newe->numOfFriends=0;
    newe->data= NULL;
    if(persons->start==NULL){
        persons->start= newe;
        persons->end= newe;
    }else{
        persons->end->pNext= newe;
    }
    return newe;
}

friendNode* addFriendNode(friendList* friends){
    friendNode* newe= NULL;
    newe= malloc(sizeof(friendNode));
    newe->pNext=NULL;
    newe->data= NULL;
    if(friends->start==NULL){
        friends->start= newe;
    }else{
        friends->end->pNext= newe;
    }
    friends->end= newe;
    return newe;
}

void addPersonAndFriend(char* buffer,personList* persons){
    personNode* person= NULL;
    char* pch= strtok(buffer,":");

    if(persons->start==NULL){ //zistenie ci osoba existuje
        person= addPersonNode(persons);
    }else{
        if((person=searchPerson(pch,persons))==NULL){
            person= addPersonNode(persons);
        }
    }

    if(person->data==NULL){ //kopirovanie mena
        person->data= malloc(strlen(pch)+1);
        if(person->data == NULL){
            fprintf(stderr,"Nedostatok pamate\n");
        }
        strcpy(person->data,pch);
    }
    pch= strtok(NULL,":");
    friendNode* friendo= NULL;
    friendo= addFriendNode(person->friends);
    friendo->data= malloc(strlen(pch)+1);
    if(friendo->data == NULL){
        fprintf(stderr,"Nedostatok pamate\n");
    }
    strcpy(friendo->data,pch);
    person->numOfFriends=person->numOfFriends+1;
}

personNode* getMostFriendPerson(personList* persons){
    personNode* current= persons->start;
    if(current==NULL){
        fprintf(stderr,"No persons\n");
        return NULL;
    }
    personNode* max=persons->start;
    while(current->pNext!=NULL){
        current= current->pNext;
        if(current->numOfFriends > max->numOfFriends){
            max=current;
        }
    }
    return  max;
}

void printFriends(friendList* friends){
    friendNode* current= friends->start;
    printf(current->data);
    while(current->pNext!=NULL){
        current= current->pNext;
        printf(", %s",current->data);
    }
}
void freeFriends(friendList* friends){
    friendNode* current= friends->start;
    friendNode* before= NULL;
    free(current->data);
    before= current;
    while(current->pNext != NULL){
        current= current->pNext;
        free(current->data);
        free(before);
        before= current;
    }
    free(before);
    free(friends);
}

void freeMemory(personList* persons){
    personNode* current= persons->start;
    personNode* before;
    freeFriends(current->friends);
    free(current->data);
    before= current;
    while(current->pNext != NULL){
        current= current->pNext;
	freeFriends(current->friends);
        free(current->data);
        free(before);
        before= current;
    }
    free(before);
    free(persons);
}

int main(int argc, char** argv)
{
    if(argc!=2){
        fprintf(stderr,"Prilis malo argumentov[./program 'nazov suboru']\n");
        return 1;
    }

    FILE* f = NULL;
    f= fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Nepodarilo sa nacitat subor\n");
    }
    int i=0;
    int c;
    int memSize=2;
    char* buffer= NULL;
    buffer= malloc(memSize);
    if(buffer==NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return 1;
    }
    personList* persons=NULL;
    persons= malloc(sizeof(personList));
    if(persons==NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return 1;
    }
    persons->start= NULL;
    persons->end= NULL;

    while((c=fgetc(f)) != EOF){
        if(c=='\n'){
            buffer= realloc(buffer,i+1);
            buffer[i]='\0';
            addPersonAndFriend(buffer,persons);
            free(buffer);
            memSize=2;
            buffer= NULL;
            buffer= malloc(memSize);
            if(buffer==NULL){
                fprintf(stderr,"Nedostatok pamate\n");
                return 1;
            }
            i=0;
            c=fgetc(f);
        }
        if(i==memSize){
            memSize*=2;
            buffer= realloc(buffer,memSize);
        }
        buffer[i]=c;
        i++;
    }
    free(buffer);
    fclose(f);
    personNode* max= NULL;

    max= getMostFriendPerson(persons);
    printf("%s = %d (",max->data,max->numOfFriends);
    printFriends(max->friends);
    printf(")\n");
    freeMemory(persons);
    return 0;
}

