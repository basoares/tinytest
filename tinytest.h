/*
 * TinyTest: A small C++ unit testing framework.
 *
 * Example usage:
 *
 *  #include <iostream>
 *  #include "tinytest.h"
 *
 *  int addOne(int n) {
 *      return n+1;
 *  }
 *
 *  TINY_TEST(f1Pass) {
 *      TINY_CHECK("Is 1+1=2?", addOne(1) == 2);
 *  }
 *
 *  TINY_TEST(f1Fail) {
 *      TINY_CHECK("Or is 1+1=1?", addOne(1) == 1);
 *  }
 *
 *  int main() {
 *      unsigned int numTestsFailed = RUN_TESTS();
 *      std::cout << "There were " << numTestsFailed << " failed tests\n";
 *  }
 *
 */

#ifndef TINYTEST_H_
#define TINYTEST_H_

#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#define TT_ESC_KEY "\033"
#define TT_COLOR_RED "[1;31m"
#define TT_COLOR_GREEN "[1;32m"
#define TT_COLOR_RESET "[0m"

namespace TinyTest {
namespace TinyTestSetup {}    

/*
 * Error throw when a test fails - Always caught by the framework
 *
 * msg = Test description
 * cond = Condition to be tested
 * file = The name of the file containing the tests
 * line_number = The number of the line for the failing test
 */
struct TinyError {
    TinyError(const std::string& msg, const std::string cond, 
              const std::string& file, int line_number) :
        msg_(msg), cond_(cond), file_(file), line_number_(line_number) {
    }

    std::string msg_, cond_, file_;
    int line_number_;
};

/*
 * Pointer to function representing the test
 */
typedef void(* Function)(void);

class Tester {
    public:
        static Tester& GetInstance() {
            static Tester instance;

            return instance;
        }

        void AddTest(const std::string& name, Function test) {
            tests_.push_back(std::make_pair(name, test));
        }

        unsigned int Run() {
            for (const auto& t : tests_) {
                try {
                    std::cout << std::setw(24) << std::left << t.first;
                    t.second();     //run test
                    std::cout << "\033[1;32m" << " passed\n" << "\033[0m";
                }
                catch (const TinyError& e) {
                    std::cout << "\033[1;31m" << " failed assertion " << 
                        "\033[0m" << "in " << e.file_ << " on line " <<
                        e.line_number_ << "\n";
                    std::cout << std::setw(32) << "";
                    std::cout << "Description: " << e.msg_ << std::endl;
                    std::cout << std::setw(32) << "";
                    std::cout << "  Condition: [ " << e.cond_ << " ]" << 
                        std::endl;

                    num_failed_tests_++;
                }
            }
            return num_failed_tests_;
        }

    private:
        Tester() : num_failed_tests_(0) {}

        unsigned int num_failed_tests_;
        std::list<std::pair<std::string, Function>> tests_;

    public:
        Tester(Tester const&)           = delete;
        void operator=(Tester const&)   = delete;
};

struct Setup {
    Setup(const std::string& name, Function f) {
        Tester::GetInstance().AddTest(name, f);
    }
};


} //Namespace TinyTester

#define TINY_TEST(testname)                                     \
    namespace TinyTest {                                        \
    namespace TinyTestSetup {                                   \
    static void testname##_tinytest();                          \
    }                                                           \
    }                                                           \
    namespace TinyTest {                                        \
    namespace TinyTestSetup {                                   \
        static TinyTest::Setup testname(#testname,              \
            TinyTest::TinyTestSetup::testname##_tinytest);      \
    }                                                           \
    }                                                           \
    void TinyTest::TinyTestSetup::testname##_tinytest()

#define TINY_CHECK(msg, cond)                                   \
    if (!(cond)) {                                              \
        throw TinyTest::TinyError(#msg, #cond, __FILE__,        \
                                  __LINE__);                    \
    }

#define RUN_TESTS() TinyTest::Tester::GetInstance().Run()

#endif  //TINY_TEST_H_
