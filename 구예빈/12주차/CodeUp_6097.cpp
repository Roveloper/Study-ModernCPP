#include <iostream>
using namespace std;

int main()
{
    //2���� �迭�� �Է��� �޴´�.
    int a[20][20];
    for (int i = 1; i <= 19; i++) {
        for (int j = 1; j <= 19; j++) {
            cin >> a[i][j];
        }
    }

    // ��ǥ ������ �Է� �޴´�.
    int n = 0;
    cin >> n;

    // ��ǥ�� �Է� �޴´�.
    for (int k = 1; k <= n; k++) {
        int x, y = 0;
        cin >> x;
        cin >> y;
        for (int i = 1; i <= 19; i++) {
            if (a[x][i] == 0) { a[x][i] = 1; }
            else { a[x][i] = 0; }
        }
        for (int i = 1; i <= 19; i++) {
            if (a[i][y] == 0) { a[i][y] = 1; }
            else { a[i][y] = 0; }
        }

    }

    // ����Ѵ�.
    for (int i = 1; i <= 19; i++) {
        for (int j = 1; j <= 19; j++) {
            cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
}