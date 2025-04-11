// lab 10
// winter 2023
// name: Samia Ahmer

#include "lab10.h"

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

NODE *head = NULL;
pthread_t thr;
pthread_mutex_t mutex, mutex2;

int main (int argc, char *argv[])
{
  if (argc < 3)
    {
    printf("The name of the file is missing\n");
    return 1;
    }

  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
   printf("Error with mutex.\n");
   return 0;
  }

  if (pthread_mutex_init(&mutex2, NULL) != 0)
  {
   printf("Error with mutex2.\n");
   return 0;
  } 

//  int pthread_mutex_init (pthread_mutex_t *restrict mutex,
//  const pthread_mutexattr_t *restrict attr); // creates mutex

//  int pthread_mutex_init (pthread_mutex_t *restrict mutex2,
//  const pthread_mutexattr_t *restrict attr); // creates mutex2  
  
  readfile(argv[1]);
  char *binfile = argv[2];
  if (pthread_create(&thr, NULL, autosave, (void *)binfile) != 0) // create not successful
  {
    printf("\nError creating thread.\n");
    return 1;
  }

  int option;

  while (1)
  {
    printf ("\n1 to make a reservation\n2 to see the reservation schedule\n3 to see what reservations match the opening just made\n4 to remove a reservation from the schedule based on a recent opening\n5 to show the reservation list backwards\n6 to show all names backwards\n7 to read from the binary autosaved file\n0 to save and quit\nEnter:");

    if (scanf ("%d", &option) != 1)
    {
      printf ("Error\n");
      return 0;
    }

    switch (option)
    {
      case 1:
      {
        char localname[20];
        int localnum = 0; 

        printf("\nYou chose to make a reservation.\n");

        printf("\nWhat is the name for your reservation party.\n");
        scanf("%s", localname);

        if (check_duplicate(localname) == 1) // duplicates are found
        {
          printf("\nThis name has already been added to the reservation booking, enter another name.\n");
        }

        printf("\nHow many people are in your reservation party?\n");
        scanf("%d", &localnum);

        insert(localname, localnum);
        break;
      }

      case 2:
      {
        shows();
        break;
      }

      case 3:
      {
        search();
        break;
      }

      case 4:
      {
       removes();
       break;
      }

      case 5:
      {
  printf("\nYou chose to display the schedule backwards.\n");
        listbackwards(head);
  break;
      }

      case 6:
      {
  printf("\nYou chose to display all reservation names backwards.\n");
        namebackwards(head);
        break;
      }
      
      case 7:
      {
      readfrombin(argv[2]);
      break;
      } 

      case 0:
      {
        savetofile(argv[1]);
        deleteall(head);
        return 0;
      }

      default:
        printf("\nPlease enter a valid number\n");
    } // switch
  } // while
} // main
