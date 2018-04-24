//
// Created by Work on 4/24/2018.
//

#ifndef CMPE126S18_LABS_RSAE_H
#define CMPE126S18_LABS_RSAE_H
//hello
namespace lab10 {
    class rsa_encrypt {
        //Emil's stuff!!
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
        //todo: encrypt message
        //todo: decrypt message
        //I wanna do this shit strings,
        //if can, with text files
        //if can, with image files
        //holy shit, encrypt a fucking jpeg down to its fucking bits,
        //the give someone a fucked up jpeg, then decrypt it to get the image

        //functions for testing
        unsigned get_prime() {return generate_prime();};


    };
}
//suck a dick!
#endif //CMPE126S18_LABS_RSAE_H
