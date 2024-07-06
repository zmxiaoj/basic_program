#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigen>


static bool insideTriangle(float x, float y, const Eigen::Vector4f* _v)
{
    Eigen::Vector3f v[3];
    for(int i = 0; i < 3; i++)
        v[i] = {_v[i].x(), _v[i].y(), 1.0}; // 将4D向量转为3D向量
    
    Eigen::Vector3f f0, f1, f2;
    f0 = v[1].cross(v[0]); // 计算边(v1, v0)的法向量
    f1 = v[2].cross(v[1]); // 计算边(v2, v1)的法向量
    f2 = v[0].cross(v[2]); // 计算边(v0, v2)的法向量

    Eigen::Vector3f p(x, y, 1.0); // 将点p表示为3D向量
    
    // 通过点积判断点p是否在三角形内
    if ((p.dot(f0) * f0.dot(v[2]) > 0) && 
        (p.dot(f1) * f1.dot(v[0]) > 0) && 
        (p.dot(f2) * f2.dot(v[1]) > 0))
        return true;

    return false;
}


int main()
{
    std::cout << "2D Vector Operations\n";
    Eigen::Vector2f v1{1.0f, 0.0f},
                    v2{0.0f, 1.0f};
    // 2d vector 不能进行cross操作
    // std::cout << "v1 cross v2:\n " << v1.cross(v2) << std::endl;
    // std::cout << "v2 cross v1:\n " << v2.cross(v1) << std::endl;

    std::cout << "v1 dot v2:\n" << v1.dot(v2) << std::endl;
    std::cout << "v2 dot v1:\n" << v2.dot(v1) << std::endl;

    std::cout << "3D Vector Operations\n";
    Eigen::Vector3f v3{1.0f, 0.0f, 0.0f},
                    v4{0.0f, 1.0f, 0.0f};
    std::cout << "v3^T:\n" << v3.transpose() << std::endl
              << "v4^T:\n" << v4.transpose() << std::endl;
    std::cout << "v3 cross v4:\n" << v3.cross(v4).transpose() << std::endl;
    std::cout << "v4 cross v3:\n" << v4.cross(v3).transpose() << std::endl;

    std::cout << "v3 dot v4:\n" << v3.dot(v4) << std::endl;
    std::cout << "v4 dot v3:\n" << v4.dot(v3) << std::endl;

    Eigen::Vector4f v[3] = {Eigen::Vector4f(0.0, 0.0, 1.0, 1.0),
                            Eigen::Vector4f(1.0, 0.0, 1.0, 1.0),
                            Eigen::Vector4f(0.0, 1.0, 1.0, 1.0)};

    std::cout << "Test insideTriangle\n";
    Eigen::Vector2f p{0.5f, 0.5f};
    std::cout << "Point p " << p.transpose() << " is " << (insideTriangle(p.x(), p.y(), v) ? "inside" : "outside") << std::endl;
    p = {0.3f, 0.3f};
    std::cout << "Point p " << p.transpose() << " is " << (insideTriangle(p.x(), p.y(), v) ? "inside" : "outside") << std::endl;
    p = {0.1f, 0.3f};
    std::cout << "Point p " << p.transpose() << " is " << (insideTriangle(p.x(), p.y(), v) ? "inside" : "outside") << std::endl;
    p = {1.0f, 1.0f};
    std::cout << "Point p " << p.transpose() << " is " << (insideTriangle(p.x(), p.y(), v) ? "inside" : "outside") << std::endl;

    return 0;
}