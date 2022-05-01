#include <stdio.h>
#include "functions.h"
#include <string.h>
#include "yearnode.h"


int main (int argc, char* argv[])
{   
    yearNode *first=NULL;
    char c;
    int size;
 

    size = readfiles(argc,argv,&first);
    
    printf("Waiting for commands.\n");
    c =getchar(); 
   
    while (c!='e')
    {
        if(c=='i'){ //αν είναι εισαγωγή
            insertAll(&first,size);
        }else if(c=='d')
        {   
            deleteID(&first,size);
        }
        else if(c=='l')
        {
           lookID(size);
        }
        else if(c=='n')
        {
            numberinYear(first);
        }
        else if(c=='t')
        {
            topinYear(first);
        }
        else if(c=='a')
        {
            averageYear(first);
        }
        else if(c=='m')
        {
            minimumYear(first);
        }
        else if(c=='c')
        {
            countAll(first);
        }
        
        

      
   
        c =getchar();//πρώτος χαρακτήρας εντολής
    }
    
   
    exitAll(&first,size);

}
    