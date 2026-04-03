// this is a main file for signing and verfying files

#include "myevp_key.h"
#include "verify_main.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void writeFile(string name, string content) {
	ofstream out(name, ios::binary);
	out << content;
	out.close();
}

QString s_main(QString sign_action)
{
	MyEVP_Key cypher;
	QString s_action = sign_action;
	string action = s_action.toStdString();
	string folderPath = "../../../backend/cypher/files/";
	string fileName = "";
	fs::path cwd = fs::current_path();

	if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
		cout << "Current path: " << cwd.string() << endl;
		cerr << "Error: Directory not found: " << folderPath << endl;
	}

	bool fileFound = false;

	// 2. Iterate through the directory
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_regular_file()) {
			fileName = entry.path().filename().string();

			fileFound = true;
			break;
		}
	}

	if (!fileFound) {
		cerr << "Error: No files exist inside the folder: " << folderPath << endl;
	}

	// all the file names
	string original_file = fileName;
	string signature_file = "my_data.sig";
	string private_key_file = "prv_enc.pem";
	string public_key_file = "public.pem";
	string the_pass = "justapass";

	// STEP: 1 [initial setup]
	cout << "\n(1) Creating original files and generating keys...\n" << endl;

	cypher.generate_rsa_key(2048);

	// save the generated keys, private key is encryted & public key is just plain text
	cypher.write_key(private_key_file, true, the_pass);
	cypher.write_key(public_key_file, false);

	if (action == "sign") {
		// STEP: 2 [signing]
		cout << "Signing the file: " << original_file  << endl;

		if (cypher.pkey_sign(original_file, signature_file)) {
			cout << "SUCCESS: signing " << "\n" << endl;
		}
		else {
			cerr << "Error: signing the file\n" << endl;
		}
	}
	else if (action == "verify") {
		// STEP: 3 [reloading & verifying]
		cout << "Reloading public key for verification" << endl;
		// simulating a new session just by loading the public key
		cypher.load_key(public_key_file, false);

		if (cypher.pkey_verify(original_file, signature_file) == 1) {
			cout << "SUCCESS: verification" << endl;
		}
		else {
			cerr << "Error : verifying " << signature_file << "\n" << endl;
		}
	}
	else {
		cerr << action << " is not a valid action\n" << endl;
	}

	// additional step: tamper test
	//cout << "\n(4) attack scenario: modifying the contents" << endl;
	//writeFile(original_file, "Transfer bitcoin to mannu"); // changed content of the file

	//cout << "attempting verification of tampered file... " << endl;
	//if (cypher.pkey_verify(original_file, signature_file) == 1) {
	//	cerr << "WARNING: verification passed (so ur detection failed)" << endl;
	//}
	//else {
	//	cout << "SUCCESS: it detected the tampering !!" << endl;
	//}

	return 0;
}