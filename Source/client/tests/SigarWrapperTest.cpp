#include <gtest/gtest.h>

#include "SigarWrapper.h"

TEST(CpuTest, SigarWrapper)
{
    EXPECT_GT(SigarWrapper::getCpu(), 0.0);
}

TEST(MemoryTest, SigarWrapper)
{
    EXPECT_GT(SigarWrapper::getMemory(), 0.0);
}

TEST(ProcessesTest, SigarWrapper)
{
    EXPECT_GT(SigarWrapper::getProcesses(), 0);
}