//
// Created by Work on 4/24/2018.
//

#ifndef CMPE126S18_LABS_RSAE_H
#define CMPE126S18_LABS_RSAE_H
//hello
#include <string>
namespace lab10 {
    class rsa_encrypt {

        unsigned generate_prime();//Fuk?
        unsigned generate_totient(unsigned p, unsigned q);

        unsigned generate_coprime_to_totient(unsigned totient);
        unsigned gcd(unsigned factor_1, unsigned factor_2);
        unsigned generate_public(unsigned totient);
        unsigned generate_private(unsigned public_key, unsigned totient);
    public:

        rsa_encrypt();
        ~rsa_encrypt();
        //todo: generate keys
        void generate_keys();
        //todo: encrypt message
        //whole number numerical ecryption/decryption
        void encrypt(unsigned message, std::string key);
        void decrypt(double  message, std::string key);
        //todo: decrypt message
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
//suck a dick!
#endif //CMPE126S18_LABS_RSAE_H
