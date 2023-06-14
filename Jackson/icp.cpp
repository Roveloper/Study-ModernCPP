#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/SVD>

constexpr double EPS = 0.0001;
constexpr int MAX_ITER = 100;

struct Point2D {
  double x;
  double y;
};

struct Vector2D {
  double x;
  double y;
  double yaw;
};

Vector2D icp_matching(std::vector<Point2D>& previous_points, std::vector<Point2D>& current_points) {
  double dError = std::numeric_limits<int>::max();
  double preError = std::numeric_limits<int>::max();
  int count = 0;

  while (dError >= EPS) {
    ++count;

    auto [indexes, error] = nearest_neighbor_association(previous_points, current_points);
    auto [Rt, Tt] = svd_motion_estimation(previous_points[:, indexes], current_points);
    
    
    current_points = (Rt @ current_points) + Tt[:, np.newaxis]; // RT, 이용해서 Transformation하는 코드 필요

    dError = preError - error;
    std::cout << "residual = " << error << std::endl;

    if (dError < 0) {
      std::cout << "Not Converged" << preError << " " << dError << " " << count << std::endl;
      break;
    }

    preError = error;
    H = update_homogeneous_matrix(H, Rt, Tt);

    if (dError <= EPS) {
      std::cout << "Converge " << error << " " << dError << " " << count << std::endl;
      break;
    } else if (MAX_ITER <= count) {
      std::cout << "Not Converged ... " << error << " " << dError << " " << count << std::endl;
      break;
    }
  }
  // return R, T
}

auto update_homogeneous_matrix() {
  // ???? 여긴 eigen 안쓰면 안될듯ㅋ
}

auto nearest_neighbor_association(std::vector<Point2D>& previous_points, std::vector<Point2D>& current_points) {
  std::vector<Point2D> delta_points;
  for (int i = 0; i < previous_points.size(); ++i) {
    delta_points.emplace_back(previous_points[i].x - current_points[i].x, previous_points[i].y - current_points[i].y);
  }

  double error;
  for (const auto& p : delta_points) {
    error += std::sqrt(p.x * p.x + p.y + p.y);
  }
  std::vector<int> indexes(current_points.size());
  for (size_t i = 0; i < current_points.size(); ++i) {
    double min_dist = std::numeric_limits<double>::max();
    for (size_t j = 0; j < previous_points.size(); ++j) {
      auto& cp = current_points[i];
      auto& pp = previous_points[j];
      auto dist = (cp.x - pp.x) * (cp.x - pp.x) + (cp.y - pp.y) * (cp.y - pp.y);
      if (min_dist < dist) {
        min_dist = dist;
        indexes[i] = j;
      }
    }
  }

  struct result {std::vector<int> v_i; double error;};
  return result{indexes, error};
}

auto svd_motion_estimation(std::vector<Point2D>& previous_points, std::vector<Point2D>& current_points) {
  auto previous_mean = calculate_mean(previous_points);
  auto current_mean = calculate_mean(current_points);

  std::vector<Point2D> shifted_previous_points;
  std::vector<Point2D> shifted_current_points;

  Eigen::MatrixXf P(2, previous_points.size());
  Eigen::MatrixXf Q(2, current_points.size());

  for (size_t i = 0; i < previous_points.size(); ++i) {
    P(0, i) = previous_points[i].x - previous_mean.x;
    P(1, i) = previous_points[i].y - previous_mean.y;
  }
  for (size_t i = 0; i < current_points.size(); ++i) {
    Q(0, i) = current_points[i].x - current_mean.x;
    Q(1, i) = current_points[i].y - current_mean.y;
  }

  Eigen::MatrixXf M = P * Q.transpose();

  Eigen::JacobiSVD<Eigen::MatrixXf> svd(M, Eigen::ComputeThinU | Eigen::ComputeThinV);

  Eigen::MatrixXf R = svd.matrixV() * svd.matrixU().transpose();

  Vector2D T;
  T.x += (previous_mean.x - current_mean.x);
  T.y += (previous_mean.y - current_mean.y);

  T.yaw += std::atan2(R(1, 0), R(0, 0));

  struct result { Eigen::MatrixXf R; Vector2D T;};
  return result{R, T};
  // not implemented yet
}

Point2D calculate_mean(std::vector<Point2D>& input) {
  Point2D mean_point;
  for (const auto& p : input) {
    mean_point.x = p.x;
    mean_point.y = p.y;
  }
  mean_point.x /= input.size();
  mean_point.y /= input.size();

  return mean_point;
}



int main() {
  std::cout << "ICP Start!" << std::endl;

  int nPoint = 1000;
  double fieldLength = 50.0;
  Vector2D motion;
  motion.x = 0.5;
  motion.y = 2.0;
  motion.yaw = -10 * M_PI / 180;

  int nSim = 3;

  std::vector<Point2D> previous_points;
  std::vector<Point2D> current_points;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(0, 1);

  for (int i = 0; i < nSim; ++i) {
    for (int j = 0; j < nPoint; ++j) {
      Point2D tmp_point;
      
      tmp_point.x = (distr(eng) - 0.5) * fieldLength;
      tmp_point.y = (distr(eng) - 0.5) * fieldLength;
      previous_points.push_back(tmp_point);

      Point2D cur_point;
      cur_point.x = std::cos(motion.yaw) * tmp_point.x - std::sin(motion.yaw) * tmp_point.y + motion.x;
      cur_point.y = std::sin(motion.yaw) * tmp_point.x + std::cos(motion.yaw) * tmp_point.y + motion.y;
      current_points.push_back(cur_point);
    }

    auto result = icp_matching(previous_points, current_points);
    std::cout << "Rotation x, y, yaw = " << result.x << ", " << result.y << ", " << result.yaw * 180 / M_PI << std::endl;
  }

  return 0;
}