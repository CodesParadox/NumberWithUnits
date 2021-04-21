#pragma once // ifendef
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
namespace ariel
{

	class NumberWithUnits
	{
	private:
		double number;
		string str;

	public:
		NumberWithUnits(double number, const string &str);

		double getNumber() const { return number; }
		string getstr() const { return str; }
		static void read_units(std::ifstream &units_file);
		/*  */
		friend NumberWithUnits operator+(const NumberWithUnits &k);
		friend NumberWithUnits operator+(const NumberWithUnits &k, const NumberWithUnits &i);
		friend NumberWithUnits operator+=(NumberWithUnits &k, const NumberWithUnits &i);
		/*  */
		friend NumberWithUnits operator-(const NumberWithUnits &k);
		friend NumberWithUnits operator-(const NumberWithUnits &k, const NumberWithUnits &i);
		friend NumberWithUnits operator-=(NumberWithUnits &k, const NumberWithUnits &i);

		/*  */
		friend bool operator>(const NumberWithUnits &k, const NumberWithUnits &i);
		friend bool operator>=(const NumberWithUnits &k, const NumberWithUnits &i);
		friend bool operator<(const NumberWithUnits &k, const NumberWithUnits &i);
		friend bool operator<=(const NumberWithUnits &k, const NumberWithUnits &i);
		friend bool operator==(const NumberWithUnits &k, const NumberWithUnits &i);
		friend bool operator!=(const NumberWithUnits &k, const NumberWithUnits &i);
		/*  */
		friend NumberWithUnits operator++(NumberWithUnits &another1);
		friend NumberWithUnits operator++(NumberWithUnits &another1, int);
		friend NumberWithUnits operator--(NumberWithUnits &another1);
		friend NumberWithUnits operator--(NumberWithUnits &another1, int);

		/*  */
		friend NumberWithUnits operator*(const double n, const NumberWithUnits &c);
		friend NumberWithUnits operator*(const NumberWithUnits &c, const double n);
		friend NumberWithUnits operator*=(const double n, const NumberWithUnits &c);
		friend NumberWithUnits operator*=(const NumberWithUnits &c, const double n);

		friend std::ostream &operator<<(std::ostream &in, const NumberWithUnits &c);
		friend std::istream &operator>>(std::istream &out, NumberWithUnits &c);
	};
}