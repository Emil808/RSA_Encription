//
// Created by Work on 4/24/2018.
//
#include "RSAE.h"
#include <cmath>
#include <cstdlib>
//#include <ctime>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
namespace lab10{
    bool isPrime(int num); //Auxilary function that checks if number is prime

    rsa_encrypt::rsa_encrypt() {}

    rsa_encrypt::~rsa_encrypt() {}

    unsigned rsa_encrypt::generate_prime() {
        //std::srand((unsigned)time(0));
        unsigned seed = (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();//gets system time
        std::minstd_rand0 rd1(seed);//calls random method, seeds with the system time
        unsigned random = rd1() % 100;//calls random generator
        while (!isPrime(random)) {//checks if number is a prime
           // srand(static_cast<unsigned int>(time(0)));
           // random = static_cast<unsigned int>(rand());
            random = rd1() % 100;//if not, call random again
        }
        return random;//we found a random, now return
    }

    unsigned rsa_encrypt::generate_totient(unsigned p, unsigned q) {
        unsigned totient = (p - 1) * (q - 1);
        return totient;
    }

    //todo:confirm correct key generation
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
        //d = prvate key
        //de mod totient = 1

        //one way
        //d*e = 1 + k*totient
        //use a random number generator to find k, can be real number
        //while gcd e,d != 1
             //d = (1 + k*totient)/e
        //return d

        //Emil's way
        /*
        unsigned d;
        unsigned k = 0;
        do{
            ++k;
            d = (1+ k*totient) / public_key;
        }while( (d*public_key % totient) != 1);
        return d;

*/
        //andy's implementation

        int quotient = 0;
        int remainder = 0; //creates two variables and initializes them to 0
        int originalTotient = totient; // originalTotient holds the totient value since it is changes in the while loop
        int x = 1;
        int prevX = 0;//necessary variables for Extended Euclidean Algorithm
        int temp;
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

    long double rsa_encrypt::exp_by_squ(long double base, unsigned expo){
        if(expo < 0) return exp_by_squ(1 / base, -expo);
        else if (expo == 0) return  1;
        else if (expo == 1) return  base;
        else if (expo % 2 == 0) return exp_by_squ(base * base,  expo / 2);
        else if (expo % 2 != 0) return base * exp_by_squ(base * base, (expo - 1) / 2);
    }

    long double rsa_encrypt::modulo_expo(long double message, unsigned e, unsigned n){
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
    void rsa_encrypt::generate_keys() {
        unsigned p, q, n, totient;
        p = generate_prime();
        q = generate_prime();
        n = p*q;
        totient = generate_totient(p,q);
        unsigned e = generate_public(totient);
        unsigned d = generate_private(e, totient);

        //save keys to a txt file to then share.
        std::cout <<"PUBLIC KEY: " << e << "-" << n << std::endl
                  <<"PRIVATE KEY: "<< d << "-" << n << std::endl;
    }


    long double parse_key(std::string &key);
    void rsa_encrypt::encrypt(long double message, std::string key) {
        long double e = parse_key(key);
        long double n = parse_key(key);
//        long double encrypted = exp_by_squ(message, e);
//        encrypted = fmodl(encrypted, n);
        long double encrypted = modulo_expo(message, e, n);
        std::cout<< "Encrypted Message: "  << encrypted << std::endl;
    };
    void rsa_encrypt::decrypt(long double message, std::string key) {
        long double d = parse_key(key);
        long double n = parse_key(key);
//        long double encrypted = exp_by_squ(message, d);
//        encrypted = fmodl(encrypted, n);
        long double encrypted = modulo_expo(message, d, n);
        std::cout << "Decrypted Message: " << encrypted << std::endl;
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

    long double parse_key(std::string &input){
        std::string key_string;

        while(isdigit(input[0]) && input[0] != '\0'){
            key_string.push_back(input[0]);
            input.erase(0, 1);
        }
        if(input[0] == '-')
            input.erase(0,1);

        long double key = atoi(key_string.c_str());
        return key;

    }
}


