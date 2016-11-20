/*
** Created by Gaston Siffert
*/

#ifndef SIGAR_WRAPPER_H
#define SIGAR_WRAPPER_H

/*
** Sigar is a C library, this wrapper is meant to abstract those
** C functions, from the C++ project.
*/
class SigarWrapper
{
public:
    // Get the current CPU usage in percent
    static float getCpu();
    // Get the current memory usage in percent
    static float getMemory();
    // Get the number of running processes
    static int getProcesses();
};

#endif //SIGAR_WRAPPER_H