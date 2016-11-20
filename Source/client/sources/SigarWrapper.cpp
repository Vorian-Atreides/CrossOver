/*
** Created by Gaston Siffert
*/

#include <unistd.h>
#include <sigar.h>
extern "C" 
{
    #include <sigar_format.h>
}

#include "SigarWrapper.h"

float SigarWrapper::getCpu()
{
    sigar_t *sigar;
    sigar_cpu_t old;
    sigar_cpu_t current;
    sigar_cpu_perc_t perc;

    if (sigar_open(&sigar))
    {
        // TODO log
        return -1;
    }
    if (sigar_cpu_get(sigar, &old) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    sleep(1);
    if (sigar_cpu_get(sigar, &current) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    if (sigar_cpu_perc_calculate(&old, &current, &perc) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    
    sigar_close(sigar);
    return perc.combined * 100.0;
}

float SigarWrapper::getMemory()
{
    sigar_t *sigar;    
    sigar_mem_t memory;

    if (sigar_open(&sigar) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    if (sigar_mem_get(sigar, &memory) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }

    sigar_close(sigar);
    float percent = memory.actual_used * 100.0 /
        (memory.total == 0 ? -1 : ((float) memory.total));
    return percent;
}

int SigarWrapper::getProcesses()
{
    sigar_t *sigar;
    sigar_proc_list_t processes;

    if (sigar_open(&sigar) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    if (sigar_proc_list_get(sigar, &processes) != SIGAR_OK)
    {
        // TODO log
        return -1;
    }
    int number = processes.number;
    sigar_proc_list_destroy(sigar, &processes);
    
    sigar_close(sigar);
    return number;
}