#include <string.h>
#include <stdio.h>
#include "studentlist.h"
#include <stdlib.h>

//εισαγωγή του καινο΄υριου κόμβου στη λίστα με κεφαλή head
listNode* insertNode(listNode ** head, int ID, char* name,char *lastname,float gpa,int zip,int year) 
{ 
    int size;
    listNode* newNode = (listNode*) malloc(sizeof( listNode)); 
   
    
   if( newNode == NULL ) {
      fprintf(stderr, "Error - unable to allocate required memory for list node\n");
      return NULL;
    }else{
        
        newNode->studentID = ID;
        newNode->gpa = gpa;
        newNode->zip = zip;
        newNode->year = year;
        
        //εισαγωγή ονόματος
        size = strlen(name) + 1;
        newNode->name =  (char *) malloc( size * sizeof(char) );
       
	
        if( newNode->name == NULL ) {
            fprintf(stderr, "Error - unable to allocate required memory for name\n");;
        } else {
            strcpy( newNode->name,name );
        }
        //εισαγωγή επωνύμου
        size = strlen(lastname) + 1;
        newNode->lastname = (char*) malloc( size * sizeof(char) );
        
        if( newNode->lastname == NULL ) {
            fprintf(stderr, "Error - unable to allocate required memory for last name\n");
        } else {
            strcpy( newNode->lastname,lastname );
        }
        
        if(*head == NULL){ //αν  η λίστα είναι κενή τότε ο κόμβος γίνεται η κεφαλή
            *head = newNode;
            return *head;
        }

        newNode->next = *head;
        *head= newNode;
        return *head;
    }
        
}
 

//διαγραφή του κόμβου με studentID το key
int deleteNode(listNode** head, int key)
{ 
    listNode* temp ;
    listNode *previous; 
    
    temp = *head;
    if (temp == NULL) {
        fprintf(stderr, "Can't delete the node with key %d\n",key);
        return -1; 
    }
    // αν ο κόμβος είναι η κεφαλή η κεφαλή γίνεται ο δεύτερος κόμβος
   
    if ( key == temp->studentID) 
    { 
        *head = temp->next;   
        free(temp->name);
        free(temp->lastname);
        free(temp);               
        return 0; 
    } 
  
   //ψάχνει τον κόμβο 
    while (temp != NULL && key!=temp->studentID) 
    { 
        previous = temp; 
        temp = temp->next; 
    } 
  
    //αν υπάρχει αυτός ο κόμβος αλλάζει τον προηγούμενο κόμβο να δείχνει στον επόμενο αυτού που διαγράφεται
    if(temp!=NULL){
        previous->next = temp->next; 
        free(temp->name);
        free(temp->lastname);
        free(temp); 
        return 0; 
    }
    fprintf(stderr, "Node with ID %d does not exist.\n",key);
    return 0;
} 


//εκτυπώνει τον κόμβο με studentID το key
void printNode(listNode head,int key){
    listNode *temp;
    
    if((temp=findNode(&head,key))!= NULL)
        printf("%d %s %s %d %d %f\n",temp->studentID,temp->lastname,temp->name,temp->year,temp->zip,temp->gpa);
}


//βρισκεί αν υπάρχει κόμβος με studentID το key και τον επιστρέφει 
listNode* findNode(listNode* head,int key){
    listNode *temp;
    
    temp = head;
    
    if(temp!=NULL){
        while(temp!= NULL && key != temp->studentID){
             temp = temp->next; 
        }
    }
    
    return temp;
    
}


//διαγράφει όλη τη λίστα με κόμβο κεφαλής head
void deleteList(listNode **head) 
{ 
    listNode* current = *head; 
    listNode* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       if(deleteNode(head,current->studentID)==-1){
          fprintf(stderr, "Can't delete the the list\n");
          return;
       }
       current = next; 
   } 
    
    
} 