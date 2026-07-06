#include <chrono>
#include <iostream>
#include <memory>

#include "fastsim.h"

auto GetTickCount() {
    return std::chrono::high_resolution_clock::now();
}

int main() {
    // 1982 -Kalker- A FAST ALGORITHM FOR THE SIMPLIFIED THEORY OF ROLLING CONTACT (TESTS)
    // -----------------------------------------------------------------------------------
    // N°0: ux=0 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=3    |=> Tx=0      & Ty=0.1843
    // N°1: ux=0 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=0.09 |=> Tx=0      & Ty=0.1850
    // N°2: ux=1 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=0.09 |=> Tx=0.5720 & Ty=0.1838
    // N°3: ux=1 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=3    |=> Tx=0.5684 & Ty=0.1857
    // N°4: ux=1 | uy=-2 | fx=2 | fy=1 | mx=5 | my=5 | TOL=0.09 |=> Tx=0.4530 & Ty=0.8299
    // -----------------------------------------------------------------------------------
    constexpr double ux = 1.0, uy = -2.0, fx = 2.0, fy = 4.0, mx = 5.0, my = 5.0, Tx = 0.0, Ty = 0.0;
    constexpr Inputs args{ux, uy, fx, fy, mx, my, Tx, Ty};
    const auto p = std::make_unique<Fastsim>(args);
    const auto startTime = ::GetTickCount();
    // ---
    p->creep(3.0);
    // ---
    const auto endTime = ::GetTickCount();
    const std::chrono::duration<double, std::micro> elapsed_seconds{endTime - startTime};
    std::cout << "Time elapsed: "
            << elapsed_seconds.count()
            << " microseconds"
            << std::endl;
    // ---
    std::cout << "Fx= " << p->T[0] << std::endl;
    std::cout << "Fy= " << p->T[1] << std::endl;
    return 0;
}
