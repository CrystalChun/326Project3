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
    //string str(getDoc());
  
  while(inProgram) {
    int count = 0;
    filestream.open("document.txt");
    string line;
    string str = "";
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
      size_t loc = str.find(replace);
      
      while(loc != string::npos) {
        str.replace(loc, replace.length(), replaceWith);
        count ++;
        loc = str.find(replace);
      }
      cout << "Replaced " << replace << " with " 
        << replaceWith << " " << count << " times." << endl;
      ofstream writeStream;
      writeStream.open("document.txt");
      writeStream << str;
      writeStream.close();
      inProgram = false;
    } else if (pid > 0 ) {
    } else {
      cout << "Error forking" << endl;
    }
  }
  return 0;
}
string getDoc() {
  string s = "Hello world! My name is June and my dog is doing just fine.";
  return s;
}


