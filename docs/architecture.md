Cryptography Application – Architecture

1. Overview

The Cryptography Application is a C++ program that allows users to encrypt and decrypt files, generate hashes, and create digital signatures.
It is designed with a modular structure that separates the user interface from the cryptographic logic.

The application uses established cryptographic libraries such as **OpenSSL**, **Crypto++**, and **Boost**.

---

2. System Structure

The project is divided into several main components:

* App – Handles user interaction through a GUI or command line interface.
* Backend – Contains the cryptographic algorithms and core application logic.
* External – Stores third-party libraries used by the application.
* Resources – Application assets such as icons or configuration files.
* Tests – Unit tests for verifying cryptographic functions.

---

3. Component Responsibilities

 Application Layer (app)

Responsible for interacting with the user.

Functions include:

* file selection
* key input
* triggering encryption or decryption
* displaying results and errors

---

Cryptography Engine (backend)

The backend implements the cryptographic functionality of the system.

Main capabilities include:

* file encryption and decryption
* hashing
* digital signature generation and verification

Supported algorithms include:

* AES
* RSA
* Blowfish
* MD5
* SHA-256

---

External Libraries (external)

The project relies on well-tested libraries for cryptographic operations:

* OpenSSL – cryptographic primitives and secure algorithms
* Crypto++ – additional cryptographic implementations
* Boost – utility libraries and data structures

---

4. Data Flow

Typical workflow:

1. User selects a file
2. User chooses an operation (encrypt, decrypt, hash, sign)
3. Application forwards the request to the backend
4. Backend processes the operation using the cryptographic library
5. The result is written to disk or displayed to the user

---

5. Security Considerations

The application follows several security practices:

* use of established cryptographic libraries
* separation of UI and cryptographic logic
* avoidance of custom cryptographic implementations
* secure handling of encryption keys

---

6. Build Structure

The project is organized into multiple modules to keep the code maintainable and scalable.

Example layout:

```
app/
backend/
resources/
tests/
docs/
```

---

7. Future Improvements

Possible future extensions include:

* key management features
* password-based key derivation
* additional encryption algorithms
* extended testing and validation
