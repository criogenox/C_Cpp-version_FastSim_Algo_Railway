#include <gmock/gmock-matchers.h>
#include "fastsim.h"
#include <gtest/gtest.h>

using ::testing::Pointwise;

auto GetTickCount() {
    return std::chrono::steady_clock::now();
}

void bench(auto startTime, auto endTime) {
    std::cout << "\033[0;38;5;144mComputation time elapsed: "
            << std::chrono::duration<double, std::ratio<1, 1000000> >(endTime - startTime).count()
            << " microseconds"
            << std::endl;
}

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

struct InputCases {
    static auto test(const int c, double Tx, double Ty) {
        switch (c) {
            case 0:
            case 1: {
                const Inputs args{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, Tx, Ty};
                return args;
            }
            //
            case 2:
            case 3: {
                const Inputs args{1.0, -2.0, 2.0, 4.0, 5.0, 5.0, Tx, Ty};
                return args;
            }
            //
            case 4: {
                // static double Tx = 0.0, Ty = 0.0;
                const Inputs args{1.0, -2.0, 2.0, 1.0, 5.0, 5.0, Tx, Ty};
                return args;
            }
            //
            default: assert("Check your input data!!!");
            // static constexpr Inputs args{0, 0, 0, 0, 0, 0, Tx, Ty};
            // return args;
        }
    }
};

struct CalcCases {
    static void calc(const int c, auto &p) {
        const auto startTime = ::GetTickCount();
        switch (c) {
            case 0:
            case 3: {
                p->v1(0.4, 3.0);
            }
            break;
            //
            case 1:
            case 2:
            case 4: {
                p->v1(0.4, 0.09);
            }
            break;
            //
            default: assert("Check your input data!!!");
        }
        const auto endTime = ::GetTickCount();
        std::cout << "\033[0;38;5;12m* TEST CASE N°: " << c << std::endl;
        bench(startTime, endTime);
    }
};

class ForcesFxFy : public ::testing::TestWithParam<std::vector<double> > {
};

int tests = 0;
TEST_P(ForcesFxFy, TestCase) {
    int i = 0;
    constexpr double Tx = 0.0, Ty = 0.0;
    const auto p = std::make_unique<Fastsim>(InputCases::test(tests, Tx, Ty));
    CalcCases::calc(tests, p);
    const auto m = GetParam();
    std::for_each(p->T.begin(), p->T.end(),
                  [&i, &m](const double s) mutable {
                      const int j = i;
                      i++;
                      ASSERT_NEAR(m[j], s, 1e-2);
                  });
    tests++;
}

INSTANTIATE_TEST_SUITE_P(FastSimAlgo, ForcesFxFy,
                         ::testing::Values(std::vector<double>{0.0, 0.1843},
                             std::vector<double>{0.0, 0.1850},
                             std::vector<double>{0.5720, 0.1838},
                             std::vector<double>{0.5684, 0.1857},
                             std::vector<double>{0.453, 0.8299}));

int main(int argc, char **argv) {
    std::cout << "\033[1;31m# C++ ver. | FASTSIM ALGORITHM FOR ROLLING CONTACT" << std::endl;
    std::cout << "\033[1;31m# ================================================" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
