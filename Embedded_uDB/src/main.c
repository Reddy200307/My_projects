#include "Embedded_uDb.h"
int main()
{
        srch *s;
        s = (srch *)malloc(sizeof(srch));
        s->index = 10;
        strcpy(s->link, "www.google.com");
        strcpy(s->keywords[0], "google");
        strcpy(s->keywords[1], "search");
        strcpy(s->keywords[2], "browser");
        strcpy(s->keywords[3], "company");
        printf("Printing details\n");
        printf("link is %s index is %d\n", s->link, s->index);
        printf("keywords\n");
        for (int i = 0; i < 4; i++)
        {
                printf("%s\n", s->keywords[i]);
        }
        printf("\n");
}