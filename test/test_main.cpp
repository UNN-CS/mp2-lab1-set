#include <gtest/gtest.h>
#include <Header.h>

int test(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
