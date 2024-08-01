// 2024.07.31 速腾聚创

#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>

class Box
{
public:
    // explicit 关键字，防止隐式类型转换和复制初始化
    // Box b1(1, 2); // OK
    // Box b2 = 1; // Error
    explicit Box(const Eigen::Vector2f &center, const Eigen::Vector2f &size) : center_(center), size_(size) {
        std::cout << "Box constructor" << std::endl;
    }

    // virtual 关键字，表示该函数是虚函数
    // const 修饰成员函数，表示该函数不会修改成员变量
    // noexcept 修饰成员函数，表示该函数不会抛出异常
    virtual float area() const noexcept
    {
        float val;
        val = size_.x() * size_.y();
        return val;
    }

protected:
    Eigen::Vector2f center_;
    Eigen::Vector2f size_;
};

class Cube : public Box
{
public:
    explicit Cube(const Eigen::Vector2f &center, const Eigen::Vector2f &size, float height)
        : Box(center, size), height_(height) {
            std::cout << "Cube constructor" << std::endl;
        }

    // return 4 points, as ld, lt, rt, rd. (r-right)(t-top)(l-left)(d-down)
    std::vector<Eigen::Vector2f> get_corners() const
    {
        std::vector<Eigen::Vector2f> corners;
        corners.resize(4, Eigen::Vector2f::Zero());

        corners[0] = center_ + Eigen::Vector2f(-size_.x() / 2.f, -size_.y() / 2.f);
        corners[1] = center_ + Eigen::Vector2f(-size_.x() / 2.f, size_.y() / 2.f);
        corners[2] = center_ + Eigen::Vector2f(size_.x() / 2.f, size_.y() / 2.f);
        corners[3] = center_ + Eigen::Vector2f(size_.x() / 2.f, -size_.y() / 2.f);
        return corners;
    }

    virtual float area() const noexcept
    {
        // 显示调用基类的 area 函数
        // float val = Box::area();
        float val = 0.f;
        val += 2 * size_.x() * size_.y();
        val += 2 * size_.x() * height_;
        val += 2 * size_.y() * height_;
        return val;
    }

private:
    float height_{0.f};
};


int main()
{
    Eigen::Vector2f center(0.f, 0.f);
    Eigen::Vector2f size(1.f, 1.f);
    float height = 1.f;
    Cube cube(center, size, height);
    float cubeArea = cube.area();
    std::cout << "Cube area: " << cubeArea << std::endl;
    auto corners = cube.get_corners();
    for (auto corner : corners)
    {
        std::cout << "Cube corners: " << corner.transpose() << std::endl;
    }
    return 0;
}

