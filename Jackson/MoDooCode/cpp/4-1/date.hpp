#ifndef FCD6DD12_1A5E_4DA5_857C_2DC425667818
#define FCD6DD12_1A5E_4DA5_857C_2DC425667818

#include <iostream>

class Date 
{
	public:
		Date();
		~Date();
		void SetDate(int year, int month, int day);
		void AddDay(int inc);
		void AddMonth(int inc);
		void AddYear(int inc);

		void ShowDate();

		int GetLastDay();
		int GetLastDay(int month);
		bool IsLeapYear();
		bool IsValidDate(int year, int month, int day);

	private:
		int year_;
		int month_;
		int day_;
};

#endif /* FCD6DD12_1A5E_4DA5_857C_2DC425667818 */