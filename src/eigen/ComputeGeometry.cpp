#include <bits/stdc++.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>


class BoundingBox {
public:
    double rt_x, rt_y;
    double lt_x, lt_y;

    BoundingBox(double x1, double y1, double x2, double y2) :
        lt_x(x1), lt_y(y1), rt_x(x2), rt_y(y2) {
            std::cout << "Construct BoundingBox" << std::endl
                      << "left bottom positon: " << lt_x << " " << lt_y << std::endl
                      << "right top positon: " << rt_x << " " << rt_y << std::endl;
        }
    
    BoundingBox() : rt_x(0), rt_y(0), lt_x(0), lt_y(0) {
        std::cout << "Construct BoundingBox with default intialization" << std::endl;
    }

    virtual ~BoundingBox() {
        std::cout << "Destruct BoundingBox" << std::endl;
    }

    virtual void print() {
        std::cout << "left bottom positon: " << lt_x << " " << lt_y << std::endl
                  << "right top positon: " << rt_x << " " << rt_y << std::endl;
    }

};

class BoundingBox3D : public BoundingBox {
public:
    double rt_z, lt_z;
    BoundingBox3D(double x1, double y1, double z1, double x2, double y2, double z2) :
        BoundingBox(x1, y1, x2, y2), lt_z(z1), rt_z(z2) {
            std::cout << "Construct BoundingBox3D" << std::endl
                      << "left bottom positon: " << lt_x << " " << lt_y << " " << lt_z << std::endl
                      << "right top positon: " << rt_x << " " << rt_y << " " << rt_z << std::endl;
        }
    
    BoundingBox3D() : BoundingBox(), rt_z(0), lt_z(0) {
        std::cout << "Construct BoundingBox3D with default intialization" << std::endl;
    }

    virtual ~BoundingBox3D() {
        std::cout << "Destruct BoundingBox3D" << std::endl;
    }
    
    virtual void print() {
        std::cout << "left bottom positon: " << lt_x << " " << lt_y << " " << lt_z << std::endl
                  << "right top positon: " << rt_x << " " << rt_y << " " << rt_z << std::endl;
    }

};

// 两直线A{l, r} B{l, r} 
// 不相交情况  A.l > B.r || A.r < B.l 
// 相交情况    A.l <= B.r && A.r >= B.l
// 推广到2D AABB x,y轴均相交

inline bool isIntersectionBoundingBox(const BoundingBox &b1, const BoundingBox &b2) {
    return b1.lt_x <= b2.rt_x && b1.rt_x >= b2.lt_x 
        && b1.lt_y <= b2.rt_y && b1.rt_y >= b2.lt_y;
}

inline bool isIntersectionBoundingBox3D(const BoundingBox3D &b1, const BoundingBox3D &b2) {
    return b1.lt_x <= b2.rt_x && b1.rt_x >= b2.lt_x 
        && b1.lt_y <= b2.rt_y && b1.rt_y >= b2.lt_y 
        && b1.lt_z <= b2.rt_z && b1.rt_z >= b2.lt_z;
}

int main() {
    BoundingBox bbox2D1(1.3, 2.3, 5.5, 5.6);
    BoundingBox bbox2D2(3.4, 2.4, 6.6, 7.8);

    BoundingBox3D* bbox3DPtr1 = new BoundingBox3D(1.3, 2.3, 3.4, 5.5, 5.6, 6.7);
    BoundingBox3D* bbox3DPtr2 = new BoundingBox3D(10.2, 15.6, 18.8, 40.2, 32.1, 50.0);

    std::cout << "----------------" << std::endl << "2D Condition" << std::endl;
    std::cout << "2D BoundingBox 1: " << std::endl;
    bbox2D1.print();
    std::cout << "2D BoundingBox 2: " << std::endl;
    bbox2D2.print();
    // BoundingBox intersection
    if (isIntersectionBoundingBox(bbox2D1, bbox2D2)) {
        std::cout << "Intersection" << std::endl;
    } else {
        std::cout << "No Intersection" << std::endl;
    }

    std::cout << std::endl << "----------------" << std::endl << "3D Condition" << std::endl;
    std::cout << "3D BoundingBox 1: " << std::endl;
    bbox3DPtr1->print();
    std::cout << "3D BoundingBox 2: " << std::endl;
    bbox3DPtr2->print();
    
    if (isIntersectionBoundingBox3D(*bbox3DPtr1, *bbox3DPtr2)) {
        std::cout << "Intersection" << std::endl;
    } else {
        std::cout << "No Intersection" << std::endl;
    }

    delete bbox3DPtr1;
    delete bbox3DPtr2;

    // is point on the segment
    std::cout << std::endl << "----------------" << std::endl << "Is point on the segment" << std::endl;

    auto isLineOnSegment = [&](Eigen::Vector3d test, Eigen::Vector3d start, Eigen::Vector3d end) -> bool {

    };

    // point to segment distance
    std::cout << std::endl << "----------------" << std::endl << "Point to segment distance" << std::endl;




    return 0;
}