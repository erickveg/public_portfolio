/***********************************************************************
 * Header File:
 *    Table : The representation of a table
 * Author:
 *    Nathan Wood
 * Summary:
 *    A collection used for linear interpolation
 ************************************************************************/

#pragma once
#include <map>
using namespace std;

template <class T>
class Table
{
private:
   map<T, double> table;
   T d0; // The lower value from the table
   T d1; // The higher value from the table
   void getBounds(const T& d); //Gets d0 and d1

public:
   Table(map <T, double>& data) : table(data), d0(0.0), d1(0.0) {}
   //Table() : table(), d0(0.0), d1(0.0) {}
   double interpolate(const T& d); //Returns R
};

/******************************************
 * TABLE : GET BOUNDS
 * Get the bounds from the table
 *****************************************/
template <class T>
void Table<T>::getBounds(const T& d)
{
   d0 = -1.0;
   bool isFirst = false;
   for (auto mapValue : table)
   {
      if (d == mapValue.first)
      {
         d0 = 0.0;
         d1 = d;
         return;
      }

      if (d < mapValue.first || isFirst)
      {
         if (d0 == -1.0)
         {
            d0 = mapValue.first;
            isFirst = true;
         }
         else
         {
            d1 = mapValue.first;
            return;
         }
      }

      d0 = mapValue.first;
   }
}

/******************************************
 * TABLE : INTERPOLATE
 * Find the value outside a table given two points
 *****************************************/
template <class T>
double Table<T>::interpolate(const T& d)
{
   getBounds(d);
   double r0 = table[d0];
   double r1 = table[d1];
   if (d1 == d0)
      return double(r0);
   double returnValue = ((((r1 - r0) / (d1 - d0)) * (d - d0)) + r0);
   if (returnValue >= 0)
      return returnValue;
   return 0.0;
}