#include <gtest/gtest.h>
#include <cstddef>

#include "../../src/Matrix/Matrix.h"


using namespace omniclid;


int main(void)
{


    Matrix_initializer<int,2> mi;
    Matrix<int,1> m_i{1,2,3,4};
    Matrix<int,3> mi2(2,2,2);
    Matrix<int,2> m2 { {{1},{2}},{{3},{4}},{{5},{6}} };

    Matrix<int,1> m2_copy(m2[1]);

    Matrix<int,3> m3 {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{11},{12}},{{13},{14}},{{15},{16}} } , { {{17},{18}},{{19},{110}},{{111},{112}} }  };

    Matrix<int,2> m3_copy(m3[2]);

    Matrix<int,4> m4 {
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  } ,
      {  { {{1},{2}},{{3},{4}},{{5},{6}} }, { {{7},{8}},{{9},{10}},{{11},{12}} } ,  { {{1},{2}},{{3},{4}},{{5},{6}} } , { {{7},{8}},{{9},{10}},{{11},{12}} }  }
    };

    Matrix<int,3> m4_copy(m4[1]);
//    ASSERT_EQ(1,m(0,0));

    for(auto it = m4_copy.begin(); it != m4_copy.end(); it++){
      std::cerr<< *it << std::endl;
    }

    Matrix<int,2> mult1 { {1,2},{3,4},{5,6} };
    Matrix<int,2> mult2 { {1,2,3},{4,5,6} };

    auto mult3 = mult1 * mult2;

    for(auto it = mult3.begin(); it != mult3.end(); it++){
      std::cout<< *it << std::endl;
    }

    mult1 += 2;
    mult1 += mult1;
    auto add3 = mult1 + mult1;

    std::cout << "matrixtype"<<Matrix_type<decltype(add3)>()<< std::endl;


    std::cout << m4 << std::endl;
    //add3[0];

    for(auto it = add3.begin(); it != add3.end(); it++){
      std::cout<< *it << std::endl;
    }

    std::cout << Matrix_type<decltype(mult2)>() << std::endl;
    std::cout << Matrix_type<int>() << std::endl;


    std::cout << "single2"<< std::endl;
    Matrix<int, 1> single {1,2,3,4,5};
    std::cout << single[2] << std::endl;

    std::cout << "end" << std::endl;
    Matrix<int,0> single_copy(single[2]);

    std::cout << single_copy() << std::endl;

    std::cout << single << std::endl;
    std::cout << m4_copy;


}
