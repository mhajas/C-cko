/*
 * Implementacny test IB002 - uloha 2. (8 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina(v ktorej ste zapisany):
 */

// Zadani:
//
// Naimplementujte metodu 'Generate', ktora vygeneruje maticu sousednosti grafu splnajuceho podmienky:
//     - obsahuje presne dany pocet vrcholov N (N je zadane ako parameter konstruktora Graph, N>=6)
//     - graf je neorientovany
//     - graf neobsahuje slucky
//     - graf neobsahuje cykly
//     - graf obsahuje hrany 3 roznych dlzok: 4, 5, 6
//     - z kazdeho vrcholu grafu vychadzaju maximalne 3 hrany (stupen kazdeho vrcholu je mensi nez 4)
//     - graf obsahuje najmenej N/2 hran (zaokruhlene nadol)
//     Pocet uzlov grafu bude splnat N >= 6 (nemusite kontrolovat)
//     Neexistujuce hrany v matici reprezentujte hodnotou -1.
//     Snazte sa o co najefektivnejsiu implementaciu.
// [8 bodov]

#include <stdio.h>
#include <stdlib.h>
#define COORS(x,y,size) ((x)*(size)+(y))

int pocetVrcholov = 6;

void Generate(int *matrix, int pocetVrcholov);
int Validate(int *matrix, int pocetVrcholov);

void printMatrix(int* matrix,int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%2d",matrix[COORS(i,j,N)]);
        }
        printf("\n");
    }
    printf("----------------\n");
}

int main()
{
    srand(time(NULL));
    int points=0;
    int from=0;
    for(int p=0;p<500;p++){

        int i,j;
        int pocetVrcholov = 7;
        int matrix1[pocetVrcholov*pocetVrcholov];
        for( i = 0; i < pocetVrcholov; i++) {
            for( j = 0; j < pocetVrcholov; j++) {
                matrix1[COORS(i,j,pocetVrcholov)] = -1;
            }
        }
        Generate(matrix1, pocetVrcholov);
        from++;
        int result = Validate(matrix1, pocetVrcholov);
        if(result){
            points++;
        }
        printf("Validacia: %d\n", result); //malo by byt 1

        pocetVrcholov = 15;
        int matrix2[pocetVrcholov*pocetVrcholov];
        for( i = 0; i < pocetVrcholov; i++) {
            for( j = 0; j < pocetVrcholov; j++) {
                matrix2[COORS(i,j,pocetVrcholov)] = -1;
            }
        }
        Generate(matrix2, pocetVrcholov);
        result = Validate(matrix2, pocetVrcholov);
        if(result){
            points++;
        }
        from++;
        printf("Validacia: %d\n", result); //malo by byt 1
    }
    printf("Vysledok:%d/%d\n",points,from);
    return 0;
}



void Generate(int *matrix, int pocetVrcholov) {
    int added= 0;
    int i,j;
    int riadok,stlpec;
    int value;
    for(int k=0;k<pocetVrcholov/2+1;k++){
        added= 0;
        while(!added){
            printMatrix(matrix,pocetVrcholov);
            i=rand() % pocetVrcholov;
            j=rand() % pocetVrcholov;

            if(matrix[COORS(i,j,pocetVrcholov)]!=-1){
                continue;
            }
            if(i==j){
                continue;
            }
            riadok=0;
            stlpec=0;
            for(int z=0;z<pocetVrcholov;z++){
                if(matrix[COORS(i,z,pocetVrcholov)]!=-1){
                    riadok++;
                }
                if(matrix[COORS(z,j,pocetVrcholov)]!=-1){
                    stlpec++;
                }
            }

            if(riadok<3 && stlpec<3){
                value= rand() % 3 + 4;
                matrix[COORS(i,j,pocetVrcholov)]= value;
                matrix[COORS(j,i,pocetVrcholov)]= value;
                added=1;
            }
        }
    }
}

int Validate(int *matrix, int pocetVrcholov)
{
    int numberOfEdges = 0;
    int i, j ;
    for( i = 0; i < pocetVrcholov; i++) {
        for( j = 0; j < pocetVrcholov; j++) {
            if (matrix[COORS(i,j,pocetVrcholov)] != matrix[COORS(j,i,pocetVrcholov)]) {
                printf("CHYBA: graf je orientovany!");
                return 0;
            }

            if (matrix[COORS(i,j,pocetVrcholov)] != -1)
                    {
                        if (i <= j)
                        {
                            numberOfEdges++;
                        }

                        if (matrix[COORS(i,j,pocetVrcholov)] < 4 || matrix[COORS(i,j,pocetVrcholov)] > 6)
                        {
                            printf("CHYBA: nespravna vaha hrany %d %d ", i, j );
                            return 0;
                        }
                    }
        }
    }

    if ( numberOfEdges < (pocetVrcholov / 2) )
            {
                printf("CHYBA: nizky pocet hran! %d %d",numberOfEdges,(pocetVrcholov/2));
                return 0;
            }

    for ( i = 0; i < pocetVrcholov; i++)
            {
                if (matrix[COORS(i,i,pocetVrcholov)] != -1)
                {
                    printf("CHYBA: graf obsahuje smycku %d", i);
                    return 0;
                }
            }
    for ( i = 0; i < pocetVrcholov; i++)
            {
                int degree = 0;
                for ( j = 0; j < pocetVrcholov; j++)
                {
                    if (matrix[COORS(i,j,pocetVrcholov)] != -1)
                    {
                        degree++;
                    }
                }
                if (degree > 3)
                {
                    printf("CHYBA: vrchol ma stupen viac, nez 3");
                    return 0;
                }
            }

    return 1;
}
