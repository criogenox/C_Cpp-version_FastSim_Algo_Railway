#include "fastsim.h"

auto GetTickCount() { return std::chrono::steady_clock::now(); }

int main() {
    // ---
    const auto startTime = ::GetTickCount();
    // ---
    // %------------------------------Prueba N°1----------------------------------
    // % ux=0; uy=-2; fx=2; fy=4;
    // % mx=5; my=5; dy=0.4; TOL=3;
    // % Resultados paper ===> Tx=0  Ty=0.1843
    double Tx = 0.0, Ty = 0.0;
    constexpr double ux = 1, uy = -2.0, fx = 2.0, fy = 4.0, mx = 5.0, my = 5.0;
    const Inputs args{ux, uy, fx, fy, mx, my, Tx, Ty};
    const auto p = std::make_unique<Fastsim>(args);
    // Fastsim fastsimo{args};
    p->v1(0.4, 0.09);
    // ---
    const auto endTime = ::GetTickCount();
    std::cout << "Time elapsed: "
            << std::chrono::duration<double, std::ratio<1, 1000000> >(endTime - startTime).count()
            << " microseconds"
            << std::endl;
    // ---
    std::cout << "Fx= " << p->T[0] << std::endl;
    std::cout << "Fy= " << p->T[1] << std::endl;
    return 0;
}
