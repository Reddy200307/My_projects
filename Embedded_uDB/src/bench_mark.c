/* benchmark_final_heavy.c */
#include <stdio.h>
#include <stdlib.h> // For rand()
#include <time.h>
#include "Embedded_uDb.h"
// took from ai because lazy to write benchmarking
//  🔥 RAMPED UP VALUES 🔥
#define NUM_NODES 50000000 // 50 Million Nodes (Heavy RAM Usage)
#define RANDOM_OPS 100     // 100 Random Operations (Statistically Significant)

// Helper to generate a large random number up to max
int get_random_id(int max)
{
        return rand() % max;
}

int main()
{
        srand(time(NULL)); // Seed the random number generator

        printf("===========================================\n");
        printf("   MicroDB HEAVYWEIGHT CHAOS BENCHMARK     \n");
        printf("===========================================\n");
        printf("Dataset Size: %d Nodes\n", NUM_NODES);
        printf("Random Ops:   %d per category\n", RANDOM_OPS);
        printf("-------------------------------------------\n\n");

        // ---------------------------------------------------------
        // PHASE 1: MASSIVE CREATION
        // ---------------------------------------------------------
        printf("[Phase 1] Building Database (50M Nodes)...");
        fflush(stdout);

        clock_t start = clock();
        for (int i = 0; i < NUM_NODES; i++)
        {
                createNode(i);
        }
        clock_t end = clock();

        double create_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf(" DONE.\n");
        printf("   ⏱️  Time: %f sec\n", create_time);
        printf("   🚀 Speed: %.0f nodes/sec\n\n", NUM_NODES / create_time);

        // ---------------------------------------------------------
        // PHASE 2: RANDOM SEARCH (The Cache Killer)
        // ---------------------------------------------------------
        printf("[Phase 2] Performing %d Random Searches...\n", RANDOM_OPS);
        double total_search_time = 0;

        // Let's verify finding at least one node to prove it works
        int print_once = 1;

        for (int i = 0; i < RANDOM_OPS; i++)
        {
                int target = get_random_id(NUM_NODES);

                clock_t op_start = clock();
                SrchStatus status = SearchData(target);
                clock_t op_end = clock();

                if (print_once && status.status == Success)
                {
                        printf("   (Sample) ✅ Found Node %d at Index %d\n", target, status.index);
                        print_once = 0; // Only print detail once to avoid flooding screen
                }

                total_search_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Search Time: %f sec/op\n\n", total_search_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // PHASE 3: RANDOM UPDATES
        // ---------------------------------------------------------
        printf("[Phase 3] Performing %d Random Updates...\n", RANDOM_OPS);
        double total_update_time = 0;

        for (int i = 0; i < RANDOM_OPS; i++)
        {
                int target = get_random_id(NUM_NODES);
                int new_val = 999999;

                clock_t op_start = clock();
                UpdateNode(target, new_val);
                clock_t op_end = clock();

                total_update_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Update Time: %f sec/op\n\n", total_update_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // PHASE 4: RANDOM INSERT (Insertion in Middle)
        // ---------------------------------------------------------
        printf("[Phase 4] Performing %d Random Mid-List Inserts...\n", RANDOM_OPS);
        double total_ins_time = 0;

        for (int i = 0; i < RANDOM_OPS; i++)
        {
                int target = get_random_id(NUM_NODES);

                clock_t op_start = clock();
                InsertNode(target, 888);
                clock_t op_end = clock();

                total_ins_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Insert Time: %f sec/op\n\n", total_ins_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // PHASE 5: RANDOM DELETE
        // ---------------------------------------------------------
        printf("[Phase 5] Performing %d Random Deletes...\n", RANDOM_OPS);
        double total_del_time = 0;

        for (int i = 0; i < RANDOM_OPS; i++)
        {
                // Deleting from the first 75% of the list to ensure hits
                int target = get_random_id(NUM_NODES * 0.75);

                clock_t op_start = clock();
                deleteNode(target);
                clock_t op_end = clock();

                total_del_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Delete Time: %f sec/op\n\n", total_del_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // CLEANUP
        // ---------------------------------------------------------
        printf("[*] Cleaning up RAM...");
        fflush(stdout);
        DeleteAll();
        printf(" DONE.\n");

        return 0;
}