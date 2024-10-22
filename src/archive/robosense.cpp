// 2024.07.31 速腾聚创

/**
 * @brief 找到存在的问题并考察八股
 * 
 */

class Box
{
public:
  // explicit 关键字，防止隐式类型转换和复制初始化
  // Box b1(1, 2); // OK
  // Box b2 = 1; // Error
  explicit Box(const Eigen::Vector2f &center, const Eigen::Vector2f &size) : center_(center), size_(size) {}

  // virtual 关键字，表示该函数是虚函数
  // const 修饰成员函数，表示该函数不会修改成员变量
  // noexcept 修饰成员函数，表示该函数不会抛出异常
  virtual float area() const noexcept
  {
    float val;
    val = size_.x() * size_.y();
    // 无返回值
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
      : Box(center, size), height_(height) {}

  // return 4 points, as ld, lt, rt, rd. (r-right)(t-top)(l-left)(d-down)
  std::vector<Eigen::Vector2f> get_corners() const
  {
    std::vector<Eigen::Vector2f> corners;
    // 预留了空间，但是未初始化
    corners.reserve(4);

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
    // 未初始化
    float val;
    val += 2 * size_.x() * size_.y();
    val += 2 * size_.x() * height_;
    val += 2 * size_.y() * height_;
    return val;
  }

private:
    float height_{0.f};
};
