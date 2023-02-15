#include "date.hpp"

Date::Date() :
    year_(0),
    month_(0),
    day_(0)
{}

Date::~Date() {
    
}

int Date::GetLastDay() {
    switch(month_) {
        default: {
            return 31;
        }

        case 4:
        case 6:
        case 9:
        case 11:
        {
            return 30;
        }

        case 2:
        {
            if (true == this->IsLeapYear()) {
                return 29;
            }
            else {
                return 28;
            }
        }

    }
}

int Date::GetLastDay(int month) {
    switch(month) {
        default :
        {
            return 31;
        }

        case 4:
        case 6:
        case 9:
        case 11:
        {
            return 30;
        }

        case 2:
        {
            if (true == this->IsLeapYear()) {
                return 29;
            }
            else {
                return 28;
            }
        }

    }
}

bool Date::IsLeapYear() {
    if (year_ % 400 == 0) {
        return true;
    }
    if (year_ % 100 == 0) {
        return false;
    }
    if (year_ % 4 == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Date::IsValidDate(int year, int month, int day) {
    if (year < 1) {
        return false;
    }
    if (month > 12 || month < 1) {
        return false;
    }
    if (day > GetLastDay(month) || day < 1) {
        return false;
    }
    return true;
}

void Date::SetDate(int year, int month, int day) {
    if (true == IsValidDate(year, month, day)) {
        year_ = year;
        month_ = month;
        day_ = day;
    }
    else {
        std::cerr << "Invalid Date Set Requested, Please Check the Date" << std::endl;
    }
}

void Date::AddYear(int inc) {
    if (inc < 0) {
        std::cerr << "Invalid increase, Please insert positive only" << std::endl;
    }
    if (true == IsValidDate(year_ + inc, month_, day_)) {
        year_ += inc;
    }
}

void Date::AddMonth(int inc) {
    if (inc < 0) {
        std::cerr << "Invalid increase, Please insert positive only" << std::endl;
    }
    int temp_year = year_;
    int temp_month = month_ + inc;
    
    while (temp_month > 12) {
        temp_year += 1;
        temp_month -= 12;
    }
    if (true == IsValidDate(temp_year, temp_month, day_)) {
        year_ = temp_year;
        month_ = temp_month;
    }
}

void Date::AddDay(int inc) {
    if (inc < 0) {
        std::cerr << "Invalid increase, Please insert positive only" << std::endl;
    }
    int temp_year = year_;
    int temp_month = month_;
    int temp_day = day_ + inc;

    while (temp_day > GetLastDay(temp_month)) {
        temp_day -= GetLastDay(temp_month);
        temp_month += 1;
        if (temp_month > 12) {
            temp_month -= 12;
            temp_year += 1;
        }
    }
    if (true == IsValidDate(temp_year, temp_month, day_)) {
        year_ = temp_year;
        month_ = temp_month;
        day_ = temp_day;
    }
}

void Date::ShowDate() {
    std::cout << year_ << "-" << month_ << "-" << day_ << std::endl;
}