#include "reservation.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int readfile(char txtfile[]) // read the txt file and put it in the linked list
{
  FILE *fh = fopen(txtfile, "r");

  if (fh == NULL)
    return 0;

  int localnum = 0;
  char localstr[20];
  while (fscanf(fh, "%s %d", localstr, &localnum) != EOF) // while it hasn't reached the end of the line (which holds one name and num)
  { 
    insert(localstr, localnum);
  }
  fclose(fh);

  return 0;
}


int savetofile(char txtfile[]) // save whatever changes you made in the linked list
{
  FILE *fh = fopen(txtfile, "w");
  NODE *transfer;

    transfer = head;
    while (transfer != NULL)
    {
      fprintf(fh, "%s %d\n", transfer->name, transfer->groupsize); // copy the name and number from the linked lists to the txt file fh, and then make a new line after each set
      transfer = transfer->next;
    }

  fclose(fh); // done adding to it, so close it
  return 0;
}

void *autosave(void *arg)
{
  char *binfile = (char *)arg;
  NODE *save;
  
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  
  while (1) // endless loop
  {
    sleep(15);
    pthread_mutex_lock (&mutex);
    FILE *fb = fopen(binfile, "wb");

    save = head;

    while (save != NULL) // while list not empty/not reached end
    {
      fwrite(save, sizeof(NODE), 1, fb);

      save = save->next; // increment pointer to point to next entry in list
    }
    fclose(fb);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int readfrombin(char binfile[])
{
  pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
  
  NODE *temp = (NODE *)malloc(sizeof(NODE));
  
  if (temp == NULL)
  {
   printf("Could not allocate memory.\n");
   return 0;
  }

  pthread_mutex_lock(&mutex2);
  FILE *fb = fopen(binfile, "rb");
  
  if (fb == NULL)
  { 
   printf("Error opening file.\n");
   return 0;
  }

  while ((fread(temp, sizeof(NODE), 1, fb)) == 1) // while there's something to read
  {
    printf("%s, %d\n", temp->name, temp->groupsize);
  }  

  fclose(fb);
  pthread_mutex_unlock(&mutex2);
  free(temp);
  return 1;
}
