//#pragma once // ifendef
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


namespace ariel
{

    class NumberWithUnits
    {
        private:
            double number;
            string str;  
    
        public:

            NumberWithUnits(double number , const string &str);
		~NumberWithUnits(){};
            static void read_units(ifstream &units_file);

		// In&Out
            friend ostream &operator<<(ostream& os, const NumberWithUnits& c);
        	friend istream &operator>>(istream& is, NumberWithUnits& n);
            //+++++++++++++++++++++/
            NumberWithUnits operator+()const ;
           friend NumberWithUnits operator+(const NumberWithUnits &n);
           friend NumberWithUnits operator+(const NumberWithUnits &n,const NumberWithUnits &k);

            //----------------------/
            friend NumberWithUnits operator-(const NumberWithUnits &n);
		 friend NumberWithUnits operator-(const NumberWithUnits &n,const NumberWithUnits &k);

            //Booleans//
          	friend bool operator>(const NumberWithUnits &n,const NumberWithUnits &k );
           	friend bool operator>=(const NumberWithUnits &n,const NumberWithUnits &k);
            friend bool operator<(const NumberWithUnits &n,const NumberWithUnits &k);
            friend bool operator<=(const NumberWithUnits &n,const NumberWithUnits &k);
            friend bool operator==(const NumberWithUnits &n,const NumberWithUnits &k);
            friend bool operator!=(const NumberWithUnits &n,const NumberWithUnits &k);
            NumberWithUnits &operator++();
            NumberWithUnits operator++(int);
            NumberWithUnits &operator--();
            NumberWithUnits operator--(int);
		NumberWithUnits &operator-=(const NumberWithUnits &n);
		NumberWithUnits &operator+=(const NumberWithUnits &n);
		NumberWithUnits &operator*(double n);
            friend NumberWithUnits operator*(const NumberWithUnits &n,double k);
            friend NumberWithUnits operator*(double k,const NumberWithUnits &n);

            
    };
}