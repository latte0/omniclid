#include "../../src/HyperComplex/HyperComplex.h"
#include "../../src/HyperComplex/imagine_map.h"

using namespace omniclid;

namespace{
	constexpr std::pair<int,int> a = std::make_pair(2,4);

}
int main()
{

	using R = typename decltype(make_hypercomplex<0,double>())::type;
	using I = typename decltype(make_hypercomplex<1,double>())::type;
	using J = typename decltype(make_hypercomplex<2>())::type;
	using K = typename decltype(make_hypercomplex<3>())::type;

	R test(2.0);
	R test2(3);

	test += 2;

	HyperComplex<quaternion_map> admin{1,2,3,4};
	HyperComplex<quaternion_map> admin2{1,2,3,4};

	admin2 += admin;

	K admintest(3);

	admintest *= 10.5;
	std::cout << admin2.get<3>().get_value() << std::endl;
	admin2 += admintest;


	test += test2;
	std::cout << test.get_value() << std::endl;
	std::cout << admin2.get<3>().get_value() << std::endl;
	std::cout << quaternion_map::opmap::get<5>::val << std::endl;

	I i(2);
	J j(2);

	auto a = i * j;
	auto a2 = j * i;

	std::cout << i.dim << j.dim << a.dim << a2.dim << std::endl;
	std::cout << i.get_value() << j.get_value() << a.get_value() << a2.get_value() << std::endl;

	HyperComplex<quaternion_map> newadmin(a2);

	std::cout << newadmin.get<1>().get_value() << std::endl;

	std::cout << newadmin.get<3>().get_value() << std::endl;


	std::cout << quaternion_map::get_dy_opmap(7) << std::endl;
	HyperComplex<quaternion_map> admin3{1,2,3,4};
	HyperComplex<quaternion_map> admin4{1,2,3,4};

	admin3 *= admin4;

	std::cout << admin3.get<2>().get_value() << std::endl;

	auto&& mu = mult_seq(1,2,3,4);
	std::cout << mu << std::endl;
	std::cout << meta_vec_multiplyer<2,1>::template get<10, 3>::val << std::endl;

	std::cout << quaternion_map::opdivmap::get<12>::val << std::endl;

	std::cout << "aa"<< std::endl;

	std::cout <<admin4.get<3>().get_value() << std::endl;

  admin4 += a2;

	std::cout << admin4.get<3>().get_value() << std::endl;

	auto newadmin2 = a - a2;

	std::cout << newadmin2.get<3>().get_value() << std::endl;

	using IR = typename decltype(make_hypercomplex<0,double,imagine_map>())::type;
	using II = typename decltype(make_hypercomplex<1,double,imagine_map>())::type;

	HyperComplex<imagine_map> imagine1{2,3};
	HyperComplex<imagine_map> imagine2{4,5};

	auto imagine3 = imagine1/imagine2;

	std::cout << imagine3 << std::endl;

	return 0;
}
