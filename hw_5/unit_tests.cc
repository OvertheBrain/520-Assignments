#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "utilities.h"
#include <map>
#include <vector>
#include "gtest/gtest.h"

namespace {
    std::map<string, int> omap = occurrence_map("./test.txt");

    TEST(Map, Parse) {
        ASSERT_EQ(omap["i'm"], 1);
        ASSERT_EQ(omap["done"], 1);
        ASSERT_EQ(omap["you"], 1);
        ASSERT_EQ(omap["are"], 1);
        ASSERT_EQ(omap["the)s"], 0);
        ASSERT_EQ(omap["is"], 4);
    }

    TEST(Map, SepcialQuotes){
        ASSERT_EQ(omap["blah"], 3);
        ASSERT_EQ(omap["biotech"], 1);
        ASSERT_EQ(omap["mallory's"], 1);
        ASSERT_EQ(omap["my"], 1);
        ASSERT_EQ(omap["wier_d"], 0);

        ASSERT_EQ(omap["i"], 0);
        ASSERT_EQ(omap["quotes'"], 1);
    }

    TEST(Sort, Sort){
        std::vector<double> v = {-1, -2, -5, 6, 7, -9, 4};
        sort_by_magnitude(v);
        ASSERT_EQ(v[0], -1);
        ASSERT_EQ(v[v.size()-1], -9);
    }

    TEST(Matrix, RandW){
        TypedArray<TypedArray<double>> matrix = read_matrix_csv("./matrix.txt");
        write_matrix_csv(matrix, "./write.txt");
    }

}