/**
 *  Count CPUs
 *  ==========
 *
 *  Linux-specific version of counting CPUs (physical and hyperthread).
 */

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

bool cpu_physical(uint32_t cpu);

int
main(int argc, const char *argv[])
{
    uint32_t all, hw, ht, index, found;
    cpu_set_t all_cpus;
    cpu_set_t hw_cpus;  // hardware CPU
    cpu_set_t ht_cpus;  // hyper-threading CPU

    sched_getaffinity(0, sizeof(cpu_set_t), &all_cpus);
    CPU_ZERO(&hw_cpus);
    CPU_ZERO(&ht_cpus);

    all = CPU_COUNT(&all_cpus);
    index = found = 0;

    while (found < all) {
        if (CPU_ISSET(index, &all_cpus)) {
            if (cpu_physical(index)) CPU_SET(index, &hw_cpus);
            else CPU_SET(index, &ht_cpus);

            found++;
        }

        index++;
    }

    hw = CPU_COUNT(&hw_cpus);
    ht = CPU_COUNT(&ht_cpus);

    printf("all: %u hw: %u ht: %u\n", all, hw, ht);

    return 0;
}

bool
cpu_physical(uint32_t cpu)
{
    char file[FILENAME_MAX];
    snprintf(file, FILENAME_MAX,
        "/sys/devices/system/cpu/cpu%d/topology/thread_siblings_list",
        cpu);

    FILE* fp = fopen(file, "r");

    if (fp != NULL) {
        char name[16];
        size_t len = fread(name, 1, 15, fp);
        name[len] = '\0';
        fclose(fp);

        if (cpu != (uint32_t)atoi(name)) return false;
    }

    return true;
}
