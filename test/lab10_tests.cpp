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
//TEST_F(Lab10Fixture)

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
    RSA.generate_keys();
}
TEST_F(Lab10Fixture, encrypt_message_test){
    RSA.encrypt(42, "71-121");


}
TEST_F(Lab10Fixture, decrypt_message_test){
    RSA.decrypt(110, "31-121");
}

TEST(Modulo_trials, test1){
    double result = remainder(4, 8);
    EXPECT_EQ(4, result);
}
TEST(Modulo_trials, test2){
    double result = remainder(12, 5 );
    EXPECT_EQ(2, result);
}
TEST(Power_tirals, test1){
    double result = pow(4, 6);
    EXPECT_EQ(4096, result);
}
TEST(Power_trials, test2){
    double result = fmod(pow(42, 85),323);



}