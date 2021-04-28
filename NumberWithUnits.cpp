#include <iostream>
#include "NumberWithUnits.hpp"
#include <fstream>
#include <map>

using namespace std;
const double EPS = 0.001;

namespace ariel
{
    static map<string, map<string, double>> MapUnit;
    
   // check if the unit is in the map 
    NumberWithUnits::NumberWithUnits(double number, const string &str)
    {
       if (MapUnit.count(str) == 0)
        {
            throw invalid_argument("unit doesnt exist "+str);
        }
        //MapUnit.at(str);
	  (*this).number = number;
	  (*this).str =str;
    }


    double changer(double num,const string &first ,const string &last)
    {
        if (first == last)
            return num;
	string t = num * MapUnit.at(first).at(last);
        if(MapUnit[first].find(last) == MapUnit[first].end()){
		   throw invalid_argument{"not the same family of values!"};
	  }
        return num * MapUnit.at(first).at(last);
        }
       
    }


    void insertUnit(const string& unit1, const string& unit2)
    {
        for (auto &map : MapUnit[unit2])
        {
            double num = MapUnit[unit1][unit2] * map.second;
            MapUnit[unit1][map.first] = num;
            MapUnit[map.first][unit1] = 1 / num;
        }
    }

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string u1;
	  string u2;
	  string s1;
        double v1=0;
	  double v2=0;

        while (units_file >> v1 >> u1 >> s1 >> v2 >> u2)
        {
            MapUnit[u1][u2] = v2;
            MapUnit[u2][u1] = 1 / v2;
            insertUnit(u1, u2);
            insertUnit(u2, u1);
        }
    }

    //================ + ====================//

   
    NumberWithUnits operator+(const NumberWithUnits &n) 
    {
       (*this).number += changer(n.number, n.str, this->str);
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        (*this).number += changer(n.number, n.str, this->str);
        return *this;
    }

   
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n) const
    {
        double numCheck = changer(n.number, n.str, this->str);
        return NumberWithUnits(this->number - numCheck, this->str);
    }
    NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        this->number -= changer(n.number, n.str, this->str);
        return NumberWithUnits((*this).number -=);
    }


    bool NumberWithUnits::operator>(const NumberWithUnits &n) 
    {
        double compare = changer(n.number, n.str, this->str);
        return (this->number > compare);
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &n) 
    {
        return !(*this < n);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &n)
    {
        return (this->number < changer(n.number, n.str, this->str));
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &n)
    {
        return !(*this > n);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &n, const NumberWithUnits &k) 
    {
        return (abs(this->number-changer(n.number, n.str, this->str))<=EPS);
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &n) 
    {
        return !(*this == n);
    }


    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {

        return NumberWithUnits((*this).number++, this->str);
    }

    NumberWithUnits& NumberWithUnits::operator--()
    {
        --(this->number);
        return *this; 
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(this->number--, this->str);
    }




    NumberWithUnits operator*(double d, const NumberWithUnits &n)
    {
        return NumberWithUnits(n.number * d, n.str);
    }

    NumberWithUnits NumberWithUnits::operator*(double n) 
    {
        return n*(*this);

    std::ostream& operator<<(std::ostream &os, const NumberWithUnits &c)
    {
        os << c.number << "[" << c.str << "]";
        return os;
    }

    }

    istream &operator>>(istream &is, NumberWithUnits &n) {
        double num=0;
        string type;
        char c=' ';
        is >> num;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            is>>c;
        }
       if(MapUnit[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        n.number=num;
        n.str=type;
        return is;
    }

};
