//
// Created by Work on 4/24/2018.
//
#include "gtest/gtest.h"
#include "RSAE.h"
TEST(RSAE,gcdTEST)
{
    lab10::rsa_encrypt RSA;
    EXPECT_EQ(5,RSA.gcd(10,5));
}