#include <iostream>
#include "file_cyption.hpp"
#include "../processManagement/tasks.hpp"
#include "../file_handling/ReadFromEnv.cpp"

using namespace std;

int file_encryption(const string &taskData)
{
    Task task = Task::fromString(taskData);
    ReadEnv env;

    string envKey = env.getenv();
    int key = stoi(envKey);

    char ch;
    int file_no = 0;
    auto& fs = task.f_stream;

    // setting the stream
    fs.clear();
    fs.seekg(0, ios::beg);
    fs.seekp(0, ios::beg);

    while (true) {
        std::streampos readPos = fs.tellg();

        if (!fs.get(ch)) break;  // stop at EOF

        // Modify character
        if (task.action == Action::ENCRYPT)
            ch = (ch + key) % 256;
        else if (task.action == Action::DECRYPT)
            ch = (ch - key + 256) % 256;

        // Move write pointer to the character we just read
        fs.seekp(readPos);

        fs.put(ch);

        // Move read pointer to next character
        fs.seekg(readPos + streamoff(1));
        file_no += 1;
    }

    fs.close();

    if (task.action == Action::ENCRYPT)
        cout << "File " << file_no << " has been encrypted" << endl;
    else
        cout << "File " << file_no << " has been decrypted" << endl;

    return 0;
}

// first, u get a task, then u get the env, read it,
// apply an ecryption algorithm, and an decryption algrorithm .

// caused me a lot of headaches

// nope. the older version of the cryption algorithm had a major flaw.

 /*
     if (task.action == Action::ENCRYPT) {
        char ch;
        while (task.f_stream.get(ch)) {
            ch = (ch + key) % 256;
            task.f_stream.seekp(-1, ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
        }
    else {
        char ch;
        while (task.f_stream.get(ch)) {
            ch = (ch - key + 256) % 256;
            task.f_stream.seekp(-1, ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
*/

/* the older version as u can see above used to
   1. check the action,
   2. create a loop of .get() - this is used to read the byte. this loop whould read the byte of the file by f_stream
   3. change the byte according to the key.
   3.5 seek back to the previous byte and make it current pos
   4. write the changed byte into the file
   5. then, repeat the loop

   but the read position would be the unchanged bcoz the read ptr would not be pushed forward.
   and the write ptr would go forward, while read went backward and backwards. then BOOM!!
*/

/*
    But, the newer version does this:
    We explicitly control both pointers:

    Step	                    Pointer

    tellg()                 	save read position
    get()	                    read 1 byte
    seekp(readPos)	            go back to overwrite
    put()	                    write
    seekg(readPos + 1)	        move forward

    the read ptr is saved and write moves according to the saved read ptr
*/