#ifndef  TASKS_HPP
#define  TASKS_HPP

#include <iostream>
#include <string>
#include "../file_handling/IO.hpp"
#include <sstream>

enum class Action {
	ENCRYPT,
	DECRYPT
};

struct Task {
	std::string file_path;
	std::fstream f_stream;
	Action action;

	// this type is used in cpp for assigning parameters to variables
	Task(std::fstream&& stream, Action act, std::string file_path) : f_stream(std::move(stream)), action(act), file_path(file_path) {}

	std::string toString() {
		std::ostringstream oss;
		oss << file_path << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");

		return oss.str();
	}

	static Task fromString(const std::string &taskData) {
		std::string file_path;
		std::string actionStr;
		std::istringstream iss(taskData);

		// ex: task: "task.txt,ENCRYPT"
		if (std::getline(iss, file_path, ',') && std::getline(iss, actionStr)) {
			Action action = (actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
			IO io(file_path);
			std::fstream f_stream = std::move(io.getFileStream());
			if (f_stream.is_open()) {
				return Task(std::move(f_stream), action, file_path);
			}
			else {
				throw std::runtime_error("Failed to open file" + file_path);
			}
		}
		else {
			throw std::runtime_error("Task couldn't be created");
		}

	}

	// now, the en/decryption class, will create tasks, which will have filepath, filename and action. which will be adopted by a process management.
	// the pM(process Management) will create a new process child from it.
	// for the sake of learning, serialization / deserialization wil be used.

	// by adding &var_name, the value of the var_name will be passed by reference
};

#endif