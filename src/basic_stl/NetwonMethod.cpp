#include<bits/stdc++.h>

double sqrt_newton(double n, double epsilon = 1e-7) {
    if (n < 0) {
        return NAN;  // 负数没有实数平方根
    }
    
    double x_n = n;  // 初始猜测值
    while (true) {
        double x_n1 = 0.5 * (x_n + n / x_n);  // 牛顿法迭代公式
        if (std::fabs(x_n1 - x_n) < epsilon) {
            return x_n1;
        }
        x_n = x_n1;
    }
}

int main() {
    double number = 16.0;
    double result = sqrt_newton(number);
    std::cout << "sqrt(" << number << ") ≈ " << result << std::endl;
    return 0;
}