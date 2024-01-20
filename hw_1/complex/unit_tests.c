#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complexes, BasicsAdd) {
        Complex a = (Complex) { 2, 3 },
                 b = (Complex) { 4, 5 };
        EXPECT_EQ(add(a,b).real, 6);
        EXPECT_EQ(add(a,b).im, 8);

    }

    TEST(Complexes, BasicsMultiply) {
        Complex a = (Complex) { 2, 3 },
                 b = (Complex) { -2, 3 };
        EXPECT_EQ(multiply(a,b).real, -13);
        EXPECT_EQ(multiply(a,b).im, 0);

    }

    TEST(Complexes, BasicsNegate) {
        Complex a = (Complex) { 4, 5 };

        EXPECT_EQ(negate(a).real, -4);
        EXPECT_EQ(negate(a).im, -5);
    }

    TEST(Complexes, BasicsMagnitude) {
        Complex a = (Complex) { 3, 4 };

        EXPECT_EQ(magnitude(a), 5);
    }

}
