#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void replaceString(string, string, string);
void write(string);
string getDocument();

int main(int argc, const char* argv[]) {
    bool inProgram = true;
    
    while(inProgram) {
                
        string str = getDocument();
        
        cout << "\nDocument: " << str << endl << endl;

        cout << "Enter the string to replace: ";
        string replace;
        string line;
        getline(cin, replace);
        cout << endl;
        
        if(replace.compare("!wq") == 0) {
            cout << "Good bye." << endl;
            break;
        }
        
        cout << "Enter the string to replace with: ";
        string replaceWith;
        getline(cin, replaceWith);
        cout << endl;

        int pid = fork();
        wait(NULL);
        
        if(pid == 0) {
            // In child process
            replaceString(str, replace, replaceWith);      
            
            inProgram = false;
        } else if (pid > 0 ) { // In parent process
            cin.clear();
        } else {
            cout << "Error forking" << endl;
        }
    }
    return 0;
}

/** 
 * Replaces the specified string with the given replaceWith
 * string in the specified document.
 * @param document The string representation of the document.
 * @param replace The string to be replaced in the document.
 * @param replaceWith The string that's replacing the specified
 *      replace string.
 */
void replaceString(string document, string replace, string replaceWith) {
    size_t loc = document.find(replace);
    int count = 0; // The number of times the string was replaced.
 
    // Replace the string with the string to replace with if it still exists
    while(loc != string::npos) {
        document.replace(loc, replace.length(), replaceWith);
        count ++;

        loc += replace.length();
        loc = document.find(replace, loc);
    }
  
    while(count == 0) {
      cout << "." << endl;
    }

    cout << "Replaced " << replace << " with " 
      << replaceWith << " " << count << " times." << endl;

    write(document);
}
/**
 * Writes the specified document to file.
 * @param document The string object of the document
 *      to be written to file.
 */ 
void write(string document) {
    // Writes the changes to document
    ofstream writeStream;
    writeStream.open("document.txt");
    
    writeStream << document;
    writeStream.close();
}

/**
 * Reads the document from file and returns a
 * string of its contents.
 * @ return A string representation of the document.
 */
string getDocument() {
    ifstream filestream;
    string line; 
    string str = "";

    filestream.open("document.txt");
    
    // Reads every line in the document
    while(getline(filestream, line)) {
      str += line;
    }
    filestream.close(); 
    
    return str;
}
