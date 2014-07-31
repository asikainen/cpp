/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "calendar.hpp"
/*
  Vuosi on karkausvuosi,jos se on neljÅ‰llÅ‰ jaollinen. Kuitenkin
  sadalla jaollisista vuosista vain 400:lla jaolliset ovat 
  karkausvuosia. 
*/

// Static consts.
static const int firstYear = 0, lastYear =2100, months = 12;


// Main
int main(int argc, char *argv[])
{
  // Check arguments
  if (argc != 5)
    {
      cout << "# usage: calendar.exe day month year ndays" << endl;
      return 1;
    }

  // Extract arguments
  const int day = atoi(argv[1]);
  const int month = atoi(argv[2]);
  const int year = atoi(argv[3]);
  const int ndays = atoi(argv[4]);

  // Allocate leap year and month arrays
  int *isLeap = new int[lastYear - firstYear + 1];
 // NOTE: index range daysInMonth[0-1][0-11] !!!
  int **daysInMonth = new int *[2];
  for (int m=0; m<2; m++)
    daysInMonth[m] = new int[months];

  // Initialize leap years
  GetLeapYears(isLeap);

  // Initialize days in months
  GetDaysInMonths(daysInMonth);

  // Checking
  CheckDate(day,month,year,daysInMonth,isLeap);

  // Build up the calendar starting from the given date
  BuildCalendar(day,month,year,ndays,daysInMonth,isLeap);

  // Free memory
  delete [] isLeap;
  for (int m=1; m>=0; m--)
    delete [] daysInMonth[m];
  delete [] daysInMonth;

  // Done
  return 0;
}

void GetLeapYears(int *isLeap)
{
  int year = firstYear;
  while (year <= lastYear)
    {
      if ( (year % 4 == 0) &&
	   ((year % 100 != 0) || (year % 400 == 0)) )
	isLeap[year] = 1;
      else
	isLeap[year] = 0;
      year++;
    }
}

void GetDaysInMonths(int **daysInMonth)
{
  // January -> July
  for (int m=0; m<7; m++)
    {
      if (m % 2 == 0)
	{
	  daysInMonth[0][m] = 31;
	  daysInMonth[1][m] = 31;
	}
      else
	{
	  daysInMonth[0][m] = 30;
	  daysInMonth[1][m] = 30;
	}
    }

  // August -> December
  for (int m=7; m<months; m++)
    {
      if (m % 2 == 1)
	{
	  daysInMonth[0][m] = 31;
	  daysInMonth[1][m] = 31;
	}
      else
	{
	  daysInMonth[0][m] = 30;
	  daysInMonth[1][m] = 30;
	}
    }

  // February separately
  daysInMonth[0][1] = 28;
  daysInMonth[1][1] = 29;
}

void BuildCalendar(const int day,const int month,const int year,
		   const int ndays,int **daysInMonth, int *isLeap)
{
  // Printing
  PrintDate(day,month,year,"Starting date");

  // Loop ndays starting from the given date
  int d = day, m = month, y = year;
  for (int n=0; n<ndays; n++)
    {
      // Increase day
      d++;
      
      // Check if within a month
      if (d > daysInMonth[isLeap[y]][m-1])
	{
	  // Reset day
	  d = 1;
	  // Increase month
	  m++;
	  // Check if within a year
	  if (m > months)
	    {
	      // Reset month
	      m = 1;
	      y++;
	      if (y > lastYear)
		{
		  cout << "# Increase lastYear" << endl;
		  exit(4);
		}
	    }
	}
    }

  // Printing
  PrintDate(d,m,y,"Final date");
}

void PrintLeapYears(int *isLeap)
{
  for (int y=firstYear; y<=lastYear; y++)
    if (isLeap[y] == 1)
      cout << y << " is a leap year." << endl;
}

void PrintDaysInMonths(int **daysInMonth)
{
  for (int m=0; m<months; m++)
    cout << m+1 << "\t" << daysInMonth[0][m]
	 << "\t" << daysInMonth[1][m] << endl;
}

void PrintDate(const int day,const int month,const int year, char *txt)
{
  // Pick up the date
  char d[3], m[3], y[5], tmp[3];
  sprintf(d,"%d",day);
  if (day < 10)
    {
      sprintf(tmp,"0");
      strcat(tmp,d);
      strcpy(d,tmp);
    }
  sprintf(m,"%d",month);
  if (month < 10)
    {
      sprintf(tmp,"0");
      strcat(tmp,m);
      strcpy(m,tmp);
    }
  sprintf(y,"%d",year);

  // Output
  cout << "# " << txt << ": "
       << d << "." << m << "." << y << endl;
}

void CheckDate(const int day,const int month,const int year,
	       int **daysInMonth, int *isLeap)
{
  if (year < firstYear || year > lastYear)
    {
      cout << "# year out of range!" << endl;
      exit(1);
    }
  if (month < 1 || month > 12)
    {
      cout << "# month out of range!" << endl;
      exit(2);
    }
  if ( day < 1 || day > daysInMonth[isLeap[year]][month-1])
    {
      cout << "# day out of range!" << endl;
      exit(3);
    }
}
