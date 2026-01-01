#include "Embedded_uDb.h"
DLL *head = NULL;
DLL *NavPtr = NULL;
DLL *CenterNode = NULL;
DLL *cursor = NULL;
Result createNode(int data)
{
        Result res;

        DLL *temp = NULL;
        int status = 0;
        if (head == NULL)
        {
                head = (DLL *)malloc(sizeof(DLL));
                if (head != NULL)
                {
                        head->next = NULL;
                        head->prev = NULL;
                        head->data = data;
                        NavPtr = head;
                        status = Success;
                        strcpy(res.message, "Node Created Succesfully");
                }
                else
                {

                        res.status = Failure;
                        strcpy(res.message, "Node Failed To Create Node Succesfully");
                }
        }
        else
        {
                temp = (DLL *)malloc(sizeof(DLL));
                if (temp != NULL)
                {

                        temp->data = data;
                        temp->next = NULL;
                        temp->prev = NavPtr;
                        NavPtr->next = temp;
                        NavPtr = temp;
                        res.status = Success;
                        strcpy(res.message, "Node Created Succesfully");
                }
                else
                {

                        res.status = Failure;
                        strcpy(res.message, "Node Failed To Create Node Succesfully");
                }
        }
        return res;
}
Result InsertNode(int target, int data)
{
        Result res;
        DLL *temp = head, *varptr = NULL;
        int status = 0;

        if (head == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Head is Empty First Create head Node");
                return res;
        }

        while (temp != NULL && temp->data != target)
        {
                temp = temp->next;
        }

        if (temp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Target Node Not Found");
                return res;
        }

        varptr = (DLL *)malloc(sizeof(DLL));
        if (varptr != NULL)
        {

                varptr->data = data;
                varptr->prev = temp;
                varptr->next = temp->next;

                if (temp->next != NULL)
                {
                        temp->next->prev = varptr;
                }

                temp->next = varptr;
                if (temp == NavPtr)
                {
                        NavPtr = varptr;
                }
                status = Success;
                strcpy(res.message, "Successfully Inserted Node");
        }
        else
        {

                res.status = NotFound;
                strcpy(res.message, "Target Node Not Found");
        }
        return res;
}
void ResetCursor()
{
        cursor = head;
}
struct ViewData viewData()
{
        struct ViewData res;
        if (head == NULL)
        {
                res.status = Failure;
                res.data = EOF;
                strcpy(res.message, "Head is Empty First Create head Node");
                return res;
        }
        if (cursor != NULL)
        {
                res.data = cursor->data;
                cursor = cursor->next;
                strcpy(res.message, "Printing The Node");
        }
        else
        {
                res.data = EOF;
                strcpy(res.message, "Printed All Data Node");
        }
        res.status = Success;
        return res;
}
void resetRevCursor()
{
        cursor = NavPtr;
}
struct ViewData printReverse()
{
        struct ViewData res;
        if (head == NULL)
        {
                res.status = Failure;
                res.data = EOF;
                strcpy(res.message, "Head is Empty First Create head Node");
                return res;
        }
        if (cursor != NULL)
        {
                res.data = cursor->data;
                cursor = cursor->prev;
                strcpy(res.message, "Printing The Node");
        }
        else
        {
                res.data = EOF;
                strcpy(res.message, "Printed All Data Node");
        }
        res.status = Success;
        return res;
}
Result deleteNode(int target)
{
        Result res;
        DLL *temp = head, *varptr = NULL;
        if (head == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Head is Empty First Create head Node");
                return res;
        }
        while (temp != NULL && temp->data != target)
        {
                temp = temp->next;
        }

        if (temp == NULL)
        {
                res.status = NotFound;
                strcpy(res.message, "Not Found");
                return res;
        }

        if (temp == head)
        {
                varptr = head;
                head = head->next;

                if (head != NULL)
                {
                        head->prev = NULL;
                }
                else
                {
                        NavPtr = NULL;
                }

                free(varptr);
        }
        else if (temp == NavPtr)
        {
                varptr = NavPtr;
                NavPtr = NavPtr->prev;
                NavPtr->next = NULL;
                free(varptr);
        }
        else
        {
                varptr = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(varptr);
        }
        res.status = Success;
        strcpy(res.message, "Deleted All Nodes");
        return res;
}
Result WriteTOFile()
{
        Result res;
        FILE *fp;
        DLL *temp = head;

        if (head == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Head is Empty");
                return res;
        }

        fp = fopen("Hello.csv", "w");
        if (fp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Error Opening File");
                return res;
        }
        while ((temp != NULL) && (temp->next != NULL))
        {
                fprintf(fp, "%d,", temp->data);
                temp = temp->next;
        }

        if (temp != NULL)
        {
                fprintf(fp, "%d", temp->data);
        }

        fclose(fp);
        res.status = Success;
        strcpy(res.message, "Wrote To File");
        return res;
}
Result LoadFromFile()
{
        Result res;
        FILE *fp;
        // DLL *temp = head;
        fp = fopen("Hello.csv", "r");
        int num = 0;
        if (fp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "Error Opening File");
                return res;
        }
        while (fscanf(fp, "%d,", &num) == 1)
        {
                createNode(num);
        }

        fclose(fp);
        res.status = Success;
        strcpy(res.message, "Loaded From File");
        return res;
}
Result DeleteAll()
{
        Result res;
        DLL *temp = head;
        if (temp == NULL)
        {
                res.status = Success;
                strcpy(res.message, "Head is  already Empty");
                return res;
        }
        while (temp != NULL)
        {
                head = head->next;
                free(temp);
                temp = head;
        }
        NavPtr = NULL;
        head = NULL;
        res.status = Success;
        strcpy(res.message, "Deleted All Nodes");
        return res;
}
