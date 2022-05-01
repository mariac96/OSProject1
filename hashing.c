#include <string.h>
#include <stdio.h>
#include "studentlist.h"
#include <stdlib.h>
#include "hashing.h"

listNode ** hashtable;

//δημιουργία hash table για size αριθμό εγγραφών
int initialize(int size){
    size = size>>2;
    int i;
    
    hashtable = malloc(sizeof(listNode*)*size);
    if(hashtable==NULL){
        fprintf(stderr, "Error - unable to allocate required memory for the hash table\n");
        return -1;
    }
    
   for ( i = 0; i < size; i++)
    {
        hashtable[i]=NULL;
       
    }
    
    return size;
    
}

int hashfunction (int key,int size){
    int k;
    size = size>>2;
    k=  key%size;
    return k;
}

//εισαγωγή κόμβου listNode 
listNode* insert(int size,int ID, char* name,char *lastname,float gpa,int zip,int year,int *count)
{   
    listNode *temp=NULL;
    int k;
    k =hashfunction(ID,size);
    
    //αν δεν υπάρχει ήδη φοιτητής με αυτό το ID
  
    if(findNode(hashtable[k],ID)==NULL){
        if((temp=insertNode(&hashtable[k], ID,  name,lastname, gpa, zip, year))==NULL)
        {
            fprintf(stderr, "Error - unable to insert node\n");
            return NULL;
        }
        return temp;
    }
    else
    {
        (*count) ++; //αν υπάρχει ήδη φοιτητής με αυτό το id
       
    }
    
    
    return temp;
}


//διαγραφή listNode με studentID ID 
void deleteHashNode(int ID,int size){
    int k;
    k = hashfunction(ID,size);
    deleteNode(&hashtable[k],ID);
}

//διαγραφή hashtable
void deleteHashtable(int size){
    size = size>>2;
    int i ;
    for ( i = 0; i < size; i++)
    {
        deleteList(&hashtable[i]);
    }
    free(hashtable);
}


//βρίσκει κόμβο με ID το key
listNode* findHashNode(int size,int key){
    int k;
    k = hashfunction(key,size);
    listNode* temp;
    temp = findNode(hashtable[k],key);
    return temp;
}