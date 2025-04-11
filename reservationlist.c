#include "lab10.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

// function definitions
int check_duplicate(char tempname[])
{
  NODE *tempdupe = (NODE *)malloc(sizeof(NODE));
  tempdupe = head;

  while (tempdupe != NULL)
  {
    if (strcmp(tempname, tempdupe->name) == 0) // comparing inputted name (from insert function) to pointer pointing to name of first struct, then incrementing pointer to compare inputted name to pointer of second struct, etc. till counter
    {
      return 1; // duplicate found
    }
    tempdupe = tempdupe->next;
  }
  return 0; // no duplicate found
}

void insert(char *localname, int localnum)
{

  NODE *node = (NODE *)malloc(sizeof(NODE)); // allocating memory for new node
  NODE *compnode;
  NODE *follow;

  if (node == NULL)
  {
    printf("Error\n");
  }

    strcpy(node->name, localname);
    node->groupsize = localnum;

    compnode = follow = head;

    while (compnode != NULL) // have to insert to the left of compnode, compnode should be bigger than insert node
    {
      if (node->groupsize < compnode->groupsize)
      {
        break;
      }
      follow = compnode;
      compnode = compnode->next;
    }

    if (compnode == head) // first item in list
    {
      node->next = head;
      head = node;
    }

    else
    {
      if (compnode == NULL) // last item in list
      {
        node->next = NULL;
        follow->next = node;
      }

      else // middle of list
      {
        node->next = compnode;
        follow->next = node;
      }

      // strcpy(node->name, localname);
      // node->groupsize = localnum;
    }

  printf("\nYour reservation has been added!\n\n");

}

int shows()
{
  NODE *tempshow = (NODE *)malloc(sizeof(NODE));

  if (tempshow == NULL)
  {
    printf ("Error\n");
  }

  printf("\nYou chose to display the reservation schedule.\n");

  tempshow = head;
  while (tempshow != NULL)
  {
    printf ("%s, %d\n", tempshow->name, tempshow->groupsize);
    tempshow = tempshow->next;
  }
}

int search()
{
  NODE *tempsearch = (NODE *)malloc(sizeof(NODE));
  tempsearch = head;

  int opening = 0;
  int openbool = 0;

  printf("\nYou chose to see what reservations match the opening just created.\n");

  if (head == NULL)
  {
    printf("\nThere are no reservations in the schedule.\n");
    return 0;
  }

  printf("\nWhat is the size of the opening that has been created?\n");
  scanf("%d", &opening);

  while (tempsearch != NULL)
  {
    if (tempsearch->groupsize == opening)
    {
      printf("\n%s", tempsearch->name);
      printf("'s reservation size matches this opening.\n");
      openbool = 1;
      return 1;
    }

    tempsearch = tempsearch->next;
  }

  if (openbool == 0)
  {
    printf("\nNo current reservations are made for the same size as the opening made.\n");
    return 0;
  }

}

void removes()
{
  NODE *rem1, *rem2 = (NODE *)malloc(sizeof(NODE));

  int newnum;
  int i = 0, j = 0, k = 0;
  int removed = 0;

  if (head == NULL)
  {
    printf("\nThere are no reservations in the schedule.\n");
  }

  printf("\nYou chose to remove a group from the reservation schedule based on a recent opening\n");

  printf("\nWhat is the size of the new opening that has been made\n");
  scanf("%d", &newnum);

  rem1 = rem2 = head;

  while (rem1 != NULL) // compares rem1 node from head to end, to see if its groupsize matches the opening
  {
    if (rem1->groupsize <= newnum)
    {
      break;
    }

    rem2 = rem1; // if no match is found, rem2 takes the place of old rem1, and rem1 moves to the next node to be compared to the opening found
    rem1 = rem1->next; 
  }

  if (rem1 == NULL) // if rem1 is NULL, that means that rem1 iterated through the whole linked list and no matching groupsize to the opening was found, so no reservations will be removed
  {
    printf("\nNo reservations with that opening size were found.\n");
  }

  if (rem1 == head) // if the desired node to be removed (rem1) is at the start/head, make sure the new head pointer points to the next node in line, since the original head is going to be deleted and list needs new head
  {
  head = head->next;
  removed = 1;
  }

  else
  {
    if (rem1->next == NULL) // if rem1 is at the very last node and being deleted, the list should hold no other nodes after it
    {
      rem2->next = NULL; // so set rem2 (previous node) to null because the last one is being deleted, to kick rem1 out of list
    }
    else // if rem1 is not outside the list, not the last and not the first meaning it is in the middle, make the pointer of the node before it (rem2) to point to the node after rem1, so rem1 is just excluded from the linked list
    {
      rem2->next = rem1->next;
      removed = 1;
    }
  }

  if (rem1 != NULL) 
  {
  free(rem1);
  rem1 = NULL; // releases the data in rem1, the reservation being deleted, so it doesn't use up unnecessary memory
  }
  if (removed == 1)
  {
    printf("\nThis is the updated reservation schedule:\n");
    shows();
  }

  else
  {
    printf("\nNo reservations with that opening size were found.\n");
  }

}

void listbackwards(NODE *backw)
{
//  NODE *tbackwards = (NODE *)malloc(sizeof(NODE));

  if (backw == NULL) // nothing in list
  {
   // printf("\nThe list is empty\n");
    return;
  }

  listbackwards(backw->next);
  printf("%s, %d\n", backw->name, backw->groupsize);
}

void namebackwards(NODE *backname)
{
  if (backname == NULL)
   return;

  char tempchar;
  char tempstr[20];
  strcpy(tempstr, backname->name);
  int len = strlen(tempstr);
  int i, j;

  for (i = 0, j = len - 1; i < j; i++, j--)
  {
    tempchar = tempstr[i];
    tempstr[i] = tempstr[j];
    tempstr[j] = tempchar;
  }

  printf("%s\n", tempstr);

  namebackwards(backname->next);
}

void deleteall(NODE *p)
{
  if (p == NULL)
    printf("Nothing to delete\n");
  return;

  deleteall(p->next);
  free(p);
}
