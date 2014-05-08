/**
 * Tento priklad slouzi jako vzorovy priklad, co vas muze cekat na implementacnim testu.
 * Vasi ulohou je pochopit uz implementovanu datovu strukturu Dictionary a implementovat
 * nektere funkce, ktere s ni pracuji s pouzitim funkci jiz predepsanych. Je mozne si doprogramovat
 * i vlastni funkce, pokud vam ty jiz naimplementovane nevyhovuji.
 *
 * Slova jsou v slovniku reprezentovane tak, ze v kazdem uzlu sa nachazi jeden znak
 * a pole ukazatelu vsech moznych nasledujicich znakuv.
 *
 * V nasledujicom kodu implementujte funkci listWordsWithPrefix, ktera vrati ve strukture Words
 * vsechny slova v slovniku zacinajici na dany prefix. Davejte si pozor na to, ze znaky v jednotlivych
 * uzlech nejsou nutne usporadane.
 *
 * Pro praci s retezci muzete pouzivat funkce z knihovny string.h, obecne muzete pouzivat cokoliv ze standardni knihovny.
 *
 * Na vypracovani ulohy budete mit hodinu, muzete pouzivat vlastne materialy (zbirka, slajdy) pristup na internet nebude povoleny.
 * V ramci implementacniho testu naostro budete mit za ukol vyresit dva priklady. Toto je vzorove zadani jen jedneho prikladu.
 * Rieseni prikladu byste meli zvladnut za 15 - 20 minut.
 *
 * @author Karel Kubicek, 408351
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//maximalni pocet podstromu kazdeho uzlu
#define MAX_CHILDS 26
//maximalni pocet slov, ktere vase funkce listWordsWithPrefix vraci
#define MAX_WORDS 100

/**
 * Struktura Node popisuje uzel v slovniku. Node obsahuje
 * key popisujuci znak daneho uzlu v slovniku
 * pole ukazatelu na Node childs s potomky uzlu.
 * Pocet potomku je specifikovan v promenne childCount (obsah pole od pozice dane childCount neni nijak garantovan).
 * Pokud uzel neobsahuje potomky, childCount je 0. Zaroven uzol bez potomku urcuje koniec slova.
 */
typedef struct _node {
    char key;
    struct _node* childs[MAX_CHILDS];
    int childCount;
} Node;

/**
 * Struktura Dictionary popisuje datovu strukturu slovniku.
 * Dictionary obsahuje pole ukazatelu na Node, ktere
 * zacinaji na znak, ktery je jejich klicem.
 */
typedef struct {
    Node* childs[MAX_CHILDS];
    int childCount;
} Dictionary;

/**
  * Struktura Words je strukturou, do ktere nalezena slova ukladate.
  * Pro spravne reseni ulohy vubec nemusite do teto struktury koukat,
  * staci vam vedet, ze slovo do ni vlozite pomoci funkce wordsInsert.
  * Pokud byste pri reseni ulohy potrebovali pracovat s ulozenymi daty,
  * muzu vam poradit, ze vase reseni je prilis slozite (a vas algoritmus
  * je pravdepodobne neoptimalni). Pokud vsak na tomto reseni trvate,
  * pak si se strukturou klidne pracujte.
  */
typedef struct {
    char* words[MAX_WORDS];
    int wordsCount;
} Words;

/**
 * Funkce, ktere se vam pravdepodobne budou hodit
 */
//vraci podstrom obsahujici jen slova zacinajici na dany prefix
Node* dictSearch(Dictionary *dict, char *prefix);
//prida znak na konec nejakeho slova
char* addCharToWord(char* string, char character);
//prida slovo do seznamu slov, rada: pouzivejte strukturu Words jako write only,
//    pokud se vam k tomu nehodi, napiste si vlastni, ale zbytecne si praci komplikujete
void wordsInsert(Words* wordsArray, char* word);


/**
 * TODO: Vrati ve strukture Words slova nachadejici se ve slovniku a zacinajici na zadany prefix.
 * Za slovo sa povazuji ty postupnosti uzlu, ktere konci uzlem bez deti.
 * Priklad (s jednim Node, kteremu odpovida klic 'a'):
 *              a
 *            /   \
 *           h     u
 *         /   \    \
 *        a     o    t
 *               \    \
 *                j    o
 *                 \
 *                  t
 *                   \
 *                    e
 *
 * Slova s prefixom "ah" su ["aha", "ahojte"]
 *
 * V pripade ze slova s prefixem neexistuji, vrati se NULL.
 * V pripade ze cely prefix je jedno slovo, vrati se
 * struktura Words obsahujici prave toto slovo.
 * @param dict slovnik, ve kterem mate hledat
 * @param prefix vypisovanych slov
 * @return slova s danym prefixem ve strukture Words
 */
Words* listWordsWithPrefix(Dictionary* dict, char* prefix, Words* foundedWords) {
    //TODO do foundedWords pridavate pomoci wordsInsert(foundedWords, char* slovo)
    if(foundedWords==NULL){
        if(dictSearch(dict,prefix)==NULL){
            return NULL;
        }
        foundedWords = malloc(sizeof(Words));
        foundedWords->wordsCount = 0;
    }
    //TODO implementujte funkci


    Node* temp= NULL;
    while((temp=dictSearch(dict,prefix))!=NULL){
        if(temp->childCount==0){
            break;
        }
        if(temp->childCount==1){
            prefix= addCharToWord(prefix,temp->childs[0]->key);
            continue;
        }

        char * temp2= malloc(strlen(prefix+2));
        strcpy(temp2,prefix);
        for(int i=1;i<temp->childCount;i++){
            strcpy(prefix,temp2);
            prefix= addCharToWord(prefix,temp->childs[i]->key);
            foundedWords= listWordsWithPrefix(dict,prefix, foundedWords);
        }
        strcpy(prefix,temp2);
        prefix= addCharToWord(prefix,temp->childs[0]->key);
    }
    wordsInsert(foundedWords,prefix);

    return foundedWords;
}

/**
 * Vlozi slovo do slovniku
 * @param dict slovnik, do ktereho vkladame
 * @param word vkladani slovo
 */
void dictInsert(Dictionary* dict, char* word) {
    if(word == NULL || strlen(word) == 0) return;

    Node* chosen = NULL;
    for (int i = 0; i < dict->childCount; ++i) {
        if(dict->childs[i]->key == word[0]) {
            chosen = dict->childs[i];
            break;
        }
    }
    //key is not in dictionary
    if(chosen == NULL) {
        chosen = malloc(sizeof(Node));
        chosen->key = word[0];
        chosen->childCount = 0;
        dict->childs[dict->childCount] = chosen;
        dict->childCount++;
    }

    Node* tmp;
    for (unsigned int i = 1; i < strlen(word); ++i) {
        tmp = chosen;
        for (int j = 0; j < chosen->childCount; ++j) {
            if(chosen->childs[j]->key == word[i]) {
                chosen = chosen->childs[j];
                break;
            }
        }
        if(chosen == tmp) {
            chosen = malloc(sizeof(Node));
            chosen->key = word[i];
            chosen->childCount = 0;
            tmp->childs[tmp->childCount] = chosen;
            tmp->childCount++;
        }
    }
}

/**
 * Vyhlada podstrom so slovami zacinajucimi na prefix
 * @param dict slovnik, do ktereho vkladame
 * @param prefix hladanych slov
 * @return uzol s nasledujucimi slovami
 */
Node* dictSearch(Dictionary* dict, char* prefix) {
    if(prefix == NULL || strlen(prefix) == 0) return NULL;

    Node* chosen = NULL;
    for (int i = 0; i < dict->childCount; ++i) {
        if(dict->childs[i]->key == prefix[0]) {
            chosen = dict->childs[i];
            break;
        }
    }
    //prefix is not in dictionary
    if(chosen == NULL) {
        return NULL;
    }

    Node* tmp;
    for (unsigned int i = 1; i < strlen(prefix); ++i) {
        tmp = chosen;
        for (int j = 0; j < chosen->childCount; ++j) {
            if(chosen->childs[j]->key == prefix[i]) {
                chosen = chosen->childs[j];
                break;
            }
        }
        if(chosen == tmp) {
            return NULL;
        }
    }
    return chosen;
}

void wordsInsert(Words* wordsArray, char* word) {
    wordsArray->words[wordsArray->wordsCount] = word;
    wordsArray->wordsCount++;
}

void wordsPrint(Words* wordsArray) {
    if(wordsArray == NULL) {
        puts("null");
        return;
    }
    printf("[");
    for (int i = 0; i < wordsArray->wordsCount - 1; ++i) {
        printf("%s, ", wordsArray->words[i]);
    }
    printf("%s]\n", wordsArray->words[wordsArray->wordsCount - 1]);
}

char* addCharToWord(char* string, char character) {
    char* newWord = malloc(strlen(string)+2);
    strcpy(newWord, string);
    newWord[strlen(string)] = character;
    newWord[strlen(string) + 1] = '\0';
    return newWord;
}


int main(void)
{
    // nasledujuci kod sluzi pre otestovanie vasej funkcnosti
    // mozete si ho modifikovat podla vlastnych potrieb
    Dictionary dic;
    dic.childCount = 0;
    //naplnenie slovniku
    dictInsert(&dic, "algoritmus");
    dictInsert(&dic, "algoritmizacia");
    dictInsert(&dic, "algologia");
    dictInsert(&dic, "funkcionalny");
    dictInsert(&dic, "funkcionalizmus");
    dictInsert(&dic, "funktiv");
    dictInsert(&dic, "futurizmus");
    dictInsert(&dic, "fuzia");

    Words* words;
    //listWordsWithPrefix("a") vrati slova v slovniku zacinajuce na "a"
    puts("Test 1.:");
    puts("Pozadovany vystup (v libovolnem poradi):\t[algologia, algoritmizacia, algoritmus]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "a", NULL);
    wordsPrint(words);

    //listWordsWithPrefix("b") vrati slova v slovniku zacinajuce na "b"
    puts("\nTest 2.:");
    puts("Pozadovany vystup:\tnull");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "b", NULL);
    wordsPrint(words);

    //listWordsWithPrefix("funkc") vrati slova v slovniku zacinajuce na "funkc"
    puts("\nTest 3.:");
    puts("Pozadovany vystup (v libovolnem poradi):\t[funkcionalizmus, funkcionalny]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "funkc", NULL);
    wordsPrint(words);

    //listWordsWithPrefix("fuz") vrati slova v slovniku zacinajuce na "fuz"
    puts("\nTest 4.:");
    puts("Pozadovany vystup:\t[fuzia]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "fuz", NULL);
    wordsPrint(words);
    return 0;
}
