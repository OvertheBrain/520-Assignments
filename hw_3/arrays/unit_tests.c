#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    /**
     * @brief Test fixture for DynamicArray class.
     */
    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    /**
     * @brief Test fixture for DynamicArray class with death tests.
     */
    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    /**
     * @brief Test fixture for DynamicArray class with small index.
     */
    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    /**
     * @brief Test fixture for DynamicArray class with big index.
     */
    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    /**
     * @brief Test fixture for DynamicArray class with really big index.
     */
    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    /**
     * @brief Test fixture for DynamicArray class with push operation.
     */
    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    /**
     * @brief Test fixture for DynamicArray class with push_front operation.
     */
    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    /**
     * @brief Test fixture for DynamicArray class with ToString operation.
     */
    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    /**
     * @brief Test fixture for DynamicArray class with pop operation.
     */
    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    /**
     * @brief Test fixture for DynamicArray class with map operation.
     */
    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }

    /**
     * @brief Test fixture for DynamicArray class with various mathematical operations.
     */
    TEST(DynamicArray, Math) {
        DynamicArray *r = DynamicArray_range(0, 1, 0.1);
        char * str = DynamicArray_to_string(r);
        printf("ToString Example: %s\n", str);
        DynamicArray *a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 5);
        DynamicArray_push(a, 1);
        DynamicArray_push(a, 0);
        
        ASSERT_EQ(DynamicArray_first(r), 0);
        ASSERT_EQ(DynamicArray_median(a), 1.5);
        ASSERT_EQ(DynamicArray_min(r), 0);
        ASSERT_EQ(DynamicArray_sum(a), 8);
        ASSERT_EQ(DynamicArray_mean(r), 0.5);
        ASSERT_EQ(DynamicArray_last(a), 0);
        ASSERT_EQ(DynamicArray_max(a), 5);
        
        DynamicArray_destroy(r);
        DynamicArray_destroy(a);
    }

    /**
     * @brief Test fixture for DynamicArray class with merge operation.
     */
    TEST(DynamicArray, Merge) {
        DynamicArray * a = DynamicArray_range(0.1, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        ASSERT_EQ(DynamicArray_size(b), 10);
        DynamicArray * c = DynamicArray_concat(a, b);
        char * str = DynamicArray_to_string(c);
        printf("ToString Example: %s\n", str);
        
                ASSERT_STREQ(
            str,
            "[0.10000,0.20000,0.30000,0.40000,0.50000,0.60000,0.70000,0.80000,0.90000,1.00000,1.10000,1.20000,1.30000,1.40000,1.50000,1.60000,1.70000,1.80000,1.90000,2.00000]"
        );

        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
    }

    /**
     * @brief Test fixture for DynamicArray class with copy operation.
     */
    TEST(DynamicArray, Copy) {
        DynamicArray * a = DynamicArray_range(0.1, 1, 0.1);
        DynamicArray * b = DynamicArray_copy(a);
        DynamicArray * c = DynamicArray_new();
        DynamicArray_push(c, 0.85);
        DynamicArray * d = DynamicArray_concat(b, c);

        char * str = DynamicArray_to_string(b);
        char * str1 = DynamicArray_to_string(d);
        printf("ToString Example: %s\n", str1);
        
        ASSERT_STREQ(
            str,
            "[0.10000,0.20000,0.30000,0.40000,0.50000,0.60000,0.70000,0.80000,0.90000,1.00000]"
        );

        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    /**
     * @brief Test fixture for DynamicArray class with take operation.
     */
    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 2);  /* yields [ 1, 2 ] */
        DynamicArray * c = DynamicArray_take(a, -2); /* yields [ 4, 5 ] */
        DynamicArray * d = DynamicArray_take(a, 7);  /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */

        char * str1 = DynamicArray_to_string(b);
        char * str2 = DynamicArray_to_string(c);
        char * str3 = DynamicArray_to_string(d);
        printf("ToString Example: %s\n", str3);

        ASSERT_STREQ(
            str1,
            "[1.00000,2.00000]"
        );
        ASSERT_STREQ(
            str2,
            "[4.00000,5.00000]"
        );
        ASSERT_STREQ(
            str3,
            "[1.00000,2.00000,3.00000,4.00000,5.00000,0,0]"
        );

        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    /**
     * @brief Test fixture for DynamicArray class with extra operations.
     */
    TEST(DynamicArray, Extra) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);             
    }           

}  // End of namespace

