#include <gtest/gtest.h>
#include <iostream>
#include <Eigen/Dense>
#include "extended_kalman_filter.hpp"


#define mat Eigen::MatrixXd
// Extended Kalman Filter

class test_state_model : state_model {

    mat next_state(const mat& state, const mat& control_input) {
        mat next(2, 1);
        double x = state(0, 0);
        double v = state(1, 0);
        double step_time = control_input(1, 0);
        next << 
                x + v * step_time,
                v;
        return next;
    }

    virtual Eigen::MatrixXd jacobian(
    const mat& state
    , const mat& control_input) {
        double step_time = control_input(1, 0);
        mat jaco(2,2);
        jaco << 
             1.0  , step_time
           , 0.0  ,  1.0;
        return jaco;
    }

    virtual mat covariance() {
        mat p(2,2);
        p << 
            1.0, 0.0
          , 0.0, 1.0;
        p.setIdentity();
        return p;
    }
};

class test_observation_model : observation_model {
    Eigen::MatrixXd observe(
    const Eigen::MatrixXd & state
    , const Eigen::MatrixXd& control_input) {
        return jacobian(state, control_input) * state;
    }

    Eigen::MatrixXd jacobian(
    const Eigen::MatrixXd & state
    , const Eigen::MatrixXd& control_input) {
        mat jaco(2,2);
        jaco <<
            1.0, 0.0;
        return jaco;
    }

    Eigen::MatrixXd covariance() {
        mat conv(2, 2);
        conv <<
            1.0, 0.0,
            0.0, 1.0;
        return conv;
    }
};

class test_state_estimator {
    std::tuple<Eigen::MatrixXd, Eigen::MatrixXd>  predict(const Eigen::MatrixXd & state
                                    , const Eigen::MatrixXd& control_input) {


    }
    std::tuple<Eigen::MatrixXd, Eigen::MatrixXd>  update(const Eigen::MatrixXd & state
                                    , const Eigen::MatrixXd& control_input) {

    }
};


TEST(EkfTest, 01) {
    mat m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    test_state_model model;
}