#include <gtest/gtest.h>

TEST(Suma, 2plus3__shouldbe5) {
int result = 2 + 3;

EXPECT_EQ(result, 5);
}

TEST(Suma, 1plus6__shouldbe7) {
int result = 1 + 6;

EXPECT_EQ(result, 7);
}

TEST(Diva, 9minus5__shouldbe4) {
int result = 9 - 5;

EXPECT_EQ(result, 4);
}

class MultTests : public ::testing::Test {
protected:
    int* data;

    void SetUp() override {
        this->data = new int(42);
        std::cout << "beforeEach" << *this->data << std::endl;
    }

    void TearDown() override {
        std::cout << "afterEach" << *this->data << std::endl;
        delete this->data;
    }
};

TEST_F(MultTests, 1mult0__shouldbe0) {
int result = 1 * 0;
std::cout << *this->data << std::endl;

EXPECT_EQ(result, 0);
}

TEST_F(MultTests, 1mult1__shouldbe1) {
int result = 1 * 1;
std::cout << *this->data << std::endl;

EXPECT_EQ(result, 1);
}

TEST_F(MultTests, 1mult5__shouldbe5) {
int result = 1 * 5;
std::cout << *this->data << std::endl;

EXPECT_EQ(result, 5);
}

//test_death

// instantiate_test_case_p + test_p ????

// try to use member& instead of member*
/*
class CL {
public:
    CL(Obj&& _o)
    : o(std::move(_o))
    { }
private:
    Obj& o;
}
*/




/*
$ cat ./calc.hpp
class Calc
{
    public:
    Calc();
    virtual ~Calc();
    virtual void get();
};
$ INDENT=4 ./deps/googletest/googlemock/scripts/generator/gmock_gen.py ./calc.hpp Calc
class MockCalc : public Calc {
 public:
    MOCK_METHOD(void, get, (), (override));
};
*/
