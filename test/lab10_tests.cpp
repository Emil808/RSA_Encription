//
// Created by Work on 4/24/2018.
//
#include "gtest/gtest.h"
#include "RSAE.h"

class Lab10Fixture : public ::testing::Test{
protected:
    virtual void SetUp(){

    }
public:
    lab10::rsa_encrypt RSA;
};

TEST_F(Lab10Fixture, prime_gcd_test){
    unsigned a = RSA.get_prime();//problem, get_prime returns same exact number when called twice
    unsigned b = RSA.get_prime();

    EXPECT_EQ(1, RSA.find_gcd(a,b));
}