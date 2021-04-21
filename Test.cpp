#include "doctest.h"
#include <string>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

//const string test_file = "./units.txt";
/* 
1 km = 1000 m
1 m = 100 cm
1 kg = 1000 g
1 ton = 1000 kg
1 hour = 60 min
1 min = 60 sec
1 USD = 3.33 ILS
 */

TEST_CASE("Read_units test")
{
	ifstream units_file{"units.txt"};
	CHECK(NumberWithUnits(1, "g") == NumberWithUnits(1, "g"));
	CHECK(NumberWithUnits(1, "hour") == NumberWithUnits(1, "hour"));
	CHECK(NumberWithUnits(1, "min") == NumberWithUnits(1, "min"));
	CHECK(NumberWithUnits(1, "sec") == NumberWithUnits(1, "sec"));
	CHECK(NumberWithUnits(1, "USD") == NumberWithUnits(1, "USD"));
	CHECK(NumberWithUnits(1, "ILS") == NumberWithUnits(1, "ILS"));
	CHECK(NumberWithUnits(1, "km") == NumberWithUnits(1000, "m"));
	CHECK(NumberWithUnits(1, "m") == NumberWithUnits(100, "cm"));
	CHECK(NumberWithUnits(1, "ton") == NumberWithUnits(1000, "kg"));
	CHECK(NumberWithUnits(1, "kg") == NumberWithUnits(1000, "g"));
	CHECK(NumberWithUnits(1, "hour") == NumberWithUnits(60, "min"));
	CHECK(NumberWithUnits(1, "min") == NumberWithUnits(60, "sec"));
	CHECK(NumberWithUnits(1, "USD") == NumberWithUnits(3.33, "ILS"));
	CHECK(NumberWithUnits(1, "km") == NumberWithUnits(1, "km"));
	CHECK(NumberWithUnits(1, "m") == NumberWithUnits(1, "m"));
	CHECK(NumberWithUnits(1, "cm") == NumberWithUnits(1, "cm"));
	CHECK(NumberWithUnits(1, "ton") == NumberWithUnits(1, "ton"));
	CHECK(NumberWithUnits(1, "kg") == NumberWithUnits(1, "kg"));
}

TEST_CASE("Checking operators ")
{
	ifstream units_file{"units.txt"};
	NumberWithUnits km(2, "km");
	NumberWithUnits m1(1000, "km");
	NumberWithUnits m(500, "m");
	NumberWithUnits cm(40, "m");
	NumberWithUnits ton(1, "ton");
	NumberWithUnits kg{1, "kg"};
	NumberWithUnits g{1000, "g"};
	CHECK_EQ(km--, NumberWithUnits(1, "km"));
	CHECK_EQ(m1--, NumberWithUnits(99900, "cm"));
	CHECK_EQ(m--, NumberWithUnits(499, "km"));
	CHECK_EQ(cm--, NumberWithUnits(39, "cm"));
	CHECK_EQ(kg + g, NumberWithUnits(2, "kg"));
	CHECK_EQ(km - m1, NumberWithUnits(1000, "m"));
	CHECK_EQ(ton - kg, NumberWithUnits(999, "kg"));
	CHECK_EQ(-km, NumberWithUnits(-3, "km"));
	CHECK_EQ(-m1, NumberWithUnits(-1000, "m"));
	CHECK_EQ(-ton, NumberWithUnits(-1, "ton"));
}

TEST_CASE("operator +")
{
	ifstream units_file{"units.txt"};
	NumberWithUnits a(3, "m");
	NumberWithUnits b(-40, "cm");
	NumberWithUnits c(5, "sec");
	NumberWithUnits d(3, "min");
	CHECK(d == NumberWithUnits(3, "min"));
	CHECK((NumberWithUnits(3, "m") + NumberWithUnits(40, "cm")) == NumberWithUnits(3.4, "m"));
	CHECK((NumberWithUnits(1, "kg") + NumberWithUnits(1, "g")) == NumberWithUnits(1.001, "kg"));
	CHECK((NumberWithUnits(1, "g") + NumberWithUnits(1, "kg")) == NumberWithUnits(1001, "g"));
	CHECK((NumberWithUnits(1, "g") + NumberWithUnits(1, "ton")) == NumberWithUnits(1000001, "g"));
	CHECK((NumberWithUnits(2, "ton") + NumberWithUnits(3, "g")) == NumberWithUnits(2.000003, "ton"));
	CHECK_THROWS_MESSAGE(NumberWithUnits(3, "m") + NumberWithUnits(5, "sec"), "Types not from the same system");
	CHECK_THROWS_MESSAGE(NumberWithUnits(5, "sec") + NumberWithUnits(3, "m"), "Types not from the same system");
}

TEST_CASE("OPERTOR +=")
{
	ifstream units_file{"units.txt"};
	NumberWithUnits::read_units(units_file);
	NumberWithUnits a1(3, "m"), a2(40, "cm"), a3(3.4, "m");
	CHECK((a1 += a2) == a3);
	NumberWithUnits b1(1, "g"), b2(1, "kg"), b3(1001, "g");
	CHECK((b1 += b2) == b3);
	NumberWithUnits c1(1, "kg"), c2(1, "g"), c3(1.001, "kg");
	CHECK((c1 += c2) == c3);
}

TEST_CASE("OPERTOR check check")
{
	ifstream units_file{"units.txt"};
	NumberWithUnits::read_units(units_file);
	CHECK((NumberWithUnits(3, "m") - NumberWithUnits(40, "cm")) == NumberWithUnits(2.6, "m"));
	CHECK((NumberWithUnits(1, "kg") - NumberWithUnits(1, "g")) == NumberWithUnits(0.999, "kg"));
	CHECK((NumberWithUnits(1, "g") - NumberWithUnits(1, "kg")) == NumberWithUnits(-999, "g"));
	CHECK((NumberWithUnits(1, "g") - NumberWithUnits(1, "ton")) == NumberWithUnits(-999999, "g"));
	CHECK((NumberWithUnits(2, "ton") - NumberWithUnits(3, "g")) == NumberWithUnits(1.999997, "ton"));
	CHECK_THROWS_MESSAGE(NumberWithUnits(3, "m") - NumberWithUnits(5, "sec"), "Unit not from the same system");
	CHECK_THROWS_MESSAGE(NumberWithUnits(5, "sec") - NumberWithUnits(3, "m"), "Unit not from the same system");
	CHECK_THROWS_MESSAGE(NumberWithUnits(5, "g") - NumberWithUnits(3, "km"), "Unit not from the same system");
}

TEST_CASE("OPERTOR >=<")
{
	ifstream units_file{"units.txt"};
	NumberWithUnits::read_units(units_file);
	CHECK_FALSE(NumberWithUnits(100, "ILS") > NumberWithUnits(5, "USD"));
	CHECK(NumberWithUnits(6, "kg") >= NumberWithUnits(5, "kg"));
	CHECK(NumberWithUnits(3, "ton") >= NumberWithUnits(2000, "kg"));
	CHECK(NumberWithUnits(6001, "m") >= NumberWithUnits(6, "km"));
	CHECK(NumberWithUnits(399991, "g") >= NumberWithUnits(5, "kg"));
	CHECK(NumberWithUnits(1, "hour") >= NumberWithUnits(60, "min"));
	CHECK(NumberWithUnits(5, "kg") <= NumberWithUnits(6, "kg"));
	CHECK_FALSE(NumberWithUnits(1, "hour") >= NumberWithUnits(60.1, "min"));
	CHECK(NumberWithUnits(5, "kg") < NumberWithUnits(6, "kg"));
	CHECK(NumberWithUnits(53, "ILS") < NumberWithUnits(51, "USD"));
	CHECK(NumberWithUnits(5, "kg") <= NumberWithUnits(5000, "g"));
}
