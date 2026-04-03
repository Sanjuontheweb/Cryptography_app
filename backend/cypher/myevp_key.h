#ifndef MYEVP_KEY_H
#define MYEVP_KEY_H

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <iostream>
#include <string>
#include <vector>

class MyEVP_Key {
private:
	EVP_PKEY* pkey;

public:
	MyEVP_Key();
	~MyEVP_Key();

	// key management 

	EVP_PKEY* generate_rsa_key(unsigned int key_bits);

	// added password protection
	void write_key(std::string key_file, bool is_private = true, std::string password = "");
	void load_key(std::string key_file, bool is_private = true, std::string password = "");

	// helper for hasing 
	unsigned int load_to_md(unsigned char* md_value, std::string file_name);

	//signing and verifying
	int pkey_sign(std::string org_file, std::string sign_file);
	int pkey_verify(std::string org_file, std::string sign_file);
};

#endif