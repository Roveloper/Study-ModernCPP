#include <iostream>
using namespace std;

int main()
{
    // 2���� �迭 a ����
    int a[10][10] = { 0, };

    // ������ ������ �Է� �޴´�.
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int t = 0;
            cin >> t;
            a[i][j] = t;
        }
        //cout << endl;
    }

    // ���̸� �̵� ��Ų��.
    int x = 1;
    int y = 1;

    while (1) {

        // �������� 2�̸� ������.
        if (a[1][1] == 2) {
            a[1][1] = 9;
            break;
        }
        // �������� 2�� �ƴϸ� 9�� �ٲ۴�.
        else { a[1][1] = 9; }

        // ���������� �� �� �ִٸ� ���������� �̵��Ѵ�.
        if (a[x][y + 1] == 0) {
            a[x][y + 1] = 9;
            y += 1;
        }
        // ���������� �� �� ���ٸ� �Ʒ��� Ž���غ���.
        else if (a[x][y + 1] == 1) {
            // �Ʒ��� �� �� ���� ��
            if (a[x + 1][y] == 0) {
                a[x + 1][y] = 9;
                x += 1;
            }
            // �Ʒ��� ���� ������ ��
            else if (a[x + 1][y] == 1) {
                break;
            }
            // �Ʒ��� ���̰� ���� ��
            else if (a[x + 1][y] == 2) {
                a[x + 1][y] = 9;
                break;
            }
            else { break; }
        }
        else if (a[x][y + 1] == 2) {
            a[x][y + 1] = 9;
            break;
        }
        else { break; }
    }

    //cout << endl << endl;
    // ����Ѵ�.
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << a[i][j];
            cout << " ";
        }
        //cout << endl;
        cout << endl;
    }

    return 0;
}