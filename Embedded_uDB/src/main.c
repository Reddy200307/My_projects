#include "Embedded_uDb.h"
int nodeCount = 0;
void countIncremeent()
{
        nodeCount++;
}
void countDecrement()
{
        nodeCount--;
}
int main()
{
        int choice = 0, data = 0, target = 0;
        while (1)
        {
                printf("Enter the choice\n");
                printf("\033[34m1)Create Node\n2)Insert Node\n3)View Data\n4)Acid test(Print Rev)\n5)Delete Node\n6)Write to File\n7)Load From File\n8)Quit\n\033[0m");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                        printf("Enter the data to create node:-  ");
                        scanf("%d", &data);
                        if (createNode(data) == Success)
                        {
                                printf("\033[32m Node Created Successfully \033[0m\n");
                                countIncremeent();
                        }
                        else
                        {
                                printf("\033[31m Error occured creating node \033[0m\n");
                        }
                        break;
                case 2:
                        printf("Enter the target to insert node:-  ");
                        scanf("%d", &target);
                        printf("Enter the data to create node:-  ");
                        scanf("%d", &data);
                        if (InsertNode(target, data) == Success)
                        {
                                printf("\033[32m Node Inserted Successfully \033[0m\n");
                                countIncremeent();
                        }
                        else
                        {
                                printf("\033[31m Error occured inserting node \033[0m\n");
                        }
                        break;
                case 3:
                        if (viewData() == Failure)
                        {
                                printf("\033[31m Error occured  \033[0m\n");
                        }
                        break;
                case 4:
                        if (printReverse() == Failure)
                        {
                                printf("\033[31m Error occured  \033[0m\n");
                        }
                        break;
                case 5:
                        printf("Enter the target to delete node:-  ");
                        scanf("%d", &target);
                        if (deleteNode(target) == Success)
                        {
                                printf("\033[32m Node Deleted Successfully \033[0m\n");
                                countDecrement();
                        }
                        else
                        {
                                printf("\033[31m Error occured Deleted node \033[0m\n");
                        }
                        break;
                case 6:
                        if (WriteTOFile() == Failure)
                        {
                                printf("\033[31m Error occured Writing To File  \033[0m\n");
                        }
                        else
                        {
                                printf("\033[32m Successfully Written to File \033[0m\n");
                        }

                        break;
                case 7:
                        if (LoadFromFile() == Failure)
                        {
                                printf("\033[31m Error occured Loading From File  \033[0m\n");
                        }
                        else
                        {
                                printf("\033[32m Successfully Loaded From File \033[0m\n");
                        }
                        break;
                case 8:
                        if (DeleteAll() == Success)
                        {
                                printf("\033[32m Cleared memory \033[0m\n");
                        }
                        else
                        {
                                printf("\033[31m Error occured Clearing memory  \033[0m\n");
                        }
                        exit(0);
                        break;

                default:
                        printf("\033[31m Wrong choice\n \033[0m");
                        break;
                }
        }
        return 0;
}
