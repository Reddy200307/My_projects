/* benchmark_final_heavy.c */
#include <stdio.h>
#include <stdlib.h> // For rand()
#include <time.h>
#include "Embedded_uDb.h"

//  🔥 RAMPED UP VALUES 🔥
#define NUM_NODES 50000000
#define RANDOM_OPS 100 // 100 Random Ops

// Helper to generate a large random number up to max
int get_random_id(int max)
{
        return rand() % max;
}

int main()
{
        srand(time(NULL));

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
        // PHASE 2: RANDOM SEARCH
        // ---------------------------------------------------------
        printf("[Phase 2] Performing %d Random Searches...\n", RANDOM_OPS);
        double total_search_time = 0;
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
                        print_once = 0;
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
                clock_t op_start = clock();
                UpdateNode(target, 999999);
                clock_t op_end = clock();
                total_update_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Update Time: %f sec/op\n\n", total_update_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // PHASE 4: RANDOM INSERT
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
                int target = get_random_id(NUM_NODES * 0.75);
                clock_t op_start = clock();
                deleteNode(target);
                clock_t op_end = clock();
                total_del_time += ((double)(op_end - op_start)) / CLOCKS_PER_SEC;
        }
        printf("   📊 Avg Delete Time: %f sec/op\n\n", total_del_time / RANDOM_OPS);

        // ---------------------------------------------------------
        // PHASE 6: I/O SHOWDOWN (CSV vs BINARY) 🥊
        // ---------------------------------------------------------
        printf("===========================================\n");
        printf("   🥊 PHASE 6: THE I/O SHOWDOWN 🥊        \n");
        printf("===========================================\n");

        // --- TEST 1: CSV WRITE (The Old Way) ---
        printf("[CSV] Saving 50M nodes to 'Hello.csv' (Text Mode)...\n");
        printf("      (This might take a while, please wait...)\n");
        fflush(stdout);

        clock_t csv_start = clock();
        WriteTOFile(); // Saves to Hello.csv
        clock_t csv_end = clock();

        double csv_time = ((double)(csv_end - csv_start)) / CLOCKS_PER_SEC;
        printf("   🐌 CSV Time:    %f sec\n", csv_time);

        // --- TEST 2: BINARY DUMP (The New Way) ---
        printf("\n[BIN] Saving 50M nodes to 'bench.bin' (Binary Mode)...\n");
        fflush(stdout);

        clock_t bin_start = clock();
        SaveToBinary("bench.bin");
        clock_t bin_end = clock();

        double bin_time = ((double)(bin_end - bin_start)) / CLOCKS_PER_SEC;
        printf("   ⚡ BINARY Time: %f sec\n", bin_time);

        // --- CALCULATION ---
        if (bin_time > 0)
        {
                printf("\n   🏆 RESULT: Binary is %.2fx FASTER than CSV!\n", csv_time / bin_time);
        }

        // ---------------------------------------------------------
        // CLEANUP
        // ---------------------------------------------------------
        printf("\n[*] Cleaning up RAM...");
        fflush(stdout);
        DeleteAll();
        printf(" DONE.\n");

        return 0;
}