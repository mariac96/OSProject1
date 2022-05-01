#ifndef HASHING_H_
#define HASHING_H_

// οι συναρτήσεις για το hashtable
int initialize(int size);
int hashfunction (int key,int size);
listNode* insert(int size,int ID, char* name,char *lastname,float gpa,int zip,int year,int* count);
listNode* findHashNode(int size,int key);
void deleteHashNode(int ID,int size);
void deleteHashtable(int size);
#endif