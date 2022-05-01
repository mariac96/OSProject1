#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "yearnode.h"

//οι συναρτήσεις που χρησιμοποιούνται για τις εντολές
int readfiles(int argc, char *argv[],yearNode **head);
int insertAll(yearNode**head,int size);
void deleteID(yearNode**head,int size);
void exitAll(yearNode**head,int size);
void lookID(int size);
void numberinYear(yearNode*head);
void  topinYear(yearNode*head);
void averageYear(yearNode*head);
void minimumYear(yearNode*head);
void countAll(yearNode*head);
#endif