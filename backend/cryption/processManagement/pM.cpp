#include <iostream>
#include <cstring>
#include "pM.hpp"
//#include <sys/wait.h>
#include "../encyptDecrypt/file_cyption.hpp"

using namespace std;

ProcessManagement::ProcessManagement(){}

bool ProcessManagement::submitToQueue(unique_ptr<Task> task) {
	taskQueue.push(move(task));
	return true;
}

void ProcessManagement::executeTask() {
	while (!taskQueue.empty()) {
		unique_ptr<Task> taskToExec = move(taskQueue.front());
		taskQueue.pop();
		file_encryption(taskToExec->toString());
	}
}

// the process manager will push any task handed to a queue, which contains a unique pointeer
// then, the task is fetched from first & given to the file_encryption for encryption