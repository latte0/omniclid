#include <gtest/gtest.h>
#include <cstddef>

#include "../../src/Matrix/Matrix.h"


using namespace omniclid;


TEST(MatrixTest, Matrix)
{
    ASSERT_TRUE((Convertible<int,size_t>()));
    ASSERT_TRUE((Same<int, int>()));
    ASSERT_TRUE(
                  (Matrix_type<   decltype(Matrix<int,2>())   >)
                );

    Matrix_initializer<int,2> mi;
    Matrix<int,1> m_i{1,2,3,4};
    Matrix<int,3> mi2(2,2,2);
    Matrix<int,2> m2 { {{1},{2}},{{3},{4}},{{5},{6}} };

    Matrix<int,1> m2_copy(m2[1]);

    Matrix<int,3> m3 {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{11},{12}},{{13},{14}},{{15},{16}} } , { {{17},{18}},{{19},{110}},{{111},{112}} }  };

    Matrix<int,2> m3_copy(m3[2]);

    ASSERT_EQ(14,m3_copy(1,1));

    Matrix<int,4> m4 {
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  }
    };

    Matrix<int,3> m4_copy(m4[1]);
    ASSERT_EQ(1,m4_copy(0,0,0));
    ASSERT_EQ(7,m4_copy(1,0,0));


    Matrix<int,2> mult1 { {1,2},{3,4},{5,6} };
    Matrix<int,2> mult2 { {1,2,3},{4,5,6} };

    auto mult3 = mult1 * mult2;

    ASSERT_EQ(9,mult3(0,0));
    ASSERT_EQ(51,mult3(2,2));

    mult1 += 2;
    mult1 += mult1;
    auto add3 = mult1 + mult1;


    ASSERT_EQ(12,add3(0,0));
    ASSERT_EQ(32,add3(2,1));


    Matrix<int, 1> single {1,2,3,4,5};
    ASSERT_EQ(3,single[2]());

    single[2]() = 10;

    Matrix<int,0> single_copy(single[2]);

    ASSERT_EQ(single_copy(),10);


}
