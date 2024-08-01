#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>

// Define a point in 3D space
struct Point3D {
    float x, y, z;
};

// Function to fit a plane to three points
void fitPlane(const Point3D& p1, const Point3D& p2, const Point3D& p3, float& a, float& b, float& c, float& d) {
    // Plane equation: ax + by + cz + d = 0
    float v1x = p2.x - p1.x;
    float v1y = p2.y - p1.y;
    float v1z = p2.z - p1.z;
    float v2x = p3.x - p1.x;
    float v2y = p3.y - p1.y;
    float v2z = p3.z - p1.z;
    
    a = v1y * v2z - v1z * v2y;
    b = v1z * v2x - v1x * v2z;
    c = v1x * v2y - v1y * v2x;
    d = -(a * p1.x + b * p1.y + c * p1.z);
}

// Function to compute the distance from a point to a plane
float pointToPlaneDistance(const Point3D& p, float a, float b, float c, float d) {
    return std::fabs(a * p.x + b * p.y + c * p.z + d) / std::sqrt(a * a + b * b + c * c);
}

// RANSAC algorithm for plane fitting
void ransacPlane(const std::vector<Point3D>& points, float& best_a, float& best_b, float& best_c, float& best_d, int maxIterations, float distanceThreshold) {
    int bestInliersCount = 0;
    
    std::srand(std::time(0)); // Seed for random number generator

    for (int i = 0; i < maxIterations; ++i) {
        // Randomly select 3 points
        int idx1 = std::rand() % points.size();
        int idx2 = std::rand() % points.size();
        int idx3 = std::rand() % points.size();
        
        // Ensure the points are unique
        while (idx2 == idx1) idx2 = std::rand() % points.size();
        while (idx3 == idx1 || idx3 == idx2) idx3 = std::rand() % points.size();
        
        Point3D p1 = points[idx1];
        Point3D p2 = points[idx2];
        Point3D p3 = points[idx3];
        
        // Fit plane to the three points
        float a, b, c, d;
        fitPlane(p1, p2, p3, a, b, c, d);
        
        // Count inliers
        int inliersCount = 0;
        for (const auto& p : points) {
            float distance = pointToPlaneDistance(p, a, b, c, d);
            if (distance < distanceThreshold) {
                ++inliersCount;
            }
        }
        
        // Update best model if current model has more inliers
        if (inliersCount > bestInliersCount) {
            bestInliersCount = inliersCount;
            best_a = a;
            best_b = b;
            best_c = c;
            best_d = d;
        }
    }
}

int main() {
    // Example usage
    std::vector<Point3D> points = {
        {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4},
        {0, 1, 2}, {1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}
    };

    float best_a, best_b, best_c, best_d;
    int maxIterations = 1000;
    float distanceThreshold = 0.1;

    ransacPlane(points, best_a, best_b, best_c, best_d, maxIterations, distanceThreshold);

    std::cout << "Best plane parameters: "
              << "a = " << best_a << ", "
              << "b = " << best_b << ", "
              << "c = " << best_c << ", "
              << "d = " << best_d << std::endl;

    return 0;
}


