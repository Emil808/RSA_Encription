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
            e=rand()%(totient-2)+2;
            gcd1=gcd(e,totient);
        }
        return e;

        //generates number between 1 and totient
        // totient and coprime can only have gcd of 1

        //todo:this
        //use a random number generator, bounded between 1 and the totient
        //check e:
            //such that gcd(e, totient) = 1;
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

        //todo: this
        //d*e = 1 + k*totient
        //use a random number generator to find k, can be real number
        //d = (1 + k*totient)/e
        //return d
    }

    void rsa_encrypt::generate_keys() {
        unsigned p, q, n, totient;
        p= generate_prime();
        q = generate_prime();
        n = p*q;
        totient = generate_totient(p,q);
        unsigned e = generate_public(totient);
        unsigned d = generate_private(e, totient);

        
    }



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
}


