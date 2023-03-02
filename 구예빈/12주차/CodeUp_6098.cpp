#include <iostream>
using namespace std;


// int�� 2���� �迭 ���� �Ҵ��ϴ� �Լ�
int** alloc2Darr(int w, int h) {
    if (w <= 0 || h <= 0) return NULL;
    int** a = new int* [h];
    for (int i = 0; i < h; i++) {
        a[i] = new int[w];
    }
    return a;
}

// int�� 2���� �迭 ���� �Ҵ� �����ϴ� �Լ�
void free2DArr(int** a, int w, int h = 0) {
    if (a != NULL) {
        for (int i = 0; i < h; i++)
            delete[] a[i];
        delete[] a;
    }
}

int main()
{
    // ���� w, ���� h�� �Է� �޴´�.
    int h, w = 0;
    cin >> h >> w;

    // 2���� �迭 a ����
    int** a;
    // 2���� �迭 a �Ҵ�
    a = alloc2Darr(w, h);


    //for (int i = 0; i < h; i++)
    //{
    //    for (int j = 0; j < w; j++)
    //    {
    //        a[i][j] = 0;
    //        cout << a[i][j];
    //    }
    //    cout << endl;
    //}

    // ���� ������ �Է� �޴´�.
    int n = 0;
    cin >> n;


    // �� ������ ������ �Է� �޴´�.
    for (int k = 1; k <= n; k++) {
        int l, d, x, y = 0;
        cin >> l >> d >> x >> y;

        x = x - 1;
        y = y - 1;

        // d�� 0�̸� ���η� �����Ƿ� h�� ����
        if (d == 0) {
            for (int i = 0; i < l; i++) {
                a[x][y + i] = 1;
            }
        }
        // d�� 1�̸� ���η� �����Ƿ� w�� ����
        else {
            for (int i = 0; i < l; i++) {
                a[x + i][y] = 1;
            }
        }
    }

    // ����Ѵ�.
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }

    // 2���� �迭 a �Ҵ� ����
    free2DArr(a, w, h);

    return 0;
}