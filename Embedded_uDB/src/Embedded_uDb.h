#ifndef EMBEDDED_H
#define EMBEDDED_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct DoubleLinkedList
{
        struct DoubleLinkedList *prev;
        int data;
        struct DoubleLinkedList *next;
} DLL;
// extern DLL *head = NULL;
// extern DLL *NavPtr = NULL;
// extern DLL *CenterNode = NULL;
enum Status
{
        Success,
        Failure
};

extern int createNode(int);
extern int viewData();
extern int InsertNode(int, int);
extern int printReverse();
extern int deleteNode(int);
extern int WriteTOFile();
extern int LoadFromFile();
extern int DeleteAll();
#endif