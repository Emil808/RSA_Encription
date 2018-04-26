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
TEST(RSAE, privateKeyTest)
{
    lab10::rsa_encrypt RSA1;
    EXPECT_EQ(23, RSA1.generate_private(7,160));
    EXPECT_EQ(2753, RSA1.generate_private(17,3120));
    EXPECT_EQ(103, RSA1.generate_private(7,120));
}