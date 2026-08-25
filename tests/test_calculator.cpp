#include <gtest/gtest.h>
#include "hardware_calculations.h"

TEST(Calculations, CalculateCPU) {
    double result = calculateCPUCores(100 ,20 ,1, 1.2);
    EXPECT_EQ(result,1);
}

TEST(Calculations, CalculateRAM) {
    double result = calculateRAM( 20 ,1, 1.2);
    EXPECT_DOUBLE_EQ(result, 24);
}

TEST(Calculations, CalculateDiscSpace) {
    double result = calculateDiscSpace(100 ,700, 1.5);
    EXPECT_EQ(result, 105000);
}
