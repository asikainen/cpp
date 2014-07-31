/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef calendar_hpp
#define calendar_hpp

void GetLeapYears(int *);
void PrintLeapYears(int *);
void GetDaysInMonths(int **);
void PrintDaysInMonths(const int, int **);
void BuildCalendar(const int, const int,const int,
		   const int, int **, int *);
void CheckDate(const int, const int,const int,
	       int **, int *);
void PrintDate(const int,const int,const int, char *txt = "Date");

#endif
