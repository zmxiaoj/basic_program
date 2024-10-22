// 2024.08.10 oppo code1
#include<bits/stdc++.h>

using namespace std;

/**
 * @brief 判断质数，卡时间，过90%
 * 
 * @return int 
 */
int main()
{
    long long x = 0;
    while (cin >> x) {
        cout << x << endl;
    }

    for (long long i = x + 1; ; i++) {
        bool is_prime = true;
        for (long long j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}