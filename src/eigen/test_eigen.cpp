#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigen>
#include<eigen3/Eigen/Dense>


static bool insideTriangle(float x, float y, const Eigen::Vector4f* _v)
{
    Eigen::Vector3f v[3];
    for(int i = 0; i < 3; i++)
        v[i] = {_v[i].x(), _v[i].y(), 1.0}; // 将4D向量转为3D向量
    
    Eigen::Vector3f f0, f1, f2;
    f0 = v[1].cross(v[0]); // 计算边(v1, v0)的法向量
    // std::cout << "f0: " << f0.transpose() << std::endl;
    f1 = v[2].cross(v[1]); // 计算边(v2, v1)的法向量
    // std::cout << "f1: " << f1.transpose() << std::endl;
    f2 = v[0].cross(v[2]); // 计算边(v0, v2)的法向量
    // std::cout << "f2: " << f2.transpose() << std::endl;

    Eigen::Vector3f p(x, y, 1.0); // 将点p表示为3D向量
    
    // 通过点积判断点p是否在三角形内
    if ((p.dot(f0) * f0.dot(v[2]) > 0) && 
        (p.dot(f1) * f1.dot(v[0]) > 0) && 
        (p.dot(f2) * f2.dot(v[1]) > 0))
        return true;

    return false;
}

static bool insideTriangle_mymethod(float x, float y, const Eigen::Vector4f* _v)
{
    Eigen::Vector3f v[3];
    for(int i = 0; i < 3; i++)
        v[i] = {_v[i].x(), _v[i].y(), 1.0}; // 将4D向量转为3D向量
    
    auto sign = [](Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c) -> int
    {
        float res = (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());

        float eps = 1e-7;
        if (res > eps)
            return 1;
        else if (res < -eps)
            return -1;
        else
            return 0;
    };

    Eigen::Vector3f p{x, y, 1.0f};
    // AB x AP
    int sign1 = sign(v[0], v[1], p);
    float s1 = (v[1] - v[0]).cross(p - v[0]).z();
    // BC x BP
    int sign2 = sign(v[1], v[2], p);
    float s2 = (v[2] - v[1]).cross(p - v[1]).z();
    // CA x CP
    int sign3 = sign(v[2], v[0], p);
    float s3 = (v[0] - v[2]).cross(p - v[2]).z();

    // return (sign1 == sign2 && sign2 == sign3);
    return (s1 > 0 && s2 > 0 && s3 > 0) || (s1 < 0 && s2 < 0 && s3 < 0);
}


int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed); // 设置种子
    // std::cout << "2D Vector Operations\n";
    // Eigen::Vector2f v1{1.0f, 0.0f},
    //                 v2{0.0f, 1.0f};
    // // 2d vector 不能进行cross操作
    // // std::cout << "v1 cross v2:\n " << v1.cross(v2) << std::endl;
    // // std::cout << "v2 cross v1:\n " << v2.cross(v1) << std::endl;

    // std::cout << "v1 dot v2:\n" << v1.dot(v2) << std::endl;
    // std::cout << "v2 dot v1:\n" << v2.dot(v1) << std::endl;

    // std::cout << "3D Vector Operations\n";
    // Eigen::Vector3f v3{1.0f, 0.0f, 0.0f},
    //                 v4{0.0f, 1.0f, 0.0f};
    // std::cout << "v3^T:\n" << v3.transpose() << std::endl
    //           << "v4^T:\n" << v4.transpose() << std::endl;
    // std::cout << "v3 cross v4:\n" << v3.cross(v4).transpose() << std::endl;
    // std::cout << "v4 cross v3:\n" << v4.cross(v3).transpose() << std::endl;

    // std::cout << "v3 dot v4:\n" << v3.dot(v4) << std::endl;
    // std::cout << "v4 dot v3:\n" << v4.dot(v3) << std::endl;

    Eigen::Vector4f v[3] = {Eigen::Vector4f(0.0, 0.0, 1.0, 1.0),
                            Eigen::Vector4f(1.0, 0.0, 1.0, 1.0),
                            Eigen::Vector4f(0.0, 1.0, 1.0, 1.0)};

    std::cout << "Test insideTriangle\n";
    Eigen::Vector2f p{0.5f, 0.5f};
    std::cout << "Point p " << p.transpose() << " is " 
              << "method1: " << (insideTriangle(p.x(), p.y(), v) ? "inside " : "outside ") 
              << "method2: " << (insideTriangle_mymethod(p.x(), p.y(), v) ? "inside " : "outside ") << std::endl;
    p = {0.3f, 0.3f};
    std::cout << "Point p " << p.transpose() << " is " 
              << "method1: " << (insideTriangle(p.x(), p.y(), v) ? "inside " : "outside ") 
              << "method2: " << (insideTriangle_mymethod(p.x(), p.y(), v) ? "inside " : "outside ") << std::endl;
    p = {0.1f, 0.3f};
    std::cout << "Point p " << p.transpose() << " is " 
              << "method1: " << (insideTriangle(p.x(), p.y(), v) ? "inside " : "outside ") 
              << "method2: " << (insideTriangle_mymethod(p.x(), p.y(), v) ? "inside " : "outside ") << std::endl;

    p = {1.0f, 1.0f};
    std::cout << "Point p " << p.transpose() << " is " 
              << "method1: " << (insideTriangle(p.x(), p.y(), v) ? "inside " : "outside ") 
              << "method2: " << (insideTriangle_mymethod(p.x(), p.y(), v) ? "inside " : "outside ") << std::endl;

    std::cout << "---------------- " << std::endl;
    std::cout << "Test eigensolver " << std::endl;

    Eigen::Matrix3f A_eigensolver;
    A_eigensolver << 3, 0, 0,
                     0, 3, 0,
                     0, 0, 3;
    A_eigensolver = A_eigensolver * A_eigensolver.transpose();
    std::cout << "Matrix_eigensolver:\n" << A_eigensolver << std::endl;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigensolver(A_eigensolver);
    if (eigensolver.info() != Eigen::Success) 
        abort();
    auto eigenvalues = eigensolver.eigenvalues();
    auto eigenvectors = eigensolver.eigenvectors();
    std::cout << "Eigenvalues: " << eigenvalues.transpose() << std::endl;
    std::cout << "Eigenvectors: \n" << eigenvectors << std::endl;

    std::cout << "---------------- " << std::endl;
    std::cout << "Test solver matrix" << std::endl;

    Eigen::Matrix3f matrix_33 = Eigen::Matrix3f::Random();
    matrix_33 = matrix_33 * matrix_33.transpose();
    Eigen::Vector3f vector_31 = Eigen::Vector3f::Random();
    std::cout << "matrix_33:\n" << matrix_33 << std::endl;
    std::cout << "vector_31:\n" << vector_31.transpose() << std::endl;

    Eigen::Vector3f res_inv = matrix_33.inverse() * vector_31;
    std::cout << "The solution using the inverse is:\n" << res_inv.transpose() << std::endl;

    Eigen::Vector3f res_qr = matrix_33.householderQr().solve(vector_31);
    // Eigen::Vector3f res_qr = matrix_33.fullPivHouseholderQr().solve(vector_31);
    // Eigen::Vector3f res_qr = matrix_33.colPivHouseholderQr().solve(vector_31);
    std::cout << "The solution using QR decomposition is:\n" << res_qr.transpose() << std::endl;

    // Eigen::MatrixXf matrix_5050 = Eigen::MatrixXf::Random(5000, 5000);
    Eigen::MatrixXf matrix_5050 = Eigen::MatrixXf::Random(50, 50);
    matrix_5050 = matrix_5050 * matrix_5050.transpose();

    // Eigen::VectorXf vector_501 = Eigen::VectorXf::Random(5000, 1);
    Eigen::VectorXf vector_501 = Eigen::VectorXf::Random(50, 1);

    double start_time = clock(), end_time;
    Eigen::VectorXf res_inv_50 = matrix_5050.inverse() * vector_501;
    end_time = clock();
    std::cout << "Time using inverse: " << 1000 * (end_time - start_time) / CLOCKS_PER_SEC << "ms" << std::endl;
    float relative_error_inv = (matrix_5050 * res_inv_50 - vector_501).norm() / vector_501.norm();
    std::cout << "The relative error of the solution using the inverse is: " << relative_error_inv << std::endl;
    // std::cout << "The solution using the inverse is:\n" << res_inv_50.transpose() << std::endl;

    start_time = clock();
    Eigen::VectorXf res_qr_50 = matrix_5050.householderQr().solve(vector_501);
    end_time = clock();
    std::cout << "Time using QR decomposition: " << 1000 * (end_time - start_time) / CLOCKS_PER_SEC << "ms" << std::endl;
    float relative_error_qr = (matrix_5050 * res_qr_50 - vector_501).norm() / vector_501.norm();
    std::cout << "The relative error of the solution using QR decomposition is: " << relative_error_qr << std::endl;
    // std::cout << "The solution using QR decomposition is:\n" << res_qr_50.transpose() << std::endl;

    start_time = clock();
    Eigen::VectorXf res_ldlt_50 = matrix_5050.ldlt().solve(vector_501);
    end_time = clock();
    std::cout << "Time using LDLT decomposition: " << 1000 * (end_time - start_time) / CLOCKS_PER_SEC << "ms" << std::endl;
    float relative_error_ldlt = (matrix_5050 * res_ldlt_50 - vector_501).norm() / vector_501.norm();
    std::cout << "The relative error of the solution using LDLT decomposition is: " << relative_error_ldlt << std::endl;
    // std::cout << "The solution using LDLT decomposition is:\n" << res_ldlt_50.transpose() << std::endl;

    
    return 0;
}