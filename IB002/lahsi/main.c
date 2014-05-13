
#include <stdio.h>
#include <stdlib.h>

/**
 * Implementacni test IB002 - uloha 2. (12 bodu)
 *
 * Vyplnte nasledujice udaje:
 * Jmeno:
 * UCO: 
 * Skupina (ve ktere jste zapsan):
 *
 * Vasi ulohou v tomto prikladu je obratit poradi prvku v
 * jednostranne zretezenem linearnim seznamu
 * .
 * @author Karel Kubicek, Matus Madzin (C version)
 */
struct Element
{
  int value;
  struct Element *next;
};

/**
 * vlozi prvok na koniec zoznamu
 * @param beginning  zaciatok zoznamu
 * @param value  vkladana hodnota
 * @return  zaciatok zoznamu
 */
struct Element* insert(struct Element *beginning, int value);

/**
 * zmaze prvy prvok v zozname
 * @param beginning  zaciatok zoznamu
 * @return  novy zaciatok zoznamu
 */
struct Element* delete(struct Element *beginning);

/**
 * zmaze vsetky prvky v zozname
 * @param beginning  zaciatok zoznamu
 */
void delete_all(struct Element *beginning);

/**
 * vypisy slouzici ke kontrole
 * @param beginning  pocatek vypisu
 * @return
 */
void print_list(struct Element *beginning);

/**
 * TODO: naimplementujte metodu revert
 * metoda ma za ukol obratit poradi prvku v seznamu
 * @param beginning  pocatek seznamu
 * @return  pocatek obraceneho seznamu
 */
struct Element* revert(struct Element *beginning);

//TODO
struct Element* revert(struct Element *beginning)
{
    if(beginning==NULL){
        return NULL;
    }
    struct Element* newBeginning= NULL;
    struct Element* current= NULL;
    current= beginning;
    while(current->next!=NULL){
        current= current->next;
    }

    newBeginning= current;

    struct Element* currentN=NULL;
    currentN= newBeginning;
    while(currentN!=beginning){
        current=beginning;
        while(current->next!=currentN){
            current= current->next;
        }
        currentN->next= current;
        currentN=currentN->next;
    }
    beginning->next=NULL;
    return newBeginning;

}

int main()
{
  struct Element* beginning = NULL;

  //Test 1
  printf("Test 1.:");
  beginning = revert(beginning);

  if(beginning == NULL)
    printf("OK\n");
  else
  {
    printf("Chyba pri praci s prazdnym listem");
    return 1;
  }

  //Test 2
  printf("Test 2.:");

  beginning = NULL;
  beginning = insert(beginning, 3);

  beginning = revert(beginning);

  if(beginning->value == 3)
    printf("OK\n");
  else
  {
    printf("Chyba pri praci s listem s jednim prvkem, modifikujete jej");
    return 2;
  }
  delete_all(beginning);

  //Testy 3 - 10
  for (int i = 3; i <= 10; i++)
  {
    beginning = NULL;
    for (int j = 1; j < i; j++)
      beginning = insert(beginning, j);

    printf("Test %d.:", i);

    beginning = revert(beginning);

    int j = i-1;
    struct Element *tmp = beginning;

    while(tmp != NULL)
    {
      if(tmp->value != j)
      {
        printf("Chyba, spatne poradi: v liste %d, ocakavane %d\n", tmp->value, j);
        return i;
      }

      tmp = tmp->next;
      j--;
    }
    printf("OK\n");
    delete_all(beginning);
  }

  return 0;
}

struct Element* insert(struct Element *beginning, int value)
{
  struct Element* new = (struct Element*) malloc(sizeof(struct Element));
  new->value = value;
  new->next = NULL;

  if(beginning == NULL)
    return new;

  struct Element* tmp = beginning;

  while(tmp->next != NULL)
    tmp = tmp->next;

  tmp->next=new;

  return beginning;
}

struct Element* delete(struct Element *beginning)
{
  struct Element* del = beginning;
  beginning = beginning->next;
  free(del);
  return beginning;
}

void delete_all(struct Element *beginning)
{
  while(beginning != NULL)
    beginning = delete(beginning);
}

void print_list(struct Element *beginning)
{
  printf("List: ");

  while(beginning != NULL)
  {
    printf("%d ", beginning->value);
    beginning = beginning->next;
  }

  printf("\n");
}
