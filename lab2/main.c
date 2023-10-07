#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book
{
  char *title;
  double price;
  int pages;
  char *language;
  int weight;
  int publicationYear;
};

void printBook(struct Book book)
{
  printf("\n\e[1mНазва\e[m: %s\n", book.title);
  printf("\e[1mЦіна\e[m: £ %.2f\n", book.price);
  printf("\e[1mК-сть сторінок\e[m: %d\n", book.pages);
  printf("\e[1mМова\e[m: %s\n", book.language);
  printf("\e[1mВага\e[m: %d г\n", book.weight);
  printf("\e[1mРік публікації\e[m: %d\n", book.publicationYear);
}

struct Book Book(char *title, double price, int pages, int weight, int publicationYear)
{
  struct Book book;
  book.title = title;
  book.price = price;
  book.language = "англійська";
  book.pages = pages;
  book.weight = weight;
  book.publicationYear = publicationYear;
  return book;
}

struct Node
{
  struct Book data;
  struct Node *next;
};

struct Node *firstNode = NULL;

void insert(struct Book data)
{
  struct Node *next = (struct Node *)malloc(sizeof(struct Node));
  next->data = data;

  if (firstNode == NULL)
  {
    next->next = firstNode;
    firstNode = next;
    return;
  }

  struct Node *sibling = firstNode;

  while (sibling->next != NULL)
  {
    sibling = sibling->next;
  }

  sibling->next = next;
}

void printBooksList()
{
  struct Node *p = firstNode;

  while (p != NULL)
  {
    printBook(p->data);
    p = p->next;
  }
}

int main(void)
{
  // Ціна/вага/кількість сторінок взята із @see (waterstones.com), рік публікації
  // з @see (api.potterdb.com/v1/books), оскільки у онлайн-магазині усі книги були
  // опубліковані у одному й тому ж самому році ¯\_(ツ)_/¯
  insert(Book("Harry Potter and the Philosopher's Stone", 7.99, 352, 290, 1997));
  insert(Book("Harry Potter and the Chamber of Secrets", 7.99, 384, 314, 1998));
  insert(Book("Harry Potter and the Prisoner of Azkaban", 7.99, 480, 389, 1999));
  insert(Book("Harry Potter and the Goblet of Fire", 8.99, 640, 510, 2000));
  insert(Book("Harry Potter and the Order of the Phoenix", 8.99, 816, 1098, 2003));
  insert(Book("Harry Potter and the Half-Blood Prince", 8.99, 560, 452, 2005));
  insert(Book("Harry Potter and the Deathly Hallows", 8.99, 640, 510, 2007));

  printBooksList();

  return 1;
};
