/*
Implementacny test IB002 - uloha 2. (8 bodov)
--------------------
Vyplnte nasledujici udaje:
Meno:
UCO:
Skupina (v ktere jste zapsany):
--------------------

Ukolem je vytvorit program, ktery prerovna vstupni sekvenci cisel tak, ze
licha cisla (nikoliv liche pozice v sekvenci) budou tvorit neklesajici
posloupnost a ze suda cisla zustanou jak byla.

Pouzijte MergeSort typ algoritmu s tim, ze deleni vstupu bude na dve pulky
a razeni bude radit pouze licha cisla. Suda cisla musi ve vysledku zustat
na svych puvodnich pozicich. Algoritmus nemusi byt "in situ", ale musi mit
casovou slozitost O(n.log(n)) vzhledem k delce vstupu n.

Reseni typu vykopirovani lichych cisel stranou, jejich samostatne serazeni
a nasledne vlozeni zpet do puvodniho vstupu sice vyhovuje zadani, ale pro
ucely tohoto testu je explicitne zapovezeno a nebude uznano.

Neni bezpodminecne nutne, abyste pouzili vychozi zdrojove kody. Je vsak
bezpodminecne nutne, abyste zachovali shodny vystup programu.

Po ukonceni prace nahrajte vas kod do odevzdavarny:
IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
Odevzdavejte jen zdrojovy kod, NEODEVZDAVEJTE soubory s nastavenim pro IDE.

*/

#include <stdio.h>
#include <stdlib.h>

/* Struktura popisujici dynamicke pole dane delky. */
typedef struct {
    /* Ukazatel na samotne pole, indexy jdou 0 az length-1. */
    int* data;

    /* Aktualni delka tohoto pole. */
    int length;
} Array;


/* Pomocna funkce, ktera vraci 1 pokud je vstup liche cislo
   a ktera jinak vraci 0. */
int IsOdd(const int val) {
    if (val & 1)
        return 1;
    else
        return 0;
}


/* Pomocna funkce, ktera vypise na radek obsah pole. */
void PrintAll(Array arr) {
    if (arr.length == 0) {
        printf("Empty array.\n");
        return;
    }

    int i=0;
    /* Odkomentujte nasledujici blok pokud chcete, aby vypis obsahoval
       jeste radek s indexy do pole. */
    /*
    for (; i < arr.length; ++i)
        printf("%3i: ",i);
    printf("\n");
    */

    for (i=0; i < arr.length; ++i)
        printf("%3i  ",arr.data[i]);
    printf("\n");
}


/* Pomocna funkce, ktera vypise na radek licha cisla z pole. */
void PrintOdd(Array arr) {
    if (arr.length == 0) {
        printf("Empty array.\n");
        return;
    }

    int i=0;
    for (; i < arr.length; ++i)
        if (IsOdd(arr.data[i]))
            printf("%3i  ",arr.data[i]);
        else
            printf("     ");
    printf("\n");
}


/* Pomocna funkce, ktera vypise na radek suda cisla z pole. */
void PrintEven(Array arr) {
    if (arr.length == 0) {
        printf("Empty array.\n");
        return;
    }

    int i=0;
    for (; i < arr.length; ++i)
        if (! IsOdd(arr.data[i]))
            printf("%3i  ",arr.data[i]);
        else
            printf("     ");
    printf("\n");
}


/* Pomocna funkce, ktera overi, jestli licha cisla z pole
   tvori neklesajici posloupnost */
void AreOddNondecreasing(Array arr) {
    if (arr.length == 0) {
        printf("Empty array.\n");
        return;
    }

    /* Nalezeni prvniho licheho cisla. */
    int i=0;
    while ( (i < arr.length) && (! IsOdd(arr.data[i])) ) ++i;
    int prev=arr.data[i];

    /* Pokracovani v testovani od dalsiho cisla. */
    ++i;

    /* Samotne testovani na neklesajici posloupnost. */
    for (; i < arr.length; ++i)
        if (IsOdd(arr.data[i])) {
            if (prev > arr.data[i]) {
                printf("BIG PROBLEM at index %i.\n",i);
                return ;
            }
            prev=arr.data[i];
        }

    printf("Odds form non-decreasing, OK.\n");
}



/* Funkce realizujici zadani ukolu.
   V teto funkci je potreba doprogramovat vhodny usek kodu! */
void SortArray(Array arr) {
    if (arr.length < 3) {
        /* Vstup prijemne kratky na provedeni zatrizeni. */
        if ( (arr.length > 1)
          && (IsOdd(arr.data[0])) && (IsOdd(arr.data[1]))
          && (arr.data[0] > arr.data[1]) ) {
            /* Prehozeni dvou lichych cisel. */
            int tmp=arr.data[0];
            arr.data[0]=arr.data[1];
            arr.data[1]=tmp;
        }

    } else {
        /* Vstup stale moc dlouhy, budeme rozdelovat a panovat. */
        /* Nove zhruba stejne dlouhe podseznamy pro samostatne setrizeni. */
        Array A,B;
        A.length=arr.length/2;
        B.length=arr.length - A.length;

        A.data=(int*)malloc(A.length * sizeof(int));
        B.data=(int*)malloc(B.length * sizeof(int));
        if ((A.data == NULL) || (B.data == NULL)) {
            printf("Cannot allocate memory.\n");
            if (A.data) free(A.data);
            if (B.data) free(B.data);
            /* Ukoncime tento kousek razeni proste bez razeni. */
            return;
        }

        /* Rozdeleni: rozkopirovani. */
        int d=0;



        for (; d < A.length; ++d) A.data[d]=arr.data[d];
        for (; d < arr.length; ++d) B.data[d-A.length]=arr.data[d];


        /* Panovani: rekurze. */
        SortArray(A);
        SortArray(B);

        /* Mergovani: kopirovani zpet. */

        /* ======================== */
        /* ZDE VHODNE DOPROGRAMOVAT */
        /* ======================== */

        int AIndex=0;
        int BIndex=0;
        int k=0;


        k=0;
        while(AIndex < A.length && BIndex < B.length){
            while(!IsOdd(A.data[AIndex]) && AIndex+1 < A.length){
                AIndex++;
            }
            while(!IsOdd(B.data[BIndex]) && BIndex+1 < B.length){
                BIndex++;
            }

            while(!IsOdd(arr.data[k]) && k+1 < arr.length ) k++;

            if(A.data[AIndex] < B.data[BIndex]){
                arr.data[k++]= A.data[AIndex++];
            }else{
                arr.data[k++]= B.data[BIndex++];
            }
        }

        while(AIndex < A.length && k<arr.length){
            while(!IsOdd(arr.data[k]) && k+1 < arr.length ) k++;

            if(IsOdd(A.data[AIndex])){
                arr.data[k]=A.data[AIndex];
                k++;
            }
            AIndex++;
        }

        while(BIndex < B.length && k<arr.length){
            while(!IsOdd(arr.data[k]) && k+1 < arr.length ) k++;
            if(IsOdd(B.data[BIndex])){
                arr.data[k]=B.data[BIndex];
                k++;
            }
            BIndex++;
        }

        /* Uklid pameti. */
        free(A.data);
        free(B.data);
    }
}


int main(void) {
    /* Delka vstupniho testovaciho pole. */
   const int inArrayLength = 30;

    /* Vytvoreni vstupniho pole. */
    Array inArray;
    inArray.length=inArrayLength;
    inArray.data = (int*)malloc(inArrayLength * sizeof(int));
    if (inArray.data == NULL) {
        printf("Cannot allocate memory.\n");
        return (-1);
    }

    /* Naplneni vstupniho pole. */
    int i=0;
    for (i=0; i < inArrayLength; ++i)
        inArray.data[inArrayLength-1-i]=i;
    inArray.data[0]=5;

    /* Tisk vstupu. */
    PrintAll(inArray);
    PrintOdd(inArray);
    PrintEven(inArray);
    printf("---------------------------------------\n");
    /* Zpracovani: razeni. */
    SortArray(inArray);

    /* Tisk vystupu. */
    PrintAll(inArray);
    PrintOdd(inArray);
    PrintEven(inArray);

    /* Jeste test serazeni lichych cisel. */
    AreOddNondecreasing(inArray);

    /* Uklid alokovane pameti. */
    free(inArray.data);

    return (0);
}
