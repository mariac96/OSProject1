#ifndef YEARNODE_H_
#define YEARNODE_H_

#include "studentlist.h"
//η δομή και οι συναρτ΄ήσεις για το inverted index
typedef struct studentNode{
 listNode *info;
 struct studentNode *next;
} studentNode;

typedef struct yearNode{
 int year;
 studentNode *students;
 struct yearNode *nextYear;
} yearNode;


int insertYear(yearNode **head,listNode *student);
yearNode* findYear(yearNode* head,int year);
int insertStudentNode(studentNode **head,listNode* student);
int deleteStudentNode(yearNode** head, int key,int ID);
void deleteStudentNodeList(studentNode **head,yearNode *year);
int deleteYearNode(yearNode** head, int key);
void deleteYear(yearNode **year) ;
int countStudents(yearNode *temp);
int findTopYear(yearNode *temp,int n);
float findAverage(yearNode *temp);
void findMinYear(yearNode *temp);
#endif