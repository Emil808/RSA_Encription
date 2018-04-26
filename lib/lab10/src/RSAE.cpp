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
        unsigned random = rd1();//calls random generator
        while (!isPrime(random)) {//checks if number is a prime
           // srand(static_cast<unsigned int>(time(0)));
           // random = static_cast<unsigned int>(rand());
            random = rd1();//if not, call random again
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
            e=rand()%(totient-2)+2; //this makes sure e will not be 1 or totient (1<e<totient)
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

    void rsa_encrypt::generate_keys() {
        unsigned p, q, n, totient;
        p= generate_prime();
        q = generate_prime();
        n = p*q;
        totient = generate_totient(p,q);
        unsigned e = generate_public(totient);
        unsigned d = generate_private(e, totient);

        //save keys to a txt file to then share.
        std::cout <<"PUBLIC KEY: " << e << "-" << n << std::endl
                  <<"PRIVATE KEY: "<< d << "-" << n << std::endl;
    }


    unsigned parse_key(std::string &key);
    void rsa_encrypt::encrypt(unsigned message, std::string key) {
        unsigned e = parse_key(key);
        unsigned n = parse_key(key);

        std::cout<< "Encrypted Message: " << (unsigned)pow(message, e) % n << std::endl;
    };
    void rsa_encrypt::decrypt(unsigned message, std::string key) {
        unsigned d = parse_key(key);
        unsigned n = parse_key(key);

        std::cout << "Decrypted Message: " << (unsigned) pow(message, d) % n << std::endl;
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
        unsigned key;

        while(input[0] != '-' || input[0] != '\0'){
            key = (unsigned) atoi(&input[0]);
            input.erase(0, 1);
        }
        if(input[0] == '-')
            input.erase(0,1);

        return key;

    }
}


