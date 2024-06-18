#include "fastsim.h"

auto GetTickCount() { return std::chrono::steady_clock::now(); }

int main() {
    // #########################################################################
    // 1982-Kalker-A FAST ALGORITHM FOR THE SIMPLIFIED THEORY OF ROLLING CONTACT
    // #########################################################################
    // -------------------------------Test N°0----------------------------------
    //  ux=0; uy=-2; fx=2; fy=4;
    //  mx=5; my=5; dy=0.4; TOL=3;
    //  Paper results ===> Tx=0  Ty=0.1843
    // -------------------------------Test N°1----------------------------------
    //  ux=0; uy=-2; fx=2; fy=4;
    //  mx=5; my=5; dy=0.4; TOL=0.09;
    //  Paper results ===> Tx=0  Ty=0.1850
    // -------------------------------Test N°2----------------------------------
    //  ux=1; uy=-2; fx=2; fy=4;
    //  mx=5; my=5; dy=0.4; TOL=0.09;
    //  Paper results  ===> Tx=0.5720  Ty=0.1838
    // -------------------------------Test N°3----------------------------------
    //  ux=1; uy=-2; fx=2; fy=4;
    //  mx=5; my=5; dy=0.4; TOL=3;
    //  Paper results ===> Tx=0.5684  Ty=0.1857
    // -------------------------------Test N°4----------------------------------
    //  ux=1; uy=-2; fx=2; fy=1;
    //  mx=5; my=5; dy=0.4; TOL=0.09;
    //  Paper results ===> Tx=0.4530  Ty=0.8299
    // -------------------------------------------------------------------------
    const auto startTime = ::GetTickCount();
    double Tx = 0.0, Ty = 0.0;
    constexpr double ux = 1, uy = -2.0, fx = 2.0, fy = 4.0, mx = 5.0, my = 5.0;
    const Inputs args{ux, uy, fx, fy, mx, my, Tx, Ty};
    const auto p = std::make_unique<Fastsim>(args);
    // ---
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
