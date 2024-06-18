#pragma once
#ifndef FASTSIM_H
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#define FASTSIM_H

struct Inputs {
    double ux, uy, fx, fy, mx, my;
    double &Tx, &Ty;
};

namespace Helper {
    inline double pressure(const double P, const double S,
                           const double x0, const double x) {
        return P - S * (x0 - x);
    }

    inline double force(const double args_T, const double AR,
                        const double P) {
        return args_T + AR * P;
    }
}

class Subroutine {
public:
    explicit Subroutine(const Inputs &args);

    void sr_v1(double dy, double y) const;

    const Inputs &args_;
};

class Fastsim : Subroutine {
public:
    explicit Fastsim(const Inputs &args);

    ~Fastsim();

    Fastsim(const Fastsim &other);

    Fastsim(Fastsim &&other) noexcept;

    void v1(double dy, double TOL);

    std::vector<double> T;
};

#endif //FASTSIM_H
