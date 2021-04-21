#include <iostream>
#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel
{
	static map<string, map<string, double>> unitList;

	NumberWithUnits::NumberWithUnits(double number, const string &str)
	{
		cout << number << str << endl;
		this->number = number;
		this->str = str;
	}


	void incomeUnit(const string unit1, const string unit2)
	{
// 		for (auto map : unitList[unit2])
// 		{
// 			double val = unitList[unit1][unit2] * map.second;
// 			unitList[unit1][map.first] = val;
// 			unitList[map.first][unit1] = 1 / val;
// 		}
	}

	void NumberWithUnits::read_units(std::ifstream &units_file)
	{
// 		string unit1, unit2, c;
// 		double val1, val2;

// 		while (units_file >> val1 >> unit1 >> c >> val2 >> unit2)
// 		{ 			
// 			unitList[unit1][unit2] = val2;
// 			unitList[unit2][unit1] = 1 / val2;
// 			incomeUnit(unit1, unit2);
// 			incomeUnit(unit2, unit1);
// 		}
		}	

	NumberWithUnits operator+(const NumberWithUnits &k)
	{
		return NumberWithUnits(k.number, k.str);
	}
	NumberWithUnits operator+(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return NumberWithUnits(k);
	}
	NumberWithUnits operator+=(NumberWithUnits &k, const NumberWithUnits &j)
	{
		return k;
	}

	NumberWithUnits operator-(const NumberWithUnits &k)
	{
		return NumberWithUnits((-1) * k.number, k.str);
	}
	NumberWithUnits operator-(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return NumberWithUnits(k);
	}
	NumberWithUnits operator-=(NumberWithUnits &k, const NumberWithUnits &j)
	{
		return k;
	}

	bool operator>(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}
	bool operator>=(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}
	bool operator<(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}
	bool operator<=(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}
	bool operator==(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}
	bool operator!=(const NumberWithUnits &k, const NumberWithUnits &j)
	{
		return true;
	}

	NumberWithUnits operator++(NumberWithUnits &k)
	{
		return NumberWithUnits(k);
	}

	NumberWithUnits operator++(NumberWithUnits j, int)
	{
		return NumberWithUnits(j);
	}

	NumberWithUnits operator--(NumberWithUnits &k)
	{
		return NumberWithUnits(k);
	}

	NumberWithUnits operator--(NumberWithUnits &k, int)
	{
		return NumberWithUnits(k);
	}

	NumberWithUnits operator*(const double mispar, const NumberWithUnits &c)
	{
		return NumberWithUnits(c.number * mispar, c.str);
	}

	NumberWithUnits operator*(const NumberWithUnits &c, const double mispar)
	{
		return NumberWithUnits(c.number * mispar, c.str);
	}

	std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c)
	{
		return os;
	}

	std::istream &operator>>(std::istream &is, NumberWithUnits &c)
	{
		string s;
		is >> c.number >> s >> c.str;
		return is;
	}

};
