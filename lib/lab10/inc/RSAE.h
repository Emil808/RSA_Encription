//
// Created by Work on 4/24/2018.
//

#ifndef CMPE126S18_LABS_RSAE_H
#define CMPE126S18_LABS_RSAE_H
//hello
#include <string>
#include <vector>
namespace lab10 {
    class rsa_encrypt {


        long double modulo_expo(long double message, unsigned e, unsigned n); //modular exponentiation, does message^e % n
        long double modulo_expo(char message, unsigned e, unsigned n);
        unsigned generate_prime();
        unsigned generate_totient(unsigned p, unsigned q);

        unsigned generate_coprime_to_totient(unsigned totient);
        unsigned gcd(unsigned factor_1, unsigned factor_2);
        unsigned generate_public(unsigned totient);
        unsigned generate_private(unsigned public_key, unsigned totient);
    public:

        rsa_encrypt();
        ~rsa_encrypt();

        void generate_keys();

        //whole number numerical ecryption/decryption
//        void encrypt(long double message, std::string key);
//        void decrypt(long double  message, std::string key);

        void encrypt(long double &message, std::string key);
        void decrypt(long double &message, std::string key);

        std::vector<long double> encrypt(std::string &message, std::string key);
        std::string decrypt(std::vector<long double> &encrypted_message, std::string key);
        //I wanna do this shit strings,
        //if can, with text files
        //if can, with image files
        //holy shit, encrypt a fucking jpeg down to its fucking bits,
        //the give someone a fucked up jpeg, then decrypt it to get the image

        //functions for testing
        unsigned get_prime() {return generate_prime();};
        unsigned find_gcd(unsigned a, unsigned b) {return gcd(a,b);};
        unsigned get_private(unsigned public_key, unsigned totient) {return generate_private(public_key, totient); };

        unsigned get_coprime_to_totient(unsigned totient){ return generate_coprime_to_totient(totient);};

    };
}

#endif //CMPE126S18_LABS_RSAE_H
