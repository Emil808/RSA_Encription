//
// Created by Work on 4/24/2018.
//
#include "gtest/gtest.h"
#include "RSAE.h"
#include <math.h>

class Lab10Fixture : public ::testing::Test{
protected:
    virtual void SetUp(){

    }
public:
    lab10::rsa_encrypt RSA;
};

//generate prime functionality tests
//notice when running multiple times will result in different numbers each time!!
TEST_F(Lab10Fixture, prime_gcd_test){
    unsigned a = RSA.get_prime();
    unsigned b = RSA.get_prime();
    std::cout << std::endl << "gcd( " << a << ", " << b << ") = " << RSA.find_gcd(a,b) << std::endl;
    EXPECT_EQ(1, RSA.find_gcd(a,b));// gcd of 2 primes == 1
}
TEST_F(Lab10Fixture, prime_2_test){
    unsigned a = RSA.get_prime();
    unsigned b = RSA.get_prime();
    std::cout << std::endl << "gcd( " << a << ", " << b << ") = " << RSA.find_gcd(a,b) << std::endl;
    EXPECT_EQ(1, RSA.find_gcd(a,b));// gcd of 2 primes == 1
}
TEST_F(Lab10Fixture, prime_3_test){
    unsigned a = RSA.get_prime();
    unsigned b = RSA.get_prime();
    std::cout << std::endl << "gcd( " << a << ", " << b << ") = " << RSA.find_gcd(a,b) << std::endl;
    EXPECT_EQ(1, RSA.find_gcd(a,b));// gcd of 2 primes == 1
}
TEST_F(Lab10Fixture, prime_4_test){
    unsigned a = RSA.get_prime();
    unsigned b = RSA.get_prime();
    std::cout << std::endl << "gcd( " << a << ", " << b << ") = " << RSA.find_gcd(a,b) <<std::endl;
    EXPECT_EQ(1, RSA.find_gcd(a,b));// gcd of 2 primes == 1
}
TEST_F(Lab10Fixture, coprimeTEST1)
{
    unsigned extotient=100;
    unsigned a=RSA.get_coprime_to_totient(extotient);
    EXPECT_TRUE(a<extotient);
    EXPECT_TRUE(a>1);
    EXPECT_EQ(1,RSA.find_gcd(a,extotient));
}


//gcd functionality tests
TEST_F(Lab10Fixture, gcd_1_test){
    EXPECT_EQ(3, RSA.find_gcd(3, 6));
}
TEST_F(Lab10Fixture, gcd_2_test){
    EXPECT_EQ(8, RSA.find_gcd(8, 16));
}
TEST(RSAE, privateKeyTest)
{
    lab10::rsa_encrypt RSA1;
    EXPECT_EQ(31, RSA1.get_private(7,72)); // n = 91,
    EXPECT_EQ(2753, RSA1.get_private(17,3120));//
    EXPECT_EQ(103, RSA1.get_private(7,120));
}
TEST_F(Lab10Fixture, generate_keys_test){
    EXPECT_NO_FATAL_FAILURE(RSA.generate_keys());
}
//sets of keys to test
//PUBLIC KEY: 29959-64913
//PRIVATE KEY: 4087-64913

//PUBLIC KEY: 48911-87341
//PRIVATE KEY: 21791-87341

//PUBLIC KEY: 68827-205099
//PRIVATE KEY: 48923-205099
TEST_F(Lab10Fixture, encrypt_num_test1){
    long double number = 69;
    RSA.encrypt_num(number, "29959-64913");
    EXPECT_TRUE(69 != number);

    RSA.decrypt_num(number, "4087-64913");
    EXPECT_EQ(69, number);
}

TEST_F(Lab10Fixture, encrypt_num_test2){
    long double number = 42;
    RSA.encrypt_num(number, "48911-87341");
    EXPECT_TRUE(42 != number);

    RSA.decrypt_num(number, "21791-87341");
    EXPECT_EQ(42, number);
}
