/**
Program vytváří kopie zadaných souborů s tím, že výskyty cifer jsou duplikovány o zadaný počet

Program dostane na příkazové řádce dva argumenty: vstupní soubor a maximální počet načítaných řádků
Program otevře vstupní soubor, načte po řádcích data z textového souboru do pole struktur (zadeklarujte si vhodně sami, jednotlivé struktury jsou dynamicky alokovány)
Program načítá řádky, dokud nenarazí na konec souboru nebo nedosáhne maximálního počtu načítaných řádků
Provede změny v každé ze struktur popsané níže (po načtení všech řádků do struktury, ne během načítání)
Vytvoří nový výstupní soubor pro každý řádek vstupu (výstupní_soubor, viz. níže) a zapíše do něj výstup ve formátu popsaném níže
Uvolní všechny ostatní zdroje, které za běhu využil (uvolnění dynamické paměti, apod)
Na stdout vypíše, kolik řádků bylo reálně zpracováno
Formát vstupního řádku (můžete spoléhat na jeho korektnost)
nepřekročí délku 255 znaků
vstupní_soubor@výstupní_soubor:počet_opakování_cifry
např. 'dataIn.txt@dataout.txt : 5' (bez ')
Požadovaná úprava v každé ze struktur
pokud je jméno vstupního i výstupního souboru shodné, je k výstupnímu souboru přidána koncovka .res
pokud je jméno různé, jméno výstupního souboru zůstane nezměněno
Formát výstupního souboru
pokud vstupní soubor neobsahuje žádné cifry, tak je obsah výstupního souboru identický
pokud obsahuje cifry, tak je výskyt každé cifry duplikován k-krát, kde k je rovno počet_opakování_cifry
např. sekvence ze vstupního souboru fdkljsefa45jksdf2nnn se změní na fdkljsefa444555jksdf222nnn, pokud je počet_opakování_cifry rovno 3
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef
struct{
    char* in;
    char* out;
    int num;
}line;


int main(int argc, char** argv)
{
    if(argc!=3){
        fprintf(stderr,"zly pocet vstupnych parametrov\n");
        return 1;
    }

    FILE* f= NULL;
    f= fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Nepodarilo sa otvorit subor\n");
        return 1;
    }
    int maxLines= atoi(argv[2]);
    line* lines[maxLines];
    int i=0;
    int c;
    int memSize=2;
    char* buffer= NULL;
    buffer= malloc(memSize);
    if(buffer==NULL){
        fprintf(stderr,"Nedostatok pamate\n");
        return 1;
    }
    int numLines=0;
    char* pch;
    while((c=fgetc(f)) != EOF){
        if(c=='\n'){
            buffer= realloc(buffer,i+1);
            buffer[i]='\0';
            pch= strtok(buffer,"@:");
            lines[numLines]= malloc(sizeof(line));
            lines[numLines]->in= malloc(strlen(pch)+1);
            if(lines[numLines]->in==NULL){
                fprintf(stderr,"Nedostatok pamate\n");
                return 1;
            }
            strcpy(lines[numLines]->in,pch);
            pch= strtok(NULL,"@:");
            lines[numLines]->out= malloc(strlen(pch)+1);
            if(lines[numLines]->out==NULL){
                fprintf(stderr,"Nedostatok pamate\n");
                return 1;
            }
            strcpy(lines[numLines]->out,pch);
            pch= strtok(NULL,"@:");
            lines[numLines]->num= atoi(pch);
            numLines++;
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
    FILE* out;
    FILE* in;
    for(i=0;i<numLines;i++){
        in= NULL;
        in= fopen(lines[i]->in,"r");
        if(in==NULL){
            fprintf(stderr,"Nepodarilo sa otvorit subor\n");
            return 1;
        }
        free(lines[i]->in);
        out=NULL;
        out= fopen(lines[i]->out, "w");
        if(out==NULL){
            fprintf(stderr,"Nepodarilo sa otvorit subor\n");
            return 1;
        }
        free(lines[i]->out);
        while((c=fgetc(in))!=EOF){
            if(isdigit(c)){
                for(int j=0;j<lines[i]->num-1;j++){
                    fprintf(out,"%c",c);
                }
            }
            fprintf(out,"%c",c);

        }
        free(lines[i]);
    }
    fclose(in);
    fclose(out);

    return 0;
}

