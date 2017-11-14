#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string getDoc();
int main(int argc, const char* argv[]) {
  bool inProgram = true;
  ifstream filestream;
     
  while(inProgram) {
    int count = 0;
    
    string line;
    string str = "";
    filestream.open("document.txt");
    
    // Reads every line in the document
    while(getline(filestream, line)) {
      str += line;
    }
    filestream.close(); 

    cout << "Document: " << str << endl;

    cout << "Enter the string to replace: ";
    string replace;
    cin >> replace;
    cout << endl;
    
    if(replace.compare("!wq") == 0) {
      cout << "Good bye." << endl;
      break;
    }
    
    cout << "Enter the string to replace with: ";
    string replaceWith;
    cin >> replaceWith;
    cout << endl;

    int pid = fork();
    wait(NULL);

    
    if(pid == 0) {
      // In child process
      
      replace(str, replace, replaceWith);      
      
      inProgram = false;
    } else if (pid > 0 ) { // In parent process
    } else {
      cout << "Error forking" << endl;
    }
  }
  return 0;
}

/** 
 * Replaces the specified string with the given replaceWith
 * string in the specified document.
 */
void replace(string document, string replace, string replaceWith) {
    size_t loc = document.find(replace);
      
      // Replace the string with the string to replace with if it still exists
      while(loc != string::npos) {
        document.replace(loc, replace.length(), replaceWith);
        count ++;
        loc = document.find(replace);
      }

      cout << "Replaced " << replace << " with " 
        << replaceWith << " " << count << " times." << endl;

      write(document);
}
/**
 * Writes the specified document to file.
 */ 
void write(string document) {
    // Writes the changes to document
    ofstream writeStream;
    writeStream.open("document.txt");
    
    writeStream << document;
    writeStream.close();
}
