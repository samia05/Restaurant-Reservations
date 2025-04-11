#ifndef LAB10_INCLUDED
#define LAB10_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//#define NODE struct note

// declare global variables + struct info

typedef struct node 
{
  char name[20];
  int groupsize;
  struct node *next;
} NODE;

extern NODE *head;

// pthread_t thr;

//extern int thr;

// pthread_mutex_t mutex;
// pthread_mutex_t mutex2;

extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex2;

// function declarations
int readfile(char txtfile[]);
int savetofile(char txtfile[]);
void insert(char *, int);
int shows();
int search();
int check_duplicate();
void removes();
void listbackwards(NODE *);
void namebackwards(NODE *);
void deleteall(NODE *);
void *autosave(void *arg);
int readfrombin(char binfile[]);
#endif 
