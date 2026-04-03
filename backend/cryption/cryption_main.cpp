#include <iostream>
#include <filesystem>
#include "./processManagement/pM.hpp"
#include "./processManagement/tasks.hpp"

#include "cryption_main.hpp"

namespace fs = std::filesystem;
using namespace std;

QString c_main(QString file_action) {
	string directory;
	Action taskAction;

	cout << "Place it in 'files' dir at backend/cryption/files" << endl;
	directory = "files";

	QString Qaction = file_action;
	string action = Qaction.toStdString();

	fs::current_path("../../../backend/cryption");

	try {
		if (fs::exists(directory) && fs::is_directory(directory)) {
			ProcessManagement processManagement;
			for (const auto& entry : fs::recursive_directory_iterator(directory)) {  // this function in this line takes out all the directories inside the directory
				if (entry.is_regular_file()) {
					string filePath = entry.path().string();
					IO io(filePath);
					fstream f_stream = move(io.getFileStream());
					if (f_stream.is_open()) {

						if (action == "encrypt" || action == "ENCRYPT") {
							taskAction = Action::ENCRYPT;
						}
						else if (action == "decrypt" || action == "DECRYPT") {
							taskAction = Action::DECRYPT;
						}
						else {
							cout << "" << endl;
						}

						auto task = make_unique<Task>(move(f_stream), taskAction, filePath);
						processManagement.submitToQueue(move(task));
					}
					else {
						cerr << "Unable to open file" << filePath << endl;
					}
				}
			}
			processManagement.executeTask();
		}
		else {
			cerr << "Invalid directory path: " << directory << endl;
		}
	}
	catch (const fs::filesystem_error& ex) {
		cout << "Filesystem error: " << ex.what() << endl;
	}

	return 0;
}