#include <gtest/gtest.h>
#include <cstddef>

#include "../../src/HyperComplex/HyperComplex.h"
#include "../../src/HyperComplex/imagine_map.h"
#include "../../src/HyperComplex/quaternion_map.h"

using namespace omniclid;

TEST(QUATERNION, HyperComplex)
{

  using QR = typename decltype(make_hypercomplex<0,quaternion_map>())::type;
	using QI = typename decltype(make_hypercomplex<1,quaternion_map>())::type;
	using QJ = typename decltype(make_hypercomplex<2,quaternion_map>())::type;
	using QK = typename decltype(make_hypercomplex<3,quaternion_map>())::type;

  auto qmap = quaternion_map::opmap::get<5>::val ;

  ASSERT_EQ(qmap , -1);
  ASSERT_EQ(quaternion_map::get_dy_opmap(7), -3);


  auto&& mu = mult_seq(1,2,3,4);


  ASSERT_EQ(mu, 24);
  auto cross = meta_vec_multiplyer<2,1>::template get<10, 3>::val;
  ASSERT_EQ(cross, 23);
  auto qdivmap = quaternion_map::opdivmap::get<12>::val;
  //ASSERT_EQ(quaternion_map::opdivmap::get<12>::val, -3);



  QR q(2.0);
  QR q2(3);

  q += 2;
  q += q2;

  ASSERT_EQ(q.get_dim(),0);
  ASSERT_DOUBLE_EQ(q.get_value(),7.0);


  HyperComplex<quaternion_map> complex{1,2,3,4};
  HyperComplex<quaternion_map> complex2{1,2,3,4};

  complex2 += complex;

  QK q3(3);
  q3 *= 10.5;
  complex2 += q3;

  ASSERT_DOUBLE_EQ(complex2.get<3>().get_value(),39.5);


  QI i(2);
  QJ j(2);

  auto qx = i * j;
  auto qx2 = j * i;

  ASSERT_EQ(i.get_dim(), 1);
  ASSERT_EQ(j.get_dim(), 2);
  ASSERT_EQ(qx.get_dim(),3);
  ASSERT_EQ(qx2.get_dim(),3);

  ASSERT_EQ(i.get_value(), 2);
  ASSERT_EQ(j.get_value(), 2);
  ASSERT_EQ(qx.get_value(),4);
  ASSERT_EQ(qx2.get_value(),-4);

  HyperComplex<quaternion_map> q_copy(qx2);

  ASSERT_EQ(q_copy.get<1>().get_value(), 0);
  ASSERT_EQ(q_copy.get<3>().get_value(),-4);

  HyperComplex<quaternion_map> complex3{1,2,3,4};
  HyperComplex<quaternion_map> complex4{1,2,3,4};

  complex3 *= complex4;

  ASSERT_EQ(complex3.get<2>().get_value(),6);
  ASSERT_EQ(complex4.get<3>().get_value(),4);

  complex4 += qx2;

  ASSERT_EQ(complex4.get<3>().get_value(),0);

  auto complex5 = qx - qx2;

  ASSERT_EQ(complex5.get<3>().get_value(),8);

}

TEST(COMPLEX, HyperComplex)
{
  double delta = 0.001;

  using IR = typename decltype(make_hypercomplex<0,imagine_map>())::type;
	using II = typename decltype(make_hypercomplex<1,imagine_map>())::type;

	HyperComplex<imagine_map> imagine1{2,3};
	HyperComplex<imagine_map> imagine2{4,5};

	auto imagine3 = imagine1/imagine2;

  ASSERT_NEAR(imagine3.get<0>().get_value(), 0.560976,delta);
  ASSERT_NEAR(imagine3.get<1>().get_value(), 0.0487805,delta);

}

TEST(DUALQUATERNION, HyperComplex)
{

}
