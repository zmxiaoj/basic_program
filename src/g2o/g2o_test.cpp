#include<bits/stdc++.h>
#include<eigen3/Eigen/Eigen>
#include<eigen3/Eigen/Core>
#include<g2o/core/g2o_core_api.h>
#include<g2o/core/base_vertex.h>
#include<g2o/core/base_unary_edge.h>
#include<g2o/core/block_solver.h>
#include<g2o/core/optimization_algorithm_levenberg.h>
#include<g2o/core/optimization_algorithm_gauss_newton.h>
#include<g2o/core/optimization_algorithm_dogleg.h>
#include<g2o/solvers/dense/linear_solver_dense.h>


// vertex, 优化变量维度和数据类型
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    // reset
    virtual void setToOriginImpl() override {
        _estimate << 0, 0, 0;
    }

    // update
    virtual void oplusImpl(const double* update) override {
        _estimate += Eigen::Vector3d(update);
    }

    virtual bool read(std::istream& in) override {}

    virtual bool write(std::ostream& out) const override {}

};

// edge 
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x) {}

    // compute residual
    void computeError() override {
        const auto* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        _error(0, 0) = _measurement - std::exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
    }

    // compute jacobian
    void linearizeOplus() override {
        const auto* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        double exp_y = std::exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
        _jacobianOplusXi[0] = -_x * _x * exp_y;
        _jacobianOplusXi[1] = -_x * exp_y;
        _jacobianOplusXi[2] = -exp_y;
    }

    virtual bool read(std::istream& in) override {}

    virtual bool write(std::ostream& out) const override {}

public:
    double _x;
};



int main()
{
    // y = exp(a * x^2 + b * x + c) + w
    // x-y 
    std::vector<std::pair<double, double>> data = {{0, 1}, {1, 2}, {2, 3}};
    // initial parameters a b c
    double abc[3] = {1.0, 1.0, 1.0};

    // configure g2o
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

    auto solver = new g2o::OptimizationAlgorithmGaussNewton(
        std::make_unique<BlockSolverType>(std::make_unique<LinearSolverType>())
    );
    g2o::SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);
    optimizer.setVerbose(true);

    // add vertex
    std::cout << "Start to add vertex" << std::endl;
    CurveFittingVertex *v = new CurveFittingVertex();
    v->setEstimate(Eigen::Vector3d(abc));
    v->setId(0);
    optimizer.addVertex(v);

    // add edge
    std::cout << "Start to add edge" << std::endl;
    for (int i = 0; i < data.size(); i++) {
        CurveFittingEdge* e = new CurveFittingEdge(data[i].first);
        e->setId(i);
        // 0表示e对应的第0个顶点是v
        e->setVertex(0, v);
        e->setMeasurement(data[i].second);
        e->setInformation(Eigen::Matrix<double, 1, 1>::Identity());
        optimizer.addEdge(e);
    }

    // start optimize
    std::cout << "Start to optimize" << std::endl;
    double strat = clock(), end;
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    end = clock();

    std::cout << "Time cost: " << 1000 * (end - strat) / CLOCKS_PER_SEC << "ms" << std::endl;
    Eigen::Vector3d abc_estimate = v->estimate();
    std::cout << "Final parameters: " << abc_estimate[0] << ", " << abc_estimate[1] << ", " << abc_estimate[2] << std::endl;

    return 0;
}