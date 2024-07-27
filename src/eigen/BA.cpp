#include<bits/stdc++.h>
#include<Eigen/Eigen>

struct Camera {
    Eigen::Vector3d translation;
    Eigen::Vector3d rotation;
};
struct Point3D {
    Eigen::Vector3d position;
};
struct Observation {
    int camera_idx;
    int point3d_idx;
    Eigen::Vector2d observed_position;
};

Eigen::Vector2d project(const Camera& camera, const Point3D& point, Eigen::Matrix3d K)
{
    Eigen::Matrix3d R;
    R = Eigen::AngleAxisd(camera.rotation.norm(), camera.rotation.normalized());
    Eigen::Vector3d Pcam = R * point.position + camera.translation;
    Eigen::Vector3d P = K * Pcam;
    Eigen::Vector2d p_pixel = P.head<2>() / P(2);
    return {p_pixel(0), p_pixel(1)};
}

void bundleAdjustment(std::vector<Camera>& cameras, 
                      std::vector<Point3D>& points, 
                      std::vector<Observation>& observations,
                      Eigen::Matrix3d& K)
{
    Eigen::MatrixXd H(6 * cameras.size() + 3 * points.size(), 6 * cameras.size() + 3 * points.size());
    Eigen::VectorXd b(6 * cameras.size() + 3 * points.size());
    H.setZero();
    b.setZero();

    double total_error = 0.0;
    for (const auto& obs : observations) {
        const Camera& camera = cameras[obs.camera_idx];
        const Point3D& point = points[obs.point3d_idx];
        Eigen::Vector2d projected = project(camera, point, K);
        Eigen::Vector2d error = projected - obs.observed_position;
        total_error += error.squaredNorm();

        Eigen::Matrix<double, 2, 6> J_cam;
        Eigen::Matrix<double, 2, 3> J_point;

        // todo: calculate Jacobian Matrix
        J_cam << 1, 0, -projected(0),
                 0, 1, -projected(1);
        J_point = K * Eigen::Matrix<double, 3, 2>::Identity();
        

        H.block<6, 6>(6 * obs.camera_idx, 6 * obs.camera_idx) += J_cam.transpose() * J_cam;
        H.block<6, 3>(6 * obs.camera_idx, 6 * cameras.size() + 3 * obs.point3d_idx) += J_cam.transpose() * J_point;
        H.block<3, 6>(6 * cameras.size() + 3 * obs.point3d_idx, 6 * obs.camera_idx) += J_point.transpose() * J_cam;
        H.block<3, 3>(6 * cameras.size() + 3 * obs.point3d_idx, 6 * cameras.size() + 3 * obs.point3d_idx) += J_point.transpose() * J_point;

        b.segment<6>(6 * obs.camera_idx) += J_cam.transpose() * error;
        b.segment<3>(6 * cameras.size() + 3 * obs.point3d_idx) += J_point.transpose() * error;
    }

    Eigen::VectorXd delta = H.ldlt().solve(b);

    for (int i = 0; i < cameras.size(); ++i) {
        cameras[i].translation += delta.segment<3>(6 * i);
        cameras[i].rotation += delta.segment<3>(6 * i + 3);
    }
    for (int i = 0; i < points.size(); ++i) {
        points[i].position += delta.segment<3>(6 * cameras.size() + 3 * i);
    }
}

int main()
{
    std::vector<Camera> cameras = {
        {{0, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}}
    };
    std::vector<Point3D> points = {
        {{0, 0, 5}},
        {{1, 0, 5}}
    };
    std::vector<Observation> observations = {
        {0, 0, {0.0, 0.0}},
        {0, 1, {1.0, 0.0}},
        {1, 0, {-1.0, 0.0}},
        {1, 1, {0.0, 0.0}}
    };
    Eigen::Matrix3d K;
    K << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    bundleAdjustment(cameras, points, observations, K);

    for (const auto &cam : cameras) {
        std::cout << "Camera translation: " << cam.translation.transpose() << std::endl;
        std::cout << "Camera rotation: " << cam.rotation.transpose() << std::endl;
    }

    for (const auto &point : points) {
        std::cout << "Point position: " << point.position.transpose() << std::endl;
    }

    return 0;
}