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
    EXPECT_EQ(1, RSA.find_gcd(15, 4));
}
TEST(RSAE, privateKeyTest)
{
    lab10::rsa_encrypt RSA1;
    EXPECT_EQ(31, RSA1.get_private(7,72)); // n = 91,
    EXPECT_EQ(2753, RSA1.get_private(17,3120));//
    EXPECT_EQ(103, RSA1.get_private(7,120));
}


//encryption tests
TEST_F(Lab10Fixture, generate_keys_test){
    EXPECT_NO_FATAL_FAILURE(RSA.generate_keys());
}
//sets of keys to test
//PUBLIC KEY: 29959-64913
//PRIVATE KEY: 4087-64913
TEST_F(Lab10Fixture, encrypt_num_test1){
    long double number = 69;
    RSA.encrypt(number, "29959-64913");
    EXPECT_TRUE(69 != number);

    RSA.decrypt(number, "4087-64913");
    EXPECT_EQ(69, number);
}
//PUBLIC KEY: 48911-87341
//PRIVATE KEY: 21791-87341
//PUBLIC KEY: 35149-62291
//PRIVATE KEY: 23101-62291
TEST_F(Lab10Fixture, encrypt_num_test2){
    long double number = 42;
    RSA.encrypt(number, "35149-62291");
    EXPECT_TRUE(42 != number);

    RSA.decrypt(number, "23101-62291");
    EXPECT_EQ(42, number);
}
//PUBLIC KEY: 171983-326731
//PRIVATE KEY: 135239-326731
TEST_F(Lab10Fixture, encrypt_num_test3) {
    long double number = 72;
    RSA.encrypt(number, "171983-326731");
    EXPECT_TRUE(72 != number);

    RSA.decrypt(number, "135239-326731");
    EXPECT_EQ(72, number);
}
//PUBLIC KEY: 1307-10511
//PRIVATE KEY: 2579-10511
TEST_F(Lab10Fixture, encrypt_num_test4) {
    long double number = 9829;
    RSA.encrypt(number, "1307-10511");
    EXPECT_TRUE(9829 != number);

    RSA.decrypt(number, "2579-10511");
    EXPECT_EQ(9829, number);
}
TEST_F(Lab10Fixture, encrypt_num_test4_2) {
    long double number = 48061;//fails for 5-digit number
    RSA.encrypt(number, "1307-10511");
    EXPECT_TRUE(48061 != number);

    RSA.decrypt(number, "2579-10511");
    EXPECT_EQ(48061, number);
}

//PUBLIC KEY: 48079-260327
//PRIVATE KEY: 162511-260327
TEST_F(Lab10Fixture, encrypt_num_test5) {
    long double number = 98290;
    RSA.encrypt(number, "48079-260327");
    EXPECT_TRUE(98290 != number);

    RSA.decrypt(number, "162511-260327");

    EXPECT_EQ(98290, number);
}
TEST_F(Lab10Fixture, encrypt_num_test6) {
    long double number = 9800;
    RSA.encrypt(number, "48079-260327");
    EXPECT_TRUE(9999 != number);

    RSA.decrypt(number, "162511-260327");
    EXPECT_EQ(9800, number);
}
TEST_F(Lab10Fixture, encrypt_num_test7) {
    long double number = 98297;
    RSA.encrypt(number, "48079-260327");
    EXPECT_TRUE(98297 != number);

    RSA.decrypt(number, "162511-260327");
    EXPECT_EQ(98297, number);
}
TEST_F(Lab10Fixture, encrypt_num_test8) {//to make sure the keys work
    long double number = 9;
    RSA.encrypt(number, "19-158");
    EXPECT_TRUE(9 != number);

    RSA.decrypt(number, "37-158");
    EXPECT_EQ(9, number);
}
//PUBLIC KEY: 236993-585209
//PRIVATE KEY: 102977-585209
//keys from primes bellow 500, changed some data types in generate private from int to unsigned
TEST_F(Lab10Fixture, encrypt_num_test9) {//to make sure the keys work
    long double number = 9;
    RSA.encrypt(number, "236993-585209");
    EXPECT_TRUE(9 != number);

    RSA.decrypt(number, "102977-585209");
    EXPECT_EQ(9, number);
}
TEST_F(Lab10Fixture, encrypt_num_test10) { // 4-digit message
    long double number = 9819;
    RSA.encrypt(number, "236993-585209");
    EXPECT_TRUE(9819 != number);

    RSA.decrypt(number, "102977-585209");
    EXPECT_EQ(9819, number);
}
TEST_F(Lab10Fixture, encrypt_num_test11) { // 5-digit message
    long double number = 97190;
    RSA.encrypt(number, "236993-585209");
    EXPECT_TRUE(97190 != number);

    RSA.decrypt(number, "102977-585209");
    EXPECT_EQ(97190, number);
}
TEST_F(Lab10Fixture, encrypt_num_test12) { // 6-digit message
long double number = 971903;
RSA.encrypt(number, "236993-585209");
EXPECT_TRUE(971903 != number);

RSA.decrypt(number, "102977-585209");
EXPECT_EQ(971903, number);
}

//PUBLIC KEY: 164783-212521
//PRIVATE KEY: 42847-212521
TEST_F(Lab10Fixture, encrypt_num_test13) { // 6-digit message
    long double number = 971903;
    RSA.encrypt(number, "164783-212521");
    EXPECT_TRUE(971903 != number);

    RSA.decrypt(number, "42847-212521");
    EXPECT_EQ(971903, number);
}
TEST_F(Lab10Fixture, encrypt_num_test14) { // 5-digit message
    long double number = 97190;
    RSA.encrypt(number, "164783-212521");
    EXPECT_TRUE(97190 != number);

    RSA.decrypt(number, "42847-212521");
    EXPECT_EQ(97190, number);
}
TEST_F(Lab10Fixture, encrypt_num_test15) { // 5-digit message
    long double number = 41862;
    RSA.encrypt(number, "164783-212521");
    EXPECT_TRUE(41862 != number);

    RSA.decrypt(number, "42847-212521");
    EXPECT_EQ(41862, number);
}
//PUBLIC KEY: 7335-19549
//PRIVATE KEY: 15511-19549
TEST_F(Lab10Fixture, encrypt_num_test16) { // 5-digit message
    long double number = 41862;
    RSA.encrypt(number, "7335-19549");
    EXPECT_TRUE(41862 != number);

    RSA.decrypt(number, "15511-19549");
    EXPECT_EQ(41862, number);
}
TEST_F(Lab10Fixture, encrypt_num_test17) { // 4-digit message
    long double number = 4186;
    RSA.encrypt(number, "7335-19549");
    EXPECT_TRUE(4186 != number);

    RSA.decrypt(number, "15511-19549");
    EXPECT_EQ(4186, number);
}
TEST_F(Lab10Fixture, encrypt_num_test18) { // 4-digit message
    long double number = 9999;
    RSA.encrypt(number, "7335-19549");
    EXPECT_TRUE(9999 != number);

    RSA.decrypt(number, "15511-19549");
    EXPECT_EQ(9999, number);
}
//PUBLIC KEY: 19459-77837
//PRIVATE KEY: 139-77837
TEST_F(Lab10Fixture, encrypt_num_test19) { // 4-digit message
    long double number = 5098;
    RSA.encrypt(number, "19459-77837");
    EXPECT_TRUE(5098 != number);

    RSA.decrypt(number, "139-77837");
    EXPECT_EQ(5098, number);
}

/*
TEST_F(Lab10Fixture, encrypt_string_test){
    std::string message = "H";
    std::vector<long double> encrypted_message = RSA.encrypt_c(message, "171983-326731");

    message = '\0';
    EXPECT_TRUE( message != "H");
    message = RSA.decrypt_c(encrypted_message,"135239-326731");
    EXPECT_EQ("H", message);
}
*/


//PUBLIC KEY: 86997-507427
//PRIVATE KEY: 88453-507427
/*
TEST_F(Lab10Fixture, encrypt_string_test2){
    std::string message = "Hello world! This is a secret message!!!!!!!!!!";
    std::vector<long double> encrypted_message = RSA.encrypt_c(message, "86997-507427");

    message = '\0';
    EXPECT_TRUE( message != "Hello world! This is a secret message!!!!!!!!!!");
    message = RSA.decrypt_c(encrypted_message,"88453-507427");
    EXPECT_EQ("Hello world! This is a secret message!!!!!!!!!!", message);
}

//PUBLIC KEY: 69211-225893
//PRIVATE KEY: 4294894739-225893
TEST_F(Lab10Fixture, encrypt_string_test3){
    std::string message = "I will be changed when i become encrypted!";
    RSA.encrypt(message, "69211-225893");

    EXPECT_TRUE("I will be changed when i become encrypted!" != message);
    RSA.decrypt(message, "4294894739-225893");
    EXPECT_EQ("I will be changed when i become encrypted!", message);
}
*/