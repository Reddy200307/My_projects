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
        Result res;
        struct ViewData viewRes;
        SrchStatus srch;
        int choice = 0, data = 0, target = 0;
        while (1)
        {
                printf("Enter the choice\n");
                printf("\033[34m1)Create Node\n2)Insert Node\n3)View Data\n4)Acid test(Print Rev)\n5)Delete Node\n6)Write to File\n7)Load From File\n8)Search For Node \n9)Update Node\n10)Load From Binary\n11)Save to binary \n12)Quit\n\033[0m");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                        printf("Enter the data to create node:-  ");
                        scanf("%d", &data);
                        res = createNode(data);
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                                countIncremeent();
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 2:
                        printf("Enter the target to insert node:-  ");
                        scanf("%d", &target);
                        printf("Enter the data to create node:-  ");
                        scanf("%d", &data);
                        res = InsertNode(target, data);
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                                countIncremeent();
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 3:
                        ResetCursor();
                        printf("Data: ");
                        while (1)
                        {
                                viewRes = viewData();

                                if (viewRes.data == EOF)
                                        break;
                                printf("%d ", viewRes.data);
                        }
                        printf("\n");
                        if (viewRes.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", viewRes.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", viewRes.message);
                        }
                        break;
                case 4:
                        resetRevCursor();
                        printf("Data: ");
                        while (1)
                        {
                                viewRes = printReverse();

                                if (viewRes.data == EOF)
                                        break;
                                printf("%d ", viewRes.data);
                        }
                        printf("\n");
                        if (viewRes.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", viewRes.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", viewRes.message);
                        }
                        break;
                case 5:
                        printf("Enter the target to delete node:-  ");
                        scanf("%d", &target);
                        res = deleteNode(target);
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                                countDecrement();
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 6:
                        res = WriteTOFile();
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }

                        break;
                case 7:
                        res = LoadFromFile();
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 8:
                        printf("Enter the Node Data You want to search for ? ");
                        scanf("%d", &target);
                        srch = SearchData(target);
                        if (srch.status == Success)
                        {
                                printf("\033[32m %s at %d and took %f s \033[0m\n", srch.message, srch.index, srch.time);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", srch.message);
                        }
                        break;
                case 9:
                        printf("Enter the Node and Data You want to search and udpate ? ");
                        scanf("%d %d", &target, &data);
                        res = UpdateNode(target, data);
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 10:
                        res = LoadFromBinary("data.bin");
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 11:
                        res = SaveToBinary("data.bin");
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
                        }
                        break;
                case 12:
                        res = DeleteAll();
                        if (res.status == Success)
                        {
                                printf("\033[32m %s \033[0m\n", res.message);
                                nodeCount = 0;
                        }
                        else
                        {
                                printf("\033[31m %s \033[0m\n", res.message);
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
