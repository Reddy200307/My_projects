#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        FILE *f = fopen("tests/cases_small.txt", "r");
        if (!f)
        {
                perror("Failed to open test file");
                return 1;
        }

        int input, expected;
        int passed = 0, total = 0;

        while (fscanf(f, "%d %d", &input, &expected) == 2)
        {
                int result = solve(input);
                total++;

                if (result == expected)
                {
                        passed++;
                }
                else
                {
                        printf("FAIL: input=%d expected=%d got=%d\n",
                               input, expected, result);
                }
        }

        fclose(f);

        printf("\nResult: %d/%d tests passed\n", passed, total);
        return (passed == total) ? 0 : 1;
}
