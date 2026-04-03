#include "myevp_key.h"
using namespace std;

MyEVP_Key::MyEVP_Key() : pkey(nullptr) {}

MyEVP_Key::~MyEVP_Key() {
	if (pkey) EVP_PKEY_free(pkey);
}

EVP_PKEY* MyEVP_Key::generate_rsa_key(unsigned int key_bits) {
	// ctx is basically a workspace for hashing. it maintains 
	// the internal state of the hash while u feed it data.
	
	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	EVP_PKEY_keygen_init(ctx);
	EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_bits);
	EVP_PKEY_keygen(ctx, &pkey);
	EVP_PKEY_CTX_free(ctx);
	return pkey;
}

// to write the key in pem file so it doesn;t get lost
void MyEVP_Key::write_key(string key_file, bool is_private, string password) {
	if (!pkey) {
		return;
	}

	// create a file bio
	BIO* bio_out = BIO_new_file(key_file.c_str(), "w");
	if (!bio_out) return;

	if (is_private) {
		// writes the private key
		// password encyption used - aes-256
		if (!password.empty()) {
			PEM_write_bio_PrivateKey(bio_out, pkey, EVP_aes_256_cbc(), (unsigned char*)password.c_str(), password.length(), NULL, NULL);
			cout << "Private Key saved (encryted with password) to : " << key_file << endl;
		}
		else {
			// writes without a password
			PEM_write_bio_PrivateKey(bio_out, pkey, NULL, NULL, 0, NULL, NULL);
			cout << "Private Key saved without password to : " << key_file << endl;
		}
	}
	else {
		// public keys are not protected
		PEM_write_bio_PUBKEY(bio_out, pkey);
		cout << "Public key saved to : " << key_file << "\n" << endl;
	}

	BIO_free(bio_out);
}

// to load the written key
void MyEVP_Key::load_key(string key_file, bool is_private, string password) {
	// if a key is already loaded, free it first
	if (pkey) {
		EVP_PKEY_free(pkey);
		pkey = nullptr;
	}

	BIO* bio_in = BIO_new_file(key_file.c_str(), "rb");
	if (!bio_in) {
		cerr << "Could not open file: " << key_file << endl;
		return;
	}

	if (is_private) {
		// openssl handles the decryption using the password
		pkey = PEM_read_bio_PrivateKey(bio_in, NULL, NULL, (void*)password.c_str());
	}
	else {
		pkey = PEM_read_bio_PUBKEY(bio_in, NULL, NULL, NULL);
	}

	BIO_free(bio_in);

	if (!pkey) {
		cerr << "Error: Failed to load key. Check the password" << endl;
	}
}

// for creating a hash
unsigned int MyEVP_Key::load_to_md(unsigned char* md_value, string file_name) {
	BIO* bio_in = BIO_new_file(file_name.c_str(), "rb");
	if (!bio_in) return 0;

	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	unsigned char inBuffer[4096];
	int inByte = 0;
	unsigned int md_len = 0;

	// takes the file and reads it in chunks instead of loading the whole file into ram
	EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	while ((inByte = BIO_read(bio_in, inBuffer, sizeof(inBuffer))) > 0) {
		EVP_DigestUpdate(mdctx, inBuffer, inByte);
	}

	EVP_DigestFinal_ex(mdctx, md_value, &md_len);

	EVP_MD_CTX_free(mdctx);
	BIO_free(bio_in);
	return md_len;
}

// for signing the document
int MyEVP_Key::pkey_sign(string org_file, string sign_file) {
	unsigned char md_buffer[EVP_MAX_MD_SIZE];
	unsigned int md_len = load_to_md(md_buffer, org_file);
	if (md_len <= 0) return 0;

	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, NULL);
	EVP_PKEY_sign_init(ctx);
	EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
	EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256());

	size_t sign_len;
	EVP_PKEY_sign(ctx, NULL, &sign_len, md_buffer, md_len); // to get the size of the signature from openssl
	unsigned char* sign_buffer = (unsigned char*)OPENSSL_malloc(sign_len);

	int rc = EVP_PKEY_sign(ctx, sign_buffer, &sign_len, md_buffer, md_len);  // signing takes place

	// if success, make a signature file and update the sign
	if (rc > 0) {
		BIO* bio_out = BIO_new_file(sign_file.c_str(), "wb");
		BIO_write(bio_out, sign_buffer, sign_len);
		BIO_free(bio_out);
	}

	OPENSSL_free(sign_buffer);
	EVP_PKEY_CTX_free(ctx);
	return (rc > 0) ? 1 : 0;
}

// for verigying a signature
// first, u hash the original document again, then get the hash
// then, verifying by decypting with the public key

int MyEVP_Key::pkey_verify(string org_file, string sign_file) {
	// re-hash the og doc
	unsigned char md_buffer[EVP_MAX_MD_SIZE];
	unsigned int md_len = load_to_md(md_buffer, org_file);

	// load signature from file
	BIO* bio_sign = BIO_new_file(sign_file.c_str(), "rb");
	if (!bio_sign) return 0;

	unsigned char sign_buffer[512]; //adjust based on file size
	int sign_len = BIO_read(bio_sign, sign_buffer, sizeof(sign_buffer));
	BIO_free(bio_sign);

	// verify
	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, NULL);
	EVP_PKEY_verify_init(ctx);
	EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
	EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256());

	int rc = EVP_PKEY_verify(ctx, sign_buffer, sign_len, md_buffer, md_len);

	EVP_PKEY_CTX_free(ctx);

	return rc;

}

// output : 0 - success
//			1 - failure
//			<0 - full wrong
