#include <eigen3/Eigen/Dense>
#include <iostream>

void schurComplement(const Eigen::MatrixXd& H, const Eigen::VectorXd& b) {
    // 假设 H 是 9x9 矩阵，前3x3是A，后6x6是D
    Eigen::Matrix3d A = H.topLeftCorner<3, 3>();
    Eigen::MatrixXd B = H.topRightCorner(3, 6);
    Eigen::MatrixXd C = H.bottomLeftCorner(6, 3);
    Eigen::MatrixXd D = H.bottomRightCorner<6, 6>();

    Eigen::Vector3d b1 = b.head<3>();
    Eigen::VectorXd b2 = b.tail<6>();

    // 计算舒尔补
    Eigen::MatrixXd S = D - C * A.inverse() * B;
    Eigen::VectorXd b_schur = b2 - C * A.inverse() * b1;

    // 解舒尔补方程
    Eigen::VectorXd x2 = S.colPivHouseholderQr().solve(b_schur);

    // 回代求解x1
    Eigen::Vector3d x1 = A.inverse() * (b1 - B * x2);

    // 输出结果
    std::cout << "x1:\n" << x1 << std::endl;
    std::cout << "x2:\n" << x2 << std::endl;
}

int main() {
    Eigen::MatrixXd H = Eigen::MatrixXd::Random(9, 9);
    H.topLeftCorner<3, 3>() = Eigen::Matrix3d::Identity(); // 设置A为单位矩阵以简化
    H.bottomRightCorner<6, 6>() = Eigen::MatrixXd::Identity(6, 6); // 设置D为单位矩阵以简化
    Eigen::VectorXd b = Eigen::VectorXd::Random(9);

    schurComplement(H, b);

    return 0;
}