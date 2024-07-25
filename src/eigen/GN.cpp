#include<bits/stdc++.h>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigen>

int main()
{
    // y = exp(a*x^2 + b*x + c) + w
    // find a b c
    auto func = [](double y, double x, double a, double b, double c) -> double
    {
        return y - exp(a * x * x + b * x + c);
    };
    auto update_param = [](double a, double b, double c, double da, double db, double dc) -> Eigen::Vector3d
    {
        return {a + da, 
                b + db, 
                c + dc};
    };
    auto jacobian = [](double x, double a, double b, double c) -> Eigen::Vector3d
    {
        return {- x * x * exp(a * x * x + b * x + c), 
                - x * exp(a * x * x + b * x + c), 
                - exp(a * x * x + b * x + c)};
    };
    
    // x-y 
    std::vector<std::pair<double, double>> data = {{0, 1}, {1, 2}, {2, 3}};
    int iteration_cnt = 0, iteration_Max = 10;
    double threshold = 1e-4;

    Eigen::Vector3d param(1, 1, 1);
    std::cout << "Initial parm: " << std::endl 
              << "a: " << param[0] << ", b: " << param[1] << ", c: " << param[2] << std::endl;
    
    while (iteration_cnt < iteration_Max) {
        double cost = 0;
        Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
        Eigen::Vector3d b = Eigen::Vector3d::Zero();
        
        // matrix accumulation
        std::cout << "Accumulate matrix H and b" << std::endl;
        for (auto data_i : data) {
            double f = func(data_i.second, data_i.first, param[0], param[1], param[2]);
            Eigen::Vector3d J = jacobian(data_i.first, param[0], param[1], param[2]);
            H += J * J.transpose();
            b += - J * f;
            cost += f * f;
        }

        // // matrix stack
        // std::cout << "Stack matrix H and b" << std::endl;
        // Eigen::MatrixX3d J = Eigen::MatrixX3d::Zero(data.size(), 3);
        // Eigen::VectorXd f = Eigen::VectorXd::Zero(data.size());
        // for (int i = 0; i < data.size(); i++) {
        //     J.row(i) = jacobian(data[i].first, param[0], param[1], param[2]);
        //     f(i) = func(data[i].second, data[i].first, param[0], param[1], param[2]);
        // }
        // H = J.transpose() * J;
        // b = - J.transpose() * f;
        // cost = f.transpose() * f;

        Eigen::Vector3d delta_param = H.inverse() * b;
        // Eigen::Vector3d delta_param = H.ldlt().solve(b);
        // Eigen::Vector3d delta_param = H.householderQr().solve(b);
        param = update_param(param[0], param[1], param[2], delta_param[0], delta_param[1], delta_param[2]);

        std::cout << "Iteration count: " << iteration_cnt << ", cost: " << cost << std::endl;
        std::cout << "a: " << param[0] << ", b: " << param[1] << ", c: " << param[2] << std::endl;
        iteration_cnt += 1;
        std::cout << "delta_param: " << delta_param.transpose() << std::endl
                  << "delta_param.norm(): " << delta_param.norm() << std::endl;
        if (delta_param.norm() < threshold) {
            std::cout << "delta_param is converged" << std::endl;
            break;
        }
    }

    
    return 0;
}