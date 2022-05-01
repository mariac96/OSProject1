#include <stdio.h>
#include "yearnode.h"
#include "hashing.h"
#include <string.h>
#include "functions.h"


//διαβάζει τα αρχεία input και config αν υπάρχουν και εισάγει τις πληροφορίες στους πίνακες
int readfiles(int argc, char *argv[],yearNode **head){
    int inputfile=0,configfile=0,size,ID,zip,year,count=0;
    int i=1,k=0;
    FILE *fp;
    char name[20],lastname[20];
    float gpa;
    listNode* temp;
   
    
        while (i<argc )
        {
            if(strcmp(argv[i],"-i")==0){
                inputfile=i+1;  //το input file βρίσκεται στην επόμενη θέση
            }
            else if (strcmp(argv[i],"-c")==0)
            {
                configfile=i+1; //το configure file βρίσκεται στην επόμενη θέση
            }
            i++;
            
        }

        if(configfile!=0){
           if( (fp= fopen(argv[configfile],"r")) !=NULL){
               if(fscanf(fp,"%d",&size)==1) //διαβάζω τον αριθμό στο configure file και ορίζω το hashtable
                {
                    initialize(size);
                }
               
                fclose(fp);
           }

            
        }else
        {
            
            size=200;
            initialize(size); //αν δεν υπάρχει config file δημιουργώ hashtable για 200 εγγραφές
            
        }
        
        
        if(inputfile!=0){
            if((fp= fopen(argv[inputfile],"r"))!=NULL){
                while ((fscanf(fp,"%d %s %s %d %d %f",&ID,name,lastname,&zip,&year,&gpa))!=EOF){
                fgetc(fp); //διαβάζει την αλλαγή γραμμής  
                k=count;
                temp= insert(size,ID,name,lastname,gpa,zip,year,&count);
                
                if(k==count){ //αν δεν είναι διπλότυπο δλδ δεν έχει αυξηθεί ο μετρητής 
                    insertYear(head,temp);
                }
                
               
                }
             fclose(fp);
            }
           
            printf("They were %d doubles.\n",count);
        }
    return size;
}


//εισαγωγή φοιτητή στη δομή
int insertAll(yearNode**head,int size){
    int ID,zip,year,count=0;
    char name[2000],lastname[20];
    float gpa;
    listNode* temp;

    scanf("%d %s %s %d %d %f",&ID,name,lastname,&zip,&year,&gpa);
 
    temp= insert(size,ID,name,lastname,gpa,zip,year,&count); //εισαγωγή στο hashtable 

    
    if(count!=0){
        printf("Student %d exists\n",ID);   
        return 0;
    }
       
    insertYear(head,temp);   //εισαγωγή στο inverted index
    printf("Student %d inserted\n",ID);
    return 0;
}

//διαγραφή
void deleteID(yearNode**head,int size){
    
    int ID;
    
    scanf("%d",&ID);
   
    listNode *temp;
    if((temp=findHashNode(size,ID))!=NULL){
        deleteStudentNode(head,temp->year,ID); //διαγραφή από το inverted index΄
        deleteHashNode(ID,size); //διαγραφή από το hashtable
        printf("Student %d deleted.\n",ID);
    }
    else
    {
        printf("Student %d does not exist.\n",ID);
    }
}

//έξοδος και απελευθέρωση όλης της μνήμης
void exitAll(yearNode**head,int size){
    deleteYear(head);
    deleteHashtable(size);
}

//εκτυπώνει τον φοιτητή με ID που διαβάζει
void lookID(int size){
    int ID;
    
    scanf("%d",&ID);
    listNode* temp;
    temp=findHashNode(size,ID);
    if(temp!= NULL)
        printf("%d %s %s %d %d %f\n",temp->studentID,temp->lastname,temp->name,temp->zip,temp->year,temp->gpa);
    else
    {
        printf("Student %d does not exist.\n",ID);
    }
    
}

//εκτυπωνει τους φοιτητές που υπάρχουν στο year που διαβάζει
void numberinYear(yearNode*head){
    int year,c=0;
    yearNode *temp;
    scanf("%d",&year);
    temp = findYear(head,year);
    if(temp==NULL)
    {
        printf("No students enrolled in year %d\n",year);
       
    }else
    {
        c= countStudents(temp);
        if(c==0){
            printf("No students enrolled in year %d\n",year);

        }else
        {
            printf("%d student(s) in %d\n",c,year);
        }
    }
        
       
}

//εκτυπώνει τους n πρώτους στη χρονιά year
void  topinYear(yearNode*head){
    int year,n;
    scanf("%d %d",&n,&year);
    yearNode *temp;
    temp = findYear(head,year);

    if(temp == NULL){
        printf("No students enrolled in year %d\n",year);
    }else 
    {
        if(findTopYear(temp,n)==0){
             printf("No students enrolled in year %d\n",year);
        }
    }
    
}

void averageYear(yearNode*head){
    int year;
    scanf("%d",&year);
    float f;
    yearNode *temp;
    temp = findYear(head,year);
    
    if(temp == NULL){
        printf("No students enrolled in year %d\n",year);
    }else 
    {
        if((f = findAverage(temp))!=0)
            printf("%f\n",f);
        else
            printf("No students enrolled in year %d\n",year);
    }
}

//εκτυπώνει τους φοιτητές με τον ελάχιστο μέσο όρο
void minimumYear(yearNode*head){
    int year;
    scanf("%d",&year);
    yearNode *temp;
    temp = findYear(head,year);
    
   if(temp == NULL){
        printf("No students enrolled in year %d\n",year);
    }else 
    {
        findMinYear(temp);
    }
}

// εκτυπώνει για όλες τις χρονιές το πλήθος των φοιτητών
void countAll(yearNode*head){
    yearNode *temp;
    temp= head;
    int c,i=0;
   if (temp==NULL)
   {
       printf("No students are enrolled\n");
       i++;
   }
   else
   {
       while(temp!=NULL){
          c= countStudents(temp);
          if(c!=0){
                i++; //μετρητής αν δεν υπάρχουν φοιτητές θα είναι 0 
                printf("[%d - %d],",temp->year,c);
           }
           temp = temp->nextYear;
       }
   }
   
   if(i==0){
       printf("No students are enrolled\n");
   }
   else
   {
       printf("\n");
   }
   
}