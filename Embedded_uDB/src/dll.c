#include "Embedded_uDb.h"
DLL *head = NULL;
DLL *NavPtr = NULL;
DLL *CenterNode = NULL;
int createNode(int data)
{

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
                }
                else
                        status = Failure;
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
                        status = Success;
                }
                else
                        status = Failure;
        }
        return status;
}
int InsertNode(int target, int data)
{
        DLL *temp = head, *varptr = NULL;
        int status = 0;

        if (head == NULL)
        {
                return Failure;
        }

        while (temp != NULL && temp->data != target)
        {
                temp = temp->next;
        }

        if (temp == NULL)
        {
                return Failure;
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
        }
        else
                status = Failure;
        return status;
}
int viewData()
{
        DLL *temp = head;
        if (head == NULL)
        {
                return Failure;
        }
        system("clear");
        printf("Printing the data\n");
        while (temp != NULL)
        {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("\n\n");
        return Success;
}
int printReverse()
{
        DLL *temp = NavPtr; // Start at the END

        if (NavPtr == NULL)
        {
                printf("\033[31mList is empty\033[0m\n");
                return Failure;
        }

        printf("Printing in Reverse (The Acid Test):\n");
        while (temp != NULL)
        {
                printf("%d ", temp->data);
                temp = temp->prev; // Go BACKWARDS
        }
        printf("\n");
        return Success;
}
int deleteNode(int target)
{
        DLL *temp = head, *varptr = NULL;
        if (head == NULL)
        {
                return Failure;
        }
        while (temp != NULL && temp->data != target)
        {
                temp = temp->next;
        }

        if (temp == NULL)
        {
                return Failure;
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
        return Success;
}
int WriteTOFile()
{
        FILE *fp;
        DLL *temp = head;
        if (head == NULL)
        {
                return Failure;
        }
        fp = fopen("Hello.csv", "w");
        if (fp == NULL)
                return Failure;
        if ((temp != NULL) && (temp->next == NULL) && (temp->prev == NULL)) // if its only head node
        {
                fprintf(fp, "%d,", temp->data);
        }
        else
        {
                if (temp != NULL)
                {
                        fprintf(fp, "%d", temp->data); // Write 1st item (No comma)
                        temp = temp->next;
                }
                while ((temp != NULL)) // printing if it is more than one node
                {
                        fprintf(fp, "%d,", temp->data);
                        temp = temp->next;
                }
        }
        fclose(fp);
        return Success;
}

int LoadFromFile()
{
        FILE *fp;
        // DLL *temp = head;
        fp = fopen("Hello.csv", "r");
        int num = 0;
        if (fp == NULL)
        {
                return Failure;
        }
        while (fscanf(fp, "%d,", &num) == 1)
        {
                createNode(num);
        }

        fclose(fp);
        return Success;
}
int DeleteAll()
{
        DLL *temp = head;
        if (temp == NULL)
                return Success;
        while (temp != NULL)
        {
                head = head->next;
                free(temp);
                temp = head;
        }
        return Success;
}