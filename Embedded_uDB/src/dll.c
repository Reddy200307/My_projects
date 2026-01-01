#include "Embedded_uDb.h"
DLL *head = NULL;
DLL *NavPtr = NULL;

DLL *cursor = NULL;
Result createNode(int data)
{
        Result res;

        DLL *temp = NULL;

        if (head == NULL)
        {
                head = (DLL *)malloc(sizeof(DLL));
                if (head != NULL)
                {
                        head->next = NULL;
                        head->prev = NULL;
                        head->data = data;
                        NavPtr = head;
                        res.status = Success;
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
                strcpy(res.message, "Error");
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
                res.status = Success;
                strcpy(res.message, "Successfully Inserted Node");
        }
        else
        {

                res.status = Failure;
                strcpy(res.message, "Malloc Failed");
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
        strcpy(res.message, "Deleted Node");
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
        cursor = NULL;
        res.status = Success;
        strcpy(res.message, "Deleted All Nodes");
        return res;
}
SrchStatus SearchData(int target)
{
        DLL *temp = head;
        int count = 0;
        SrchStatus res;
        if (temp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "No Nodes");
                res.index = 0;
                res.pos = NULL;
                res.time = 0;
                return res;
        }
        clock_t start = clock();
        while (temp != NULL && temp->data != target)
        {
                temp = temp->next;
                count++;
        }
        if (temp != NULL && temp->data == target)
        {
                res.status = Success;
                strcpy(res.message, "Found target");
                res.index = count;
                res.pos = temp;
        }
        else
        {
                res.status = NotFound;
                strcpy(res.message, "target Not Found ");
                res.index = count;
                res.pos = temp;
        }
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        res.time = time_taken;
        return res;
}

Result UpdateNode(int target, int newData)
{
        Result res;
        SrchStatus search = SearchData(target);

        if (search.status == Success)
        {
                search.pos->data = newData;
                res.status = Success;
                strcpy(res.message, "Node Updated Successfully");
        }
        else
        {
                res.status = Failure;
                strcpy(res.message, "Target Node Not Found");
        }
        return res;
}

Result SaveToBinary(const char *filename)
{
        Result res;
        FILE *fp = fopen(filename, "wb");
        if (fp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "[Error] Could not open file for writing.");
                return res;
        }

        DLL *temp = head;
        int buffer[1024];
        int bufIndex = 0;

        while (temp != NULL)
        {
                buffer[bufIndex] = temp->data;
                bufIndex++;
                if (bufIndex >= 1024)
                {
                        fwrite(buffer, sizeof(int), 1024, fp);
                        bufIndex = 0;
                }

                temp = temp->next;
        }

        if (bufIndex > 0)
        {
                fwrite(buffer, sizeof(int), bufIndex, fp);
        }

        fclose(fp);
        res.status = Success;
        strcpy(res.message, "[Success] Binary Dump Complete.");
        return res;
}

Result LoadFromBinary(const char *filename)
{
        Result res;
        FILE *fp = fopen(filename, "rb");
        if (fp == NULL)
        {
                res.status = Failure;
                strcpy(res.message, "[Error] Could not open file for reading..");
                return res;
        }

        int buffer[1024];
        size_t itemsRead;

        // Read chunks of 1024 integers
        while ((itemsRead = fread(buffer, sizeof(int), 1024, fp)) > 0)
        {
                for (size_t i = 0; i < itemsRead; i++)
                {
                        createNode(buffer[i]);
                }
        }

        fclose(fp);
        res.status = Success;
        strcpy(res.message, "[Success] Database Loaded.");
        return res;
}