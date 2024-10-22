#include<bits/stdc++.h>

class KalmanFilter {
public:
    KalmanFilter(double a, double b, double processVariance, double measurementVariance)
        : a_(a), b_(b), p_(1.0), processVariance_(processVariance), measurementVariance_(measurementVariance) {}

    void update(double x, double y) {
        // Prediction
        double prediction = a_ * x + b_;
        double predictionError = y - prediction;

        // Update
        double gain = p_ * x / (x * x * p_ + measurementVariance_);
        a_ += gain * predictionError;
        b_ += gain * (y - prediction - a_ * x);
        p_ = (1 - gain * x) * p_ + processVariance_;
    }

    double getA() const { return a_; }
    double getB() const { return b_; }

private:
    double a_, b_, p_;
    double processVariance_, measurementVariance_;
};

int main() {
    // Simulate some data
    std::vector<std::pair<double, double>> data = {
        {1, 2},
        {2, 4},
        {3, 6},
        {4, 8},
        // Add more data points as needed
    };

    KalmanFilter kf(0, 0, 0.01, 0.1); // Initial guesses for a, b and variances

    for (const auto& point : data) {
        double x = point.first;
        double y = point.second;

        kf.update(x, y);

        std::cout << "Estimated a: " << kf.getA() << ", Estimated b: " << kf.getB() << std::endl;
    }

    return 0;
}