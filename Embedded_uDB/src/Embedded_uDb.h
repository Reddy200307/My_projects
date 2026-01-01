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
typedef struct ResStatus
{
        int status;
        char message[50];
} Result;
enum StatusVariables
{
        Success,
        Failure,
        NotFound
};
typedef struct searchStatus
{
        int index;
        DLL *pos;
        double time;
} SrchStatus;
struct ViewData
{
        int data;
        int status;
        char message[50];
};
extern Result createNode(int);
extern struct ViewData viewData();
extern Result InsertNode(int, int);
extern struct ViewData printReverse();
extern Result deleteNode(int);
extern Result WriteTOFile();
extern Result LoadFromFile();
extern Result DeleteAll();
extern void ResetCursor();
extern void resetRevCursor();
#endif