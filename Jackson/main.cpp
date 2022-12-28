#include "date.hpp"

int main() {
    Date Birthday;
    Birthday.SetDate(1992, 01, 16);
    Birthday.AddYear(100);
    Birthday.ShowDate();

    return 0;
}