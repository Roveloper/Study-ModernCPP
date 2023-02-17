#include <iostream>

int main()
{
    {
        int a = 10;
        int b = 20;
        int c = 30;
        int *ptr_a = new int;
        ptr_a = &a; // 순수한 누수
    }

    return 0;
}