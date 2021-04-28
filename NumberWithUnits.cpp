
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;
const double EPS = 0.001;
//static map<string, map<string, double>> MapUnity;
namespace ariel
{
    static map<string, map<string, double>> MapUnity;
    
   // check if the unit is in the map 
    NumberWithUnits::NumberWithUnits(double number, const string &str)
    {
       if (MapUnity.count(str) == 0)
        {
            throw invalid_argument("unit doesnt exist "+str);
        }
        //MapUnity.at(str);
	  (*this).number = number;
	  (*this).str =str;
    }


    double changer(double num,const string &first ,const string &last)
    {
        if (first == last)
            return num;
	
        if(MapUnity[first].find(last) == MapUnity[first].end()){
		   throw invalid_argument{"not the same family of values!"};
	  }
        return num * MapUnity.at(first).at(last);
        }
       
    }




  	void NumberWithUnits::read_units(ifstream &units_file){
        string u1 = " ";
	  string n1 = " ";
	  string u2 = " ";
	  string n2 = " ";
	  string s1 = " ";
        double v1=0;
	  double v2=0;

        while (units_file >> v1 >> u1 >> s1 >> v2 >> u2)
        {
            MapUnity[u1][u2] = v2;
            MapUnity[u2][u1] = 1 / v2;

		for (auto &map : MapUnity[u2]){
            MapUnity[u1][map.first] = MapUnity[u1][u2] * map.second;
            MapUnity[map.first][u1] = 1 / (MapUnity[u1][u2] * map.second);
		}

		for (auto &mapy : MapUnity[n1]){
            MapUnity[n2][mapy.first] = MapUnity[n2][n1] * mapy.second;
            MapUnity[mapy.first][n2] = 1 / (MapUnity[n2][n1] * mapy.second);
        }

	  }
    }

   
    NumberWithUnits operator+(const NumberWithUnits &n) 
    {
       //(*n).number += changer(n.number, n.str, (*n).str);
        return NumberWithUnits(n.number, n.str);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        (*this).number += changer(n.number, n.str, this->str);
        return *this;
    }

   
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n) 
    {
        return NumberWithUnits(this->number - (changer(n.number, n.str, this->str)), this->str);
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
    }

    
    std::ostream& operator<<(std::ostream &os, const NumberWithUnits &c)
    {
        os << c.number << "[" << c.str << "]";
        return os;
    }

    

    istream &operator>>(std::istream &is, NumberWithUnits &n) {
        double num=0;
        std::string type;
        char c=' ';
        is >> num;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            is>>c;
        }
       if(MapUnity[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        n.number=num;
        n.str=type;
        return is;
    }

};
