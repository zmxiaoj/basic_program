#include<bits/stdc++.h>
#include<ceres/ceres.h>

struct Cureve_Fitting_Cost
{
    Cureve_Fitting_Cost(double x, double y) : _x(x), _y(y) {}

    template<typename T>
    bool operator() (const T* abc, T* residual) const {
        residual[0] = T(_y) - ceres::exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]);
        return true;
    }

    const double _x, _y;
};


int main()
{
    // y = exp(a * x^2 + b * x + c) + w
    // x-y 
    std::vector<std::pair<double, double>> data = {{0.0, 1.0}, {1.0, 2.0}, {2.0, 3.0}};
    // initial parameters a b c
    double abc[3] = {1.0, 1.0, 1.0};

    // construct NLS problem
    std::cout << "Start to construct NLS problem" << std::endl;
    ceres::Problem problem;
    // ceres::LossFunction* loss_function = new ceres::HuberLoss(1.0);
    // ceres::LossFunction* loss_function = new ceres::CauchyLoss(1.0);
    for (int i = 0; i < data.size(); i++) {
        ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<Cureve_Fitting_Cost, 1, 3>(
            new Cureve_Fitting_Cost(data[i].first, data[i].second)
        );
        // problem.AddResidualBlock(cost_function, loss_function, abc);
        problem.AddResidualBlock(cost_function, nullptr, abc);
    }

    // configure solver
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    // options.linear_solver_type = ceres::DENSE_NORMAL_CHOLESKY;
    options.minimizer_progress_to_stdout = true;

    // solve
    ceres::Solver::Summary summary;
    double start = clock(), end;
    std::cout << "Start to solve NLS problem" << std::endl;
    ceres::Solve(options, &problem, &summary);
    end = clock();
    

    // output
    std::cout << summary.BriefReport() << std::endl;
    std::cout << "Time cost: " << 1000 * (end - start) / CLOCKS_PER_SEC << "ms" << std::endl;
    std::cout << "Final parameters: " << abc[0] << ", " << abc[1] << ", " << abc[2] << std::endl;
    for (auto data_i : data) {
        std::cout << "x: " << data_i.first << ", y: " << data_i.second << ", y_fit: " 
                  << ceres::exp(abc[0] * data_i.first * data_i.first + abc[1] * data_i.first + abc[2]) << std::endl;
    }

    return 0;
}