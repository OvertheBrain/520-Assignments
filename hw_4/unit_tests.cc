#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray,Concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a;
        EXPECT_EQ(b.get(5), 1);
        EXPECT_EQ(b.get(4), 0);
        
        TypedArray<int> c;
        c.push(2);
        c.push(3);

        b = b + c;
        EXPECT_EQ(b.pop(), 3);
        std::cout<< b << "\n";
    }

    TEST(TypedArray, Construction) {
        TypedArray<double> b;
        b.push(30);
        b.push(14.5);
        b.push_front(60);
        b.reverse();
        std::cout<< b << "\n";
        EXPECT_DOUBLE_EQ(b.get(0), 14.5);
        EXPECT_EQ(b.pop(), 60);
        EXPECT_DOUBLE_EQ(b.pop_front(), 14.5);

        b.push_front(0.5);
        b.reverse();
        std::cout<< b << "\n";
    }

    TEST(Complex,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Complex,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
        EXPECT_EQ(Complex(5,4) == Complex(5,4), 1);
    }

    TEST(Complex, Array) {
        TypedArray<Complex> b;
        b.set(0, Complex(3, 4));
        b.set(1, Complex(1, 2));
        b.set(20, Complex(0, 1) + Complex(6, 9));
        EXPECT_EQ(b.get(0).real(), 3);
        EXPECT_EQ(b.get(20).imaginary(), 10);
        EXPECT_EQ(b.get(20).conjugate() == Complex(6, -10), 1);

        b.reverse();
        EXPECT_DOUBLE_EQ(b.pop_front().conjugate().imaginary(), -10);
        b.push_front(Complex(-1, 0.5));
        EXPECT_DOUBLE_EQ((b.get(0) * b.pop()).real(), -5);
    }    

}