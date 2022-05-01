#ifndef STUDENTLIST_H_
#define STUDENTLIST_H_

//οι δομή και οι συναρτήσεις για την λίστα του hashtable
typedef struct listNode
{
    int studentID;
    char * name, * lastname;
    int zip, year;
    float gpa; 
    struct listNode * next;
}listNode;

listNode* insertNode(listNode ** head, int ID, char* name,char *lastname,float gpa,int zip,int year); 
int deleteNode(listNode** head, int key);
void printNode(listNode head,int key);
void deleteList(listNode **head) ;
listNode* findNode(listNode *head,int key);

#endif