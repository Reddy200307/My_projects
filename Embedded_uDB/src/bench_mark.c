/* benchmark.c */
#include <stdio.h>
#include <time.h>
#include "Embedded_uDb.h"

// Define how hard we want to stress the system
#define NUM_NODES 50000

int main()
{
        printf("======================================\n");
        printf("   MicroDB Performance Benchmark v1.0 \n");
        printf("======================================\n");
        printf("Stress Testing with %d Nodes...\n", NUM_NODES);

        // 1. Measure Write Speed
        printf("[*] Starting Insertion...\n");
        clock_t start = clock();

        for (int i = 0; i < NUM_NODES; i++)
        {
                createNode(i); // Pure insertion
        }

        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("✅ Inserted %d nodes in %f seconds.\n", NUM_NODES, time_taken);
        printf("🚀 Speed: %f nodes/sec\n", NUM_NODES / time_taken);

        // 2. Measure I/O Speed (Save to Disk)
        printf("\n[*] Saving to Disk (CSV)...\n");
        start = clock();

        WriteTOFile();

        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("✅ Saved to 'Hello.csv' in %f seconds.\n", time_taken);

        // 3. Cleanup
        printf("\n[*] Cleaning up memory...\n");
        DeleteAll();
        printf("Done.\n");

        return 0;
}