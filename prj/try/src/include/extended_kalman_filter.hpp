#ifndef EXTENDED_KALMAN_FILTER_HPP
#define EXTENDED_KALMAN_FILTER_HPP

#include <tuple>

class state_model {
public:

    virtual Eigen::MatrixXd next_state(const Eigen::MatrixXd & state
                                     , const Eigen::MatrixXd& control_input) = 0;

    virtual Eigen::MatrixXd jacobian(const Eigen::MatrixXd & state
                                     , const Eigen::MatrixXd& control_input) = 0;

    // Q
    virtual Eigen::MatrixXd covariance() = 0;

};


class observation_model {
    virtual Eigen::MatrixXd observe(const Eigen::MatrixXd & state
                                    , const Eigen::MatrixXd& control_input) = 0;

    virtual Eigen::MatrixXd jacobian(const Eigen::MatrixXd & state
                                     , const Eigen::MatrixXd& control_input) = 0;

    virtual Eigen::MatrixXd covariance() = 0;


};

class state_estimator {

    virtual std::tuple<Eigen::MatrixXd, Eigen::MatrixXd> predict(const Eigen::MatrixXd & state
                                    , const Eigen::MatrixXd& control_input) = 0;
    virtual std::tuple<Eigen::MatrixXd, Eigen::MatrixXd> update(const Eigen::MatrixXd & state
                                    , const Eigen::MatrixXd& control_input) = 0;
};

#endif