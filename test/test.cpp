#include <array>
#include <chrono>
#include <memory>
#include <ostream>

#include <gtest/gtest.h>
#include "fastsim.h"

// Timing utility
inline auto tick_now() {
    return std::chrono::high_resolution_clock::now();
}

void bench(auto startTime, auto endTime) {
    const std::chrono::duration<double, std::micro> elapsed{endTime - startTime};
    std::cout << "\033[0;38;5;144mComputation time elapsed: "
            << elapsed.count() << " microseconds" << std::endl;
}

// Testing data for validation
struct TestCase {
    Inputs inputs;
    double tol;
    std::array<double, 2> expected;
};

// Human-readable test names in GoogleTest output
void PrintTo(const TestCase &tc, std::ostream *os) {
    *os << "{" << tc.expected[0] << ", " << tc.expected[1] << "}";
}

// 1982 -Kalker- A FAST ALGORITHM FOR THE SIMPLIFIED THEORY OF ROLLING CONTACT (TESTS)
// -----------------------------------------------------------------------------------
// N°0: ux=0 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=3    |=> Tx=0      & Ty=0.1843
// N°1: ux=0 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=0.09 |=> Tx=0      & Ty=0.1850
// N°2: ux=1 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=0.09 |=> Tx=0.5720 & Ty=0.1838
// N°3: ux=1 | uy=-2 | fx=2 | fy=4 | mx=5 | my=5 | TOL=3    |=> Tx=0.5684 & Ty=0.1857
// N°4: ux=1 | uy=-2 | fx=2 | fy=1 | mx=5 | my=5 | TOL=0.09 |=> Tx=0.4530 & Ty=0.8299
// -----------------------------------------------------------------------------------

class ForcesFxFy : public ::testing::TestWithParam<TestCase> {
protected:
    static void SetUpTestSuite() {
        // Warm CPU caches, branch predictor, frequency scaling, allocator.
        // Absorbs one-time costs so the first measured test isn't penalized.
        const auto p = std::make_unique<Fastsim>(
            Inputs{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, 0.0, 0.0});
        p->creep(3.0);
    }
};

TEST_P(ForcesFxFy, TestCase) {
    const auto &[inputs, tol, expected] = GetParam();

    const auto p = std::make_unique<Fastsim>(inputs);

    const auto t0 = tick_now();
    p->creep(tol);
    const auto t1 = tick_now();

    bench(t0, t1);

    const auto *info = ::testing::UnitTest::GetInstance()->current_test_info();
    std::cout << "\033[0;38;5;12m* TEST CASE: " << info->name() << std::endl;

    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(expected[i], p->T[i], 1.5e-3);
    }
}

INSTANTIATE_TEST_SUITE_P(FastSimAlgo, ForcesFxFy,
                         ::testing::Values(
                             TestCase{{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, 0.0, 0.0}, 3.0, {0.0, 0.1843}},
                             TestCase{{0.0, -2.0, 2.0, 4.0, 5.0, 5.0, 0.0, 0.0}, 0.09, {0.0, 0.1850}},
                             TestCase{{1.0, -2.0, 2.0, 4.0, 5.0, 5.0, 0.0, 0.0}, 0.09, {0.5720, 0.1838}},
                             TestCase{{1.0, -2.0, 2.0, 4.0, 5.0, 5.0, 0.0, 0.0}, 3.0, {0.5684, 0.1857}},
                             TestCase{{1.0, -2.0, 2.0, 1.0, 5.0, 5.0, 0.0, 0.0}, 0.09, {0.453, 0.8299}}
                         ));

int main(int argc, char **argv) {
    std::cout << "\033[1;38;5;201m# C++ ver. | FASTSIM ALGORITHM FOR ROLLING CONTACT" << std::endl;
    std::cout << "\033[2;38;5;201m# ================================================" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
