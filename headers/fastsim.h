#pragma once

#include <array>
#include <cmath>

struct Inputs {
    double ux, uy, fx, fy, mx, my, Tx, Ty;
};

namespace Helper {
    inline double pressure(const double Pold, const double S, const double x_prev, const double x_curr) {
        return Pold - S * (x_prev - x_curr);
    }

    inline double force(const double Told, const double AR, const double P) {
        return Told + AR * P;
    }
}

class Subroutine {
protected:
    Inputs args_;

public:
    explicit Subroutine(const Inputs &args);

    void traction(double dy, double y);
};

class Fastsim : public Subroutine {
public:
    explicit Fastsim(const Inputs &args);

    ~Fastsim() = default;

    Fastsim(const Fastsim &other) = default;

    Fastsim(Fastsim &&other) noexcept = default;

    std::array<double, 2> T{};

    void creep(double TOL);
};
