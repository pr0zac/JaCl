#include "NaClInterface.h"

NaClInterface::NaClInterface()
{
    gen_new_nonce();
    gen_new_keys();
    gen_new_secret();
}

std::string NaClInterface::nonce()
{
    return my_nonce;
}

void NaClInterface::set_remote_nonce(std::string nonce)
{
    remote_nonce = nonce;
}

void NaClInterface::gen_new_nonce()
{
    char nonce_array[crypto_box_NONCEBYTES+1];
    for (int i = 0; i < crypto_box_NONCEBYTES; ++i)
    {
        nonce_array[i] = (rand() % 254) + 1;
    }
    nonce_array[crypto_box_NONCEBYTES] = 0;
    my_nonce = nonce_array;
}

std::string NaClInterface::public_key()
{
    return my_pk;
}

std::string NaClInterface::secret_key()
{
    return my_sk;
}

void NaClInterface::set_remote_key(std::string rk)
{
    remote_pk = rk;
}

void NaClInterface::gen_new_keys()
{
    my_pk = crypto_box_keypair(&my_sk);
}

std::string NaClInterface::secret()
{
    return my_secret;
}

void NaClInterface::set_secret(std::string new_secret)
{
    my_secret = new_secret;
}

void NaClInterface::gen_new_secret()
{
    char secret_array[crypto_secretbox_KEYBYTES+1];
    for (int i = 0; i < crypto_secretbox_KEYBYTES; ++i)
    {
        secret_array[i] = (rand() % 254) + 1;
    }
    secret_array[crypto_secretbox_KEYBYTES] = 0;
    my_secret = secret_array;
}

std::string NaClInterface::public_decrypt(std::string enc_msg)
{
    try
    {
        std::string encrypted_message = enc_msg;
        std::string message = crypto_box_open(encrypted_message, my_nonce, remote_pk, my_sk);
        return message;
    }
    catch (int e)
    {
        return "";
    }
}

std::string NaClInterface::public_encrypt(std::string msg)
{
    try
    {
        std::string message = msg;
        std::string encrypted_message = crypto_box(message, remote_nonce, remote_pk, my_sk);
        return encrypted_message;
    }
    catch (int e)
    {
        return "";
    }
}

std::string NaClInterface::secret_decrypt(std::string enc_msg)
{
    try
    {
        std::string encrypted_message = enc_msg;
        std::string message = crypto_secretbox_open(encrypted_message, my_nonce, my_secret);
        return message;
    }
    catch (int e)
    {
        return "";
    }
}

std::string NaClInterface::secret_encrypt(std::string msg)
{
    try
    {
        std::string message = msg;
        std::string encrypted_message = crypto_secretbox(message, remote_nonce, my_secret);
        return encrypted_message;
    }
    catch (int e)
    {
        return "";
    }
}

