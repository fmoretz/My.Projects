// Encrypting - decrypting files
// Federico Moretta

#include <iostream>
#include <fstream>
#include <stdio.h>
#define key 100

using namespace std;

int main(){

	char script[100], ch;
	fstream ftin, ftout;
	int todo;

	// Menù Selection
	cout << "Choose an action:" << endl,
	cout << "1. Encrypt file." << endl;
	cout << "2. Decrypt file." << endl;
	cout << "3. Exit." << endl;

	cin >> todo;

	switch(todo) {
		case 1 :

			//Encrypting Section
			//call the file 
			cout << "Enter the file name:" <<endl;
			cin >> script;

			ftin.open(script, fstream::in);

			ftout.open("tmp.txt", fstream::out);

			// encrypt message loop
			while(ftin>>noskipws>>ch){
				
				// encrypting key
				ch = ch + key;
				ftout << ch;
			}

			ftout.close();
			ftin.close();

			//copyng in the original file the encrypt code
			ftin.open(script, fstream::out);
			ftout.open("tmp.txt", fstream::in);

			while(ftout>>noskipws>>ch){
				ftin << ch;
			}

			ftin.close();
			ftout.close();

			cout << "\nFile encrypted successfully" << endl;
			//remove('tmp.txt');
			break;

		case 2 :

		    //Decrypt Section
			//call the file 
			cout << "Enter the file name:" <<endl;
			cin >> script;

			ftin.open(script, fstream::out);

			ftout.open("tmp.txt", fstream::in);

			// encrypt message loop
			while(ftout>>noskipws>>ch){
				
				// encrypting key
				ch = ch - key;
				ftin << ch;
			}

			ftout.close();
			ftin.close();

			cout << "\nFile decrypted successfully" << endl;
			break;

		case 3 :

			break;
	}

	return 0;
}
