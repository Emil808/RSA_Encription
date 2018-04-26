//
// Created by Work on 4/24/2018.
//
#include "RSAE.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace lab10 {
    bool isPrime(int num); //Auxilary function that checks if number is prime

    rsa_encrypt::rsa_encrypt() {}

    rsa_encrypt::~rsa_encrypt() {}

    unsigned rsa_encrypt::generate_prime() {
        srand(time(NULL));
        unsigned random = static_cast<unsigned int>(rand());
        while (!isPrime(random)) {
            srand(static_cast<unsigned int>(time(NULL)));
            random = static_cast<unsigned int>(rand());
        }
        return random;
    }

    unsigned rsa_encrypt::generate_totient(unsigned p, unsigned q) {
        unsigned totient = (p - 1) * (q - 1);
        return totient;
    }

    unsigned rsa_encrypt::generate_coprime_to_totient(unsigned totient) {
        //generates number between 1 and totient
        // totient and coprime can only have gcd of 1
        //use gcd function in here

    }
    //paolos comment

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
        //1 < e < totient
        //such that gcd(e, totient) = 1;
    }

    unsigned rsa_encrypt::generate_private(unsigned public_key, unsigned totient) {
        int quotient = 0;
        int remainder = 0;
        int originalTotient = totient;
        int x = 1;
        int prevX = 0;
        int temp;
        while(public_key!=0)
        {
            quotient = totient / public_key;
            remainder = totient % public_key;
            totient = public_key;
            public_key = remainder;
            temp = x;
            x = prevX - (quotient * x);
            prevX = temp;
        }
        while(prevX < 0)
        {
            prevX = prevX+originalTotient;
        }
        return prevX;
    }


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
//Whasgood


