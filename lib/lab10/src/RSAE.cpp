//
// Created by Work on 4/24/2018.
//
#include "RSAE.h"
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
namespace lab10{

    rsa_encrypt::rsa_encrypt() {}

    rsa_encrypt::~rsa_encrypt() {}

    bool isPrime(int num); //Auxilary function that checks if number is prime
    unsigned rsa_encrypt::generate_prime() {

        unsigned seed = (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();//gets system time
        std::minstd_rand0 rd1(seed);//calls random method, seeds with the system time
        unsigned random = rd1() % 1000;//calls random generator
        while (!isPrime(random)) {//checks if number is a prime
            random = rd1() % 1000;//if not, call random again
        }
        return random;//we found a random, now return
    }

    unsigned rsa_encrypt::generate_totient(unsigned p, unsigned q) {
        unsigned totient = (p - 1) * (q - 1);
        return totient;
    }

    unsigned rsa_encrypt::generate_coprime_to_totient(unsigned totient) {

        int gcd1=0;
        int e=0;
        while(gcd1!=1 && e!=1 && e!=totient)
        {
            unsigned seed = (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();//gets system time
            std::minstd_rand0 rd1(seed);//calls random method, seeds with the system time
            unsigned random = rd1() % totient;//calls random generator
            e = random;
            gcd1=gcd(e,totient);
        }
        return e;

    }
    unsigned rsa_encrypt::gcd(unsigned factor_1, unsigned factor_2) {
        if (factor_1 < factor_2) {
            unsigned temp = factor_1;
            factor_1 = factor_2;
            factor_2 = temp;
            gcd(factor_1, factor_2);
        }
        if (factor_2 == 0) {
            return factor_1;
        } else
            return gcd(factor_2, factor_1 % factor_2);
    }

    unsigned rsa_encrypt::generate_public(unsigned totient) {
        return generate_coprime_to_totient(totient);
        //to generate the public key
        //it is the coprime to the totient

    }

    unsigned rsa_encrypt::generate_private(unsigned public_key, unsigned totient) {
        //andy's implementation
        int quotient = 0;
        unsigned remainder = 0; //creates two variables and initializes them to 0
        int originalTotient = totient; // originalTotient holds the totient value since it is changes in the while loop
        unsigned x = 1;
        unsigned prevX = 0;//necessary variables for Extended Euclidean Algorithm
        unsigned temp;
        while(public_key!=0) // while the publice key (e) is not equal to 0, go through the loop
        {
            quotient = totient / public_key; // quotient holds the integer value once the totient and public key are divided
            remainder = totient % public_key; // Since the public key is relatively prime to the totient, there will be a remainder
            totient = public_key; //totient holds the public key value;
            public_key = remainder; //public key is then set to hold value from remainder
            temp = x; // temp holds the value from x, since it will be changes in the next line
            x = prevX - (quotient * x);
            prevX = temp;
        }
        //This while loop performs the Extended Euclidean Alogorithm. The main purpose of the alogrithm
        //is to determine the modular multiplicative inverse of two coprime numbers. In our case, the totient
        //and public key are coprime with eachother and this allows us to use this algorithm. The euclidean algorithm
        //can be used to find the GCD of two numbers. The algoritm works by dividing repeatedly dividing the divisor
        //by the remainder until the remainder becomes 0. The remainder before the zero-remainder is the gcd of the two
        //numbers. By using the extended Euclidean algorithm however, we do the Euclidean algorithm in reverse order
        //to find bezouts coefficients.
        while(prevX < 0) // If the private key is negative
        {
            prevX = prevX+originalTotient; // add the totient value to the public key until it become positive
        }
        return prevX;

    }

    long double rsa_encrypt::modulo_expo(long double message, unsigned e, unsigned n){
        //this returns the result of messgae^e % n
        if (n == 1) return 0;
        //Assert :: (modulus - 1) * (modulus - 1) does not overflow base
        long double result = 1;
        message = fmodl(message, n);
        while (e > 0) {
            if (e % 2 == 1)
                result = fmodl((result * message),n);
            e = e >> 1;
            message = fmodl((message * message),n);
        }
        return result;
    }

    char rsa_encrypt::modulo_expo(char message, unsigned e, unsigned n){
        if (n == 1) return 0;
        //Assert :: (modulus - 1) * (modulus - 1) does not overflow base
        long double encrypted_char = (long double) message;

        long double result = 1;
        encrypted_char = fmodl(encrypted_char, n);
        while (e > 0) {
            if (e % 2 == 1)
                result = fmodl((result * encrypted_char),n);
            e = e >> 1;
            encrypted_char = fmodl((encrypted_char * encrypted_char),n);
        }
        return (char) encrypted_char;
    };
    void rsa_encrypt::generate_keys() {
        unsigned p, q, n, totient;
        p = generate_prime();
        q = generate_prime();
        n = p*q;
        totient = generate_totient(p,q);
        unsigned e = generate_public(totient);
        unsigned d = generate_private(e, totient);

        //save keys to a txt file to then share?
        std::cout <<"PUBLIC KEY: " << e << "-" << n << std::endl
                  <<"PRIVATE KEY: "<< d << "-" << n << std::endl;
    }


//    void rsa_encrypt::encrypt(long double message, std::string key) {
//        long double e = parse_key(key);
//        long double n = parse_key(key);
//        long double encrypted = modulo_expo(message, e, n);
//        std::cout<< "Encrypted Message: "  << encrypted << std::endl;
//    };
//    void rsa_encrypt::decrypt(long double message, std::string key) {
//        long double d = parse_key(key);
//        long double n = parse_key(key);
//        long double encrypted = modulo_expo(message, d, n);
//        std::cout << "Decrypted Message: " << encrypted << std::endl;
//    };

    unsigned parse_key(std::string &key);
    void rsa_encrypt::encrypt(long double &message, std::string key) {//numerical number encryption
        unsigned e = parse_key(key);
        unsigned n = parse_key(key);
        message = modulo_expo(message, e, n);

    };
    void rsa_encrypt::decrypt(long double &message, std::string key) {
        unsigned d = parse_key(key);
        unsigned n = parse_key(key);
        message = modulo_expo(message, d, n);

    };

    void rsa_encrypt::encrypt(std::string &message, std::string key){//string encryption
        unsigned e = parse_key(key);
        unsigned n = parse_key(key);
        std::string encrypted;
        //figure this out

    };
    void rsa_encrypt::decrypt(std::string &message, std::string key){
        unsigned d = parse_key(key);
        unsigned n = parse_key(key);

    };

    //auxillary
    bool isPrime(int num) {
        bool prime = true;
        if (num <= 1) {
            return (prime = false);
        } else if (num == 2) {
            return prime;
        } else if (num % 2 == 0) {
            return (prime = false);
        } else {
            int modBy = 3;
            int limit = static_cast<int>(sqrt(num) + 1);
            while (modBy <= limit) {
                if (num % modBy == 0) {
                    prime = false;
                }
                modBy += 2;
            }
            return prime;
        }
    }

    unsigned parse_key(std::string &input){
        std::string key_string;

        while(isdigit(input[0]) && input[0] != '\0'){
            key_string.push_back(input[0]);
            input.erase(0, 1);
        }
        if(input[0] == '-')
            input.erase(0,1);

        unsigned key = atoi(key_string.c_str());
        return key;

    }
}


