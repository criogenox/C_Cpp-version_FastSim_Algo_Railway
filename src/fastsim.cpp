#include "fastsim.h"

Subroutine::Subroutine(const Inputs &args): args_(args) {
}

void Subroutine::sr_v1(const double dy, const double y) const {
    double Px = 0.0, Py = 0.0;
    double x0 = std::sqrt(1.0 - std::pow(y, 2));
    const double dx = 2.0 * x0 / args_.mx, AR = dx * dy, B = x0;
    double x = x0 - dx / 2.0;
    const double Sx = args_.ux - y * args_.fx;

    while (-(x + B) < 0.0) {
        const double Sy = args_.uy + args_.fy * (x0 + x) / 2.0;
        Px = Helper::pressure(Px, Sx, x0, x);
        Py = Helper::pressure(Py, Sy, x0, x);

        if (const double P = std::sqrt(std::pow(Px, 2) + std::pow(Py, 2)) /
                             (1.0 - std::pow(y, 2) - std::pow(x, 2)); P > 1.0) {
            Px = Px / P;
            Py = Py / P;
            args_.Tx = Helper::force(args_.Tx, AR, Px);
            args_.Ty = Helper::force(args_.Ty, AR, Py);
            x0 = x;
            x = x - dx;
        } else {
            args_.Tx = Helper::force(args_.Tx, AR, Px);
            args_.Ty = Helper::force(args_.Ty, AR, Py);
            x0 = x;
            x = x - dx;
        }
    }
}

Fastsim::Fastsim(const Inputs &args)
    : Subroutine(args) {
}

Fastsim::~Fastsim() = default;

Fastsim::Fastsim(const Fastsim &other) = default;

Fastsim::Fastsim(Fastsim &&other) noexcept = default;

void Fastsim::v1(double dy, const double TOL) {
    double s = 1.0, ymi;
    bool control;
    while (s > -2.0) {
        if (std::abs(args_.ux) > std::abs(args_.fx) ||
            std::abs(args_.uy) > std::abs(args_.fy)) {
            control = false;
            dy = 2.0 / args_.my;
            s = -1.0;
            ymi = -1.0;
        } else {
            control = true;
            dy = (1.0 - (args_.ux / args_.fx * s)) /
                 (std::floor((1.0 - (args_.ux / args_.fx * s)) * args_.my / 2.0) + 1.0);
            ymi = (args_.ux / args_.fx * s) + dy;
        }
        int nk = 1;
        double y = (1. + dy / 2.) * s;
        while (nk != 0) {
            y = y - dy * s;
            if (y * s < ymi && !control) {
                nk = 0;
            } else if (y * s < ymi) {
                if (TOL < (dy / 2.0)) {
                    dy = dy / 2.0;
                    y = y + (dy / 2.0) * s;
                    sr_v1(dy, y);
                    nk = 1;
                } else {
                    sr_v1(dy, y);
                    nk = 0;
                }
            } else {
                sr_v1(dy, y);
            }
        }
        s = s - 2.0;
    }
    T = {2.0 * -args_.Tx / M_PI, 2.0 * args_.Ty / M_PI};
}
