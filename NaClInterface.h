#include <iostream>

#include "crypto_box.h"
#include "crypto_secretbox.h"

class NaClInterface {
public:
    NaClInterface();

    // Functions for managing nonces
    std::string nonce();
    void set_remote_nonce(std::string nonce);
    void gen_new_nonce();

    // Functions for managing keys
    std::string public_key();
    std::string secret_key();
    void set_remote_key(std::string rk);
    void gen_new_keys();
    
    // Functions for managing shared secret
    std::string secret();
    void set_secret(std::string new_secret);
    void gen_new_secret();
    
    // Functions for public-key encryption
    std::string public_decrypt(std::string enc_msg);
    std::string public_encrypt(std::string msg);

    // Functions for shared-secret encryption 
    std::string secret_decrypt(std::string enc_msg);
    std::string secret_encrypt(std::string msg);

private:
    std::string my_nonce; // Local encryption nonce
    std::string remote_nonce; // Remote encryption nonce
    std::string my_pk; // Local public key
    std::string my_sk; // Local secret key
    std::string remote_pk; // Remote public key
    std::string my_secret; // Shared secret
};

