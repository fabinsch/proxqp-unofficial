//
// Copyright (c) 2022 INRIA
//
#include <doctest.hpp>
#include <Eigen/Core>
#include <Eigen/Cholesky>
#include <proxsuite/proxqp/dense/dense.hpp>
#include <proxsuite/linalg/veg/util/dbg.hpp>
#include <proxsuite/proxqp/utils/random_qp_problems.hpp>

using T = double;
using namespace proxsuite;
using namespace proxsuite::proxqp;

template<typename T, proxqp::Layout L>
using Mat =
  Eigen::Matrix<T,
                Eigen::Dynamic,
                Eigen::Dynamic,
                (L == proxqp::colmajor) ? Eigen::ColMajor : Eigen::RowMajor>;
template<typename T>
using Vec = Eigen::Matrix<T, Eigen::Dynamic, 1>;

DOCTEST_TEST_CASE("simple test case from cvxpy, check feasibility")
{

  std::cout << "---simple test case from cvxpy, check feasibility "
            << std::endl;
  T eps_abs = T(1e-9);
  dense::isize dim = 3;

  Mat<T, colmajor> H = Mat<T, colmajor>(dim, dim);
  H << 13.0, 12.0, -2.0,
       12.0, 17.0, 6.0, 
       -2.0, 6.0, 12.0;

  Vec<T> g = Vec<T>(dim);
  g << -22.0, -14.5, 13.0;

  Mat<T, colmajor> C = Mat<T, colmajor>(dim, dim);
  C << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0, 
       0.0, 0.0, 1.0;

  Vec<T> l = Vec<T>(dim);
  l << -1.0, -1.0, -1.0;

  Vec<T> u = Vec<T>(dim);
  u << 1.0, 1.0, 1.0;
  Results<T> results = dense::solve<T>(H,
                                       g,
                                       std::nullopt,
                                       std::nullopt,
                                       C,
                                       u,
                                       l,
                                       std::nullopt,
                                       std::nullopt,
                                       std::nullopt,
                                       eps_abs,
                                       0);

  T pri_res = (dense::positive_part(C * results.x - u) +
               dense::negative_part(C * results.x - l)).lpNorm<Eigen::Infinity>();
  T dua_res = (H * results.x + g + C.transpose() * results.z).lpNorm<Eigen::Infinity>();
  DOCTEST_CHECK(pri_res <= eps_abs);
  DOCTEST_CHECK(dua_res <= eps_abs);


  std::cout << "primal residual: " << pri_res << std::endl;
  std::cout << "dual residual: " << dua_res << std::endl;
  std::cout << "total number of iteration: " << results.info.iter << std::endl;
  std::cout << "setup timing " << results.info.setup_time << " solve time "
            << results.info.solve_time << std::endl;
}