#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * Implementacni test IB002 - uloha 2. (8 bodu)
 *
 * Vyplnte nasledujice udaje:
 * Jmeno: 
 * UCO:
 * Skupina (v ktere jste zapsan):
 *
 * V tomto prikladu budete pracovat se stromem, reprezentujici hierarchii unixoveho
 * souboroveho systemu. Uzel stromu Directory reprezentuje jednu slozku. Klic uzlu obsahuje
 * retezec se jmenem slozky (tento klic musi byt unikatni mezi sourozenci), list nasledniku
 * a ukazatele na rodice (nebudeme ulohu komplikovat simulaci .. a .). Presnejsi popis
 * struktury Directory najdete dole.
 * Vasi ulohou bude v tomto zadani implementovat metodu cd. Ta bude simulovat
 * prikaz cd slouzici ke zmene pracovniho adresare. Pro zjednoduseni vzdy budeme
 * adresovat absolutne, tedy celou cestou a od korenoveho adresare.
 * Vstupem funkce bude  path, coz je retezec, ktery popisuje vetev stromu,
 * kde jednotlive klice jsou rozdeleny znakem "/". Prvni existujici slozka je
 * korenovy adresar, ktery ma jako klic prazdny retezec, po nem nasleduje "/".
 *
 * Priklad:
 * mejme tento strom slozek (klice budu nadale obalovat ""):
 *
 *                         "" (= Files.root)
 *                       /                  \
 *                    "home"               "tmp"
 *                      |                /       \
 *                 "Documents"        "tmp"     "tmp2"
 *                                      |       /    \
 *                                    "tmp"  "tmp"  "tmp2"
 *
 * V takovemto strome bychom meli nekolik cest:
 * cd("") by vratilo korenovy adresar
 * cd("/home") by vratilo uzel s klicem "home", ktery ma potomka s klicem "Documents"
 *
 * @author Karel Kubicek, Matus Madzin (C version)
 */

/*
 * Datova struktura zoznam na ukladanie potomkov
 */
struct List
{
  struct Directory *dir; //odkaz na potomka
  struct List *next; //odkaz na naslednika v zozname
};

/**
 * Struktura Directory predstavuje jeden adresar stromu.
 * Retezec directory_name je klicem, ktery unikatni v dane slozce (tedy nemohou 2
 * slozky se stejnym jmenem mit stejneho rodice). Klic muze byt prazdny retezec
 * jen v pripade korenoveho adresare.
 * parent je ukazatel na rodice, v pripade korenoveho adresare je null
 * List sub_directory je seznam ukazatelu na potomky. Pokud je prazdny,
 * je slozka listem stromu.
 */
struct Directory
{
  char directory_name [256];
  struct Directory *parent;
  struct List *sub_directory;
};

/*
 * Po zavolani path_split sa v tejto premennej ulozia retazce jednotlivych uzlov ako
 * boli zapisane v ceste.
 */
char path_names [256][256];

/*
 * Koren nasho stromu
 */
struct Directory* root;

/*
 * Tato funkcia rozdeli retazec na vstupe podla '/'. Ziskane retazce ulozi v globalnej
 * premennej path_names.
 * @param  retazec ktory chceme rozdelit
 */
void path_split(char* path);

/*
 * Vytvori strom
 */
void init();

/**
 * vypise pracovni adresar = prevedeni slozky na string
 * @param from
 * @param total_path stores result of the function
 */
void pwd(struct Directory* from, char **total_path)
{
  if(from == NULL)
  {
    *total_path=NULL;
    return ;
  }

  char path[256];
  int i = 0;

  while(from != NULL)
  {
    if(i == 0)
    {
      strcpy(*total_path, from->directory_name);
      strcat(*total_path, "/");
    }
    else
    {

      strcpy(path, *total_path);
      strcpy(*total_path, from->directory_name);
      strcat(*total_path, "/");
      strcat(*total_path, path);
    }

    from = from->parent;
    i++;
  }
}

/**
 * TODO: naimplementujte metodu cd
 * V pripade, ze vstupni retezec path je null, pak vracite null
 * V pripade, ze path je prazdny retezec vratite korenovy adresar (root)
 * Pokud zadana slozka neexistuje, vracite null
 * Tato metoda nebude volana s nesmyslnym parametrem typu nesmysl/home/user,
 * ale vzdy bude volana s / na zacatku
 *
 * Mozna by se vam mohla hodit metoda path_split, ktera rozdeli retezec
 * podle zadaneho regularniho vyrazu
 * priklad pouziti:
 * path_split("/a/b/c/d") ulozi nasledujuce hodnoty do premennej
 * path_name ["a", "b", "c", "d"]
 * Na porovnanie dvoch retazcov pouzite funkciu strcmp(r1, r2) vrati 0 ak su retazce rovnake
 * @param path
 * @return
 */

struct Directory* cd(char* path)
{
    if(path==NULL){
        return NULL;
    }

    //root
    if(strcmp(path,"")==0){
        return root;
    }
    path_split(path);
    int i=0;
    struct Directory* current= NULL;
    current= root;
    struct List* currentN= current->sub_directory;
    while(strcmp(path_names[i],"")!=0){
        int founded=0;
        currentN=current->sub_directory;
        if(strcmp(currentN->dir->directory_name,path_names[i])==0){
            current= currentN->dir;
            founded=1;
        }
        while(currentN->next!=NULL && !founded){
            currentN=currentN->next;
            if(strcmp(currentN->dir->directory_name,path_names[i])==0){
                current= currentN->dir;
                founded=1;
            }
        }

        if(!founded){
            return NULL;
        }
        i++;
    }
    return current;


}

int main()
{
  init();
  /* svuj kod mozete testovat tu: */

  /* nasledujuci kod nemente*/
  printf("Test 1.:");
  if(cd(NULL) == NULL)
    printf("OK\n");
  else
    printf("Chyba, co treba osetrovat vstup?\n");

  printf("Test 2.:");
  if(cd("") == root)
    printf("OK\n");
  else
    printf("Chyba, prazdny retezec odpovida korenovemu adresari\n");

  printf("Test 3.:");
  struct Directory* tmp = cd("/home");
  char *home = (char*) malloc(256*sizeof(char));
  pwd(tmp, &home);

  if(strcmp("/home/", home) == 0)
    printf("OK\n");
  else
    printf("Chyba, vratili jste cestu %s, ale meli jste vratit /home/\n", home);

  printf("Test 4.:");
  tmp = cd("/home/");
  home = (char*) malloc(256*sizeof(char));
  pwd(tmp, &home);

  if(strcmp("/home/", home) == 0)
    printf("OK\n");
  else
    printf("Chyba, vratili jste cestu %s, ale meli jste vratit /home/\n", home);

  printf("Test 5.:");
  tmp = cd("/tmp/Documents/tmp/");
  home = (char*) malloc(256*sizeof(char));
  pwd(tmp, &home);

  if(tmp == NULL)
    printf("OK\n");
  else
    printf("Chyba, vratili jste cestu %s, ale meli jste vratit NULL\n", home);

  printf("Test 6.:");
  tmp = cd("/tmp/tmp/tmp/");
  home = (char*) malloc(256*sizeof(char));
  pwd(tmp, &home);

  if(strcmp("/tmp/tmp/tmp/", home) == 0)
    printf("OK\n");
  else
    printf("Chyba, vratili jste cestu %s, ale meli jste vratit NULL\n", home);

  return 0;
}

void path_split(char* path)
{
  char tmp[256];
  strcpy(tmp, path);

  char *saveptr;
  int j = 0;

  char *name = strtok(tmp, "/");

  while(name != NULL)
  {
    strcpy(path_names[j], name);
    name = strtok(NULL, "/");
    j++;
  }

  strcpy(path_names[j], "");
}

void insert(struct Directory *parent, struct Directory* new_child)
{
  if(parent == NULL)
    return;

  struct List *tmp = parent->sub_directory;

  struct List *new_list = (struct List*) malloc (sizeof(struct List));
  new_list->dir = new_child;
  new_list->next = tmp;

  parent->sub_directory = new_list;
  new_child->parent = parent;
}

void init()
{
  struct Directory *tmp = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp->directory_name, "");
  tmp->sub_directory = NULL;
  tmp->parent = NULL;
  root = tmp;

  tmp = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp->directory_name, "tmp");
  tmp->sub_directory = NULL;
  tmp->parent = NULL;
  insert(root, tmp);

  struct Directory *home = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(home->directory_name, "home");
  home->sub_directory = NULL;
  home->parent = NULL;
  insert(root, home);

  struct Directory *doc = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(doc->directory_name, "Documents");
  doc->sub_directory = NULL;
  doc->parent = NULL;
  insert(home, doc);

  struct Directory *tmp2 = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp2->directory_name, "tmp2");
  tmp2->sub_directory = NULL;
  tmp2->parent = NULL;
  insert(tmp, tmp2);

  struct Directory *tmp_II = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp_II->directory_name, "tmp");
  tmp_II->sub_directory = NULL;
  tmp_II->parent = NULL;
  insert(tmp, tmp_II);

  struct Directory *tmp_III = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp_III->directory_name, "tmp");
  tmp_III->sub_directory = NULL;
  tmp_III->parent = NULL;
  insert(tmp_II, tmp_III);

  struct Directory *tmp2_II = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp2_II->directory_name, "tmp2");
  tmp2_II->sub_directory = NULL;
  tmp2_II->parent = NULL;
  insert(tmp2, tmp2_II);

  tmp = (struct Directory*) malloc(sizeof(struct Directory));
  strcpy(tmp->directory_name, "tmp");
  tmp->sub_directory = NULL;
  tmp->parent = NULL;
  insert(tmp2, tmp);
}

void print_tree(struct Directory* tmp)
{
  if(tmp != NULL)
  {
    printf("node %s:\n", tmp->directory_name);

    struct List *list = tmp->sub_directory;

    while(list != NULL)
    {
      printf("\t%s\n", list->dir->directory_name);
      list = list->next;
    }

    list = tmp->sub_directory;

    while(list != NULL)
    {
      print_tree(list->dir);
      list = list->next;
    }
  }
}
