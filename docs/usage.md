Cryptography Application – Usage

1. Overview

The Cryptography Application allows users to perform common cryptographic operations on files, including encryption, decryption, hashing, and digital signatures.

The application uses secure cryptographic libraries to ensure reliable and safe operations.

---

2. Running the Application

1. Build the project using Microsoft Visual Studio (MSVC).
2. Launch the application executable generated after compilation.

Depending on the implementation, the program may run as:

* a graphical application (GUI)
* a command line application (CLI)

---

3. Encrypting a File

Steps:

1. Open the application.
2. Select the **Encrypt** option.
3. Choose the file to encrypt.
4. Enter the encryption key or password.
5. Select the encryption algorithm (AES, RSA, or Blowfish).
6. Start the encryption process.

The encrypted file will be saved to the selected output location.

---

4. Decrypting a File

Steps:

1. Select the **Decrypt** option.
2. Choose the encrypted file.
3. Enter the decryption key or password.
4. Start the decryption process.

The original file will be restored if the correct key is provided.

---

5. Hashing a File

Hashing generates a unique fingerprint for a file.

Steps:

1. Select the **Hash** option.
2. Choose the file.
3. Select the hashing algorithm (MD5 or SHA-256).
4. Generate the hash value.

The resulting hash will be displayed in the application.

---

6. Digital Signatures

Digital signatures verify the authenticity of a file or message.

Steps:

1. Select **Sign File**.
2. Choose the file to sign.
3. Provide the private key.
4. Generate the digital signature.

To verify a signature:

1. Select **Verify Signature**.
2. Choose the file and signature.
3. Provide the public key.
4. Run verification.

---

7. Supported Algorithms

Encryption algorithms:

* AES
* RSA
* Blowfish

Hashing algorithms:

* MD5
* SHA-256

---

8. Error Handling

Common errors may occur due to:

* incorrect encryption keys
* unsupported file formats
* corrupted input files
* missing cryptographic libraries

The application will display an appropriate error message when such issues occur.

---

9. Best Practices

For secure usage:

* use strong encryption keys
* avoid sharing private keys
* verify digital signatures before trusting files
* store encrypted files securely
