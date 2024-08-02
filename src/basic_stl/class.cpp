// 2024.07.31 速腾聚创

#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>

class Box
{
public:
    // explicit 关键字，防止隐式类型转换和复制初始化
    // Box b1(1, 2); // OK
    // Box b2 = 1; // Error
    explicit Box(const Eigen::Vector2f &center, const Eigen::Vector2f &size) : center_(center), size_(size) 
    {
        std::cout << "Box constructor" << std::endl;
    }

    // virtual 关键字，表示该函数是虚函数
    // const 修饰成员函数，表示该函数不会修改成员变量
    // noexcept 修饰成员函数，表示该函数不会抛出异常
    virtual float area() const noexcept
    {
        std::cout << "Calculate Box area" << std::endl;
        float val;
        val = size_.x() * size_.y();
        return val;
    }

    
    // ~Box() 
    // -> 使用基类指针释放派生类对象时，如果基类的析构函数不是虚函数，那么只会调用基类的析构函数，而不会调用派生类的析构函数
    virtual ~Box()
    {
        std::cout << "Box destructor" << std::endl;
    }

protected:
    Eigen::Vector2f center_;
    Eigen::Vector2f size_;
};

class Cube : public Box
{
public:
    explicit Cube(const Eigen::Vector2f &center, const Eigen::Vector2f &size, float height, int id)
        : Box(center, size), height_(height), id_(id) 
        {
            std::cout << "Cube constructor, ID: " << id_ << std::endl;
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
        std::cout << "Calculate Cube area, ID: " << id_ << std::endl;
        float val = 0.f;
        val += 2 * size_.x() * size_.y();
        val += 2 * size_.x() * height_;
        val += 2 * size_.y() * height_;
        return val;
    }

    virtual ~Cube()
    {
        std::cout << "Cube destructor, ID: " << id_ << std::endl;
    }

private:
    float height_{0.f};
    int id_{0};
};


int main()
{
    std::cout << "Class example" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Construct " << std::endl;
    Eigen::Vector2f center(0.f, 0.f);
    Eigen::Vector2f size(1.f, 1.f);
    float height = 1.f;
    Cube cube(center, size, height, 0);
    float cubeArea = cube.area();
    std::cout << "Cube area: " << cubeArea << std::endl;
    auto corners = cube.get_corners();
    for (auto corner : corners)
    {
        std::cout << "Cube corners: " << corner.transpose() << std::endl;
    }

    std::cout << "----------------" << std::endl;
    std::cout << "Destruct " << std::endl;
    Box* box = new Cube(center, size, height, 1);
    // malloc 分配内存不能初始化对象，返回void*后进行类型转换
    // Box* box1 = (Box*)malloc(sizeof(Cube));
    float boxArea = box->area();
    std::cout << "Box area: " << boxArea << std::endl;
    delete box;

    return 0;
}

