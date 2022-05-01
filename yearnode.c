#include "yearnode.h"
#include <string.h>
#include <stdio.h>
#include "studentlist.h"
#include <stdlib.h>

//εισαγωγή στο inverted list 
int insertYear(yearNode **head,listNode *student)
{ 
    yearNode* newNode;
    //αν δεν υπάρχει ήδη κόμβος με αυτό το έτος 
   if((newNode=findYear(*head,student->year))==NULL){
        newNode = (yearNode*) malloc(sizeof( yearNode)); 
   
    
        if(newNode == NULL ) {
            fprintf(stderr, "Error - unable to allocate required memory for year node\n");
            return -1;
        }else{
            newNode->year = student->year;
        }
        if(insertStudentNode(&newNode->students,student)==-1){
            return -1;
        }

        
        if(*head == NULL){ //αν  η λίστα είναι κενή τότε ο κόμβος γίνεται η κεφαλή
            *head = newNode;
            return 0;
        }

        newNode->nextYear = *head;
        *head= newNode;
        return 0;
    }
    else{ //aν υπάρχει ο κόμβος year εισάγω μόνο το student
        if(insertStudentNode(&newNode->students,student)==-1){
            return -1;
        }
    }
    
    
    return 0;
}


//εισαγωγή studentNode
int insertStudentNode(studentNode **head,listNode* student){ 
    
    studentNode* newNode = (studentNode*) malloc(sizeof( studentNode)); 
   
    
   if(newNode == NULL ) {
      fprintf(stderr, "Error - unable to allocate required memory for year node\n");
      return -1;
    }else{
        newNode->info = student;

        
        if(*head == NULL){ //αν  η λίστα είναι κενή τότε ο κόμβος γίνεται η κεφαλή
            *head = newNode;
            newNode->next = NULL;
            return 0;
        }

        newNode->next = *head;
        *head= newNode;
        return 0;
    }

}

//βρίσκει και επιστρέφει την κεφαλή της λίστας με χρονιά year
yearNode* findYear(yearNode* head,int year){
    yearNode *temp;
    
    temp = head;
    
    if(temp!=NULL){
        while(temp!= NULL && year != temp->year){
            temp = temp->nextYear; 
        }
    }
    
    return temp;
    
}

//εκτυπώνει τους n πρώτους φοιτητές στο node
int findTopYear(yearNode *temp,int n){
    int i,j;
    studentNode *temp2;
    listNode best[n];
    temp2 =temp->students;
    int max;
    listNode temp3;
    for(i=0;i<n;i++){
        best[i].gpa = 0;
        best[i].lastname = NULL;
    }
    while(temp2!=NULL)
    {   
        for(i=n-1; i>=0;i--){
            if(best[i].gpa - temp2->info->gpa <0){
               
               
                best[i] = *temp2->info;
                break;
            }
        }

        //ταξιμόμηση φθίνουσα
        for ( i = 0; i <= n-1; i++)
        {

            max = i; 
            for (j = i + 1; j < n; j++){
                if (best[j].gpa -best[max].gpa  >0) {
                   max = j; 
                }
            } 

            temp3 = best[i];
            best[i] = best[max];
            best[max]=temp3;
          
        } 
       
        temp2 = temp2->next;
        
    }
    j=0;
     for(i=0;i<n;i++){
            if(best[i].lastname !=NULL){
                j++;
                printf("%d, ",best[i].studentID);
    
            }
        }
    printf("\n");
    return j;
   
}


//βρίσκει τον ελάχιστο μέσο ΄΄ορο την χρονιά temp και εκτυπώνει τους φοιτητές με αυτόν
void findMinYear(yearNode *temp){
    
    studentNode* tempstudent;
    tempstudent = temp->students;
    float min = tempstudent->info->gpa;
 //πρώτα βρίσκει το μικρότερο gpa 
    while(tempstudent!=NULL){
      if (tempstudent->info->gpa -min <0)
      {
         min = tempstudent->info->gpa;
      }
       
      tempstudent = tempstudent->next;
    }
    
//εκτυπώνει τους φοιτητές με min gpa
    tempstudent = temp->students;   
    while(tempstudent!=NULL){
      if (tempstudent->info->gpa -min <0.000001)
      {
        printf("%d, ",tempstudent->info->studentID);
      }
       
      tempstudent = tempstudent->next;
    } 
    printf("\n");
}

//μετράει πόσοι φοιτητές βρίσκονται στο κόμβο temp  δλδ είναι εγγεγραμμένη αυτή τη χρονιά
int countStudents(yearNode *temp){
    int count=0;
    studentNode* tempstudent;
    tempstudent = temp->students;
    while(tempstudent!=NULL){
        count ++;
        tempstudent = tempstudent->next;
    }
    return count;
}


//υπολογίζει το gpa όλων των  φοιτητών βρίσκονται στο κόμβο temp
float findAverage(yearNode *temp){
    float a=0;
    int i=0;
    studentNode* tempstudent;
    tempstudent = temp->students;
    while(tempstudent!=NULL){
        i++;
        a = a+ tempstudent->info->gpa;
        tempstudent = tempstudent->next;
    }
    if(i!=0){
        return a/i;
    }
    return 0;
}

// διαγραφή studentNode που έχει χρονία το  key και student ID 
int deleteStudentNode(yearNode** head, int key,int ID)
{ 
    studentNode* temp ;
    studentNode *previous; 
    yearNode* temp2= *head;

 //ψάχνει σε ποιο κόμβο του yearNode ανήκει
    if((temp2=findYear(*head,key))!=NULL){
       temp = temp2->students;
        if (temp == NULL) {
            return -1; 
        }
        // αν ο κόμβος είναι η κεφαλή η κεφαλή γίνεται ο δεύτερος κόμβος
   
        if ( ID == temp->info->studentID) 
        { 
            temp2->students = temp->next;   
            free(temp);               
            return 0; 
        } 
  
     //ψάχνει τον κόμβο 
        while (temp != NULL && ID!=temp->info->studentID) 
        { 
            previous = temp; 
            temp = temp->next; 
        } 
  
         //αν υπάρχει αυτός ο κόμβος αλλάζει τον προηγούμενο κόμβο να δείχνει στον επόμενο αυτού που διαγράφεται
        if(temp!=NULL){
            previous->next = temp->next; 
            free(temp); 
            return 0; 
        }
        return -1;
    }
    return -1;
} 

//διαγράφει όλο τον κόμβο με year το key
int deleteYearNode(yearNode** head, int key)
{ 
    yearNode* temp ;
    yearNode *previous; 
    
    temp = *head;
    if (temp == NULL) {
        fprintf(stderr, "Can't delete the year node with year %d\n",key);
        return -1; 
    }
    // αν ο κόμβος είναι η κεφαλή η κεφαλή γίνεται ο δεύτερος κόμβος
   
    if ( key == temp->year) 
    { 
        deleteStudentNodeList(&temp->students,*head);
        *head = temp->nextYear;
        
           
        free(temp);               
        return 0; 
    } 
  
   //ψάχνει τον κόμβο 
    while (temp != NULL && key!=temp->year) 
    { 
        previous = temp; 
        temp = temp->nextYear; 
    } 
  
    //αν υπάρχει αυτός ο κόμβος αλλάζει τον προηγούμενο κόμβο να δείχνει στον επόμενο αυτού που διαγράφεται
    if(temp!=NULL){
        previous->nextYear = temp->nextYear; 
        deleteStudentNodeList(&temp->students,temp);
        free(temp); 
        return 0; 
    }
    fprintf(stderr, "Node with year %d does not exist.\n",key);
    return 0;
} 



//διαγράφει όλη τη λίστα studentnode με κεφαλή head
void deleteStudentNodeList(studentNode **head,yearNode *year) 
{ 
    studentNode* current = *head; 
    studentNode* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       if(deleteStudentNode(&year,year->year,current->info->studentID)==-1){
         
          return;
       }
       current = next; 
   } 
    
    
} 

//διαγράφει όλο το list year
void deleteYear(yearNode **year) 
{ 
    yearNode* current = *year; 
    yearNode* next; 
  
   while (current != NULL)  
   { 
       next = current->nextYear; 
       deleteYearNode(&current,current->year);
       current = next; 
   } 
    
} 


