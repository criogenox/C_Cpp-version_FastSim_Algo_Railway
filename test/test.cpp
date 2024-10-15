#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "fastsim.h"

auto GetTickCount() {
    return std::chrono::high_resolution_clock::now();
}

void bench(auto startTime, auto endTime) {
    const std::chrono::duration<double, std::micro> elapsed_seconds{endTime - startTime};
    std::cout << "\033[0;38;5;144mComputation time elapsed: "
            << elapsed_seconds.count() << " microseconds" << std::endl;
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
    static Inputs test(const int c, double Tx, double Ty) {
        switch (c) {
            case 0:
            case 1:
                return Inputs{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, Tx, Ty};
            case 2:
            case 3:
                return Inputs{1.0, -2.0, 2.0, 4.0, 5.0, 5.0, Tx, Ty};
            case 4:
                return Inputs{1.0, -2.0, 2.0, 1.0, 5.0, 5.0, Tx, Ty};
            default:
                throw std::invalid_argument("Check your input data!!!");
        }
    }
};

struct CalcCases {
    static void calc(const int c, auto &p) {
        switch (c) {
            case 0:
            case 3:
                p->v1(0.4, 3.0);
                break;
            case 1:
            case 2:
            case 4:
                p->v1(0.4, 0.09);
                break;
            default:
                throw std::invalid_argument("Check your input data!!!");
        }
        std::cout << "\033[0;38;5;12m* TEST CASE N°: " << c << std::endl;
    }
};

class ForcesFxFy : public ::testing::TestWithParam<std::vector<double> > {
protected:
    // Static variable to track if setup has been done
    static bool setupDone;

    static void SetUpTestSuite() {
        // Check if setup has already been performed
        if (!setupDone) {
            // Execute warm-up runs only once, for the first test
            double Tx = 0.0, Ty = 0.0;
            const auto p = std::make_unique<Fastsim>(Inputs{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, Tx, Ty});
            p->v1(0.4, 3.0);
            setupDone = true; // Mark setup as done
        }
    }
};

// Initialize the static variable
bool ForcesFxFy::setupDone = false;
int tests = 0;
TEST_P(ForcesFxFy, TestCase) {
    constexpr double Tx = 0.0, Ty = 0.0;
    auto p = std::make_unique<Fastsim>(InputCases::test(tests, Tx, Ty));
    const auto startTime = GetTickCount();
    CalcCases::calc(tests, p);
    const auto endTime = GetTickCount();
    bench(startTime, endTime);
    const auto m = GetParam();
    int i = 0; // Declare i here to avoid global state
    std::for_each(p->T.begin(), p->T.end(),
                  [&](const double s) mutable {
                      ASSERT_NEAR(m[i++], s, 1e-2);
                  });
    tests++;
}

INSTANTIATE_TEST_SUITE_P(FastSimAlgo, ForcesFxFy,
                         ::testing::Values(
                             std::vector<double>{0.0, 0.1843},
                             std::vector<double>{0.0, 0.1850},
                             std::vector<double>{0.5720, 0.1838},
                             std::vector<double>{0.5684, 0.1857},
                             std::vector<double>{0.453, 0.8299}));

int main(int argc, char **argv) {
    std::cout << "\033[1;38;5;201m# C++ ver. | FASTSIM ALGORITHM FOR ROLLING CONTACT" << std::endl;
    std::cout << "\033[2;38;5;201m# ================================================" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
