// Encrypting - decrypting files
// Federico Moretta

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#define key 100

using namespace std;

int main(){

	char script[100], ch;
	fstream ftin, ftout;
	int todo;
	bool loop = true;

	while(loop){
		// Menù Selection
		cout << "Choose an action:" << endl,
		cout << "1. Encrypt file." << endl;
		cout << "2. Decrypt file." << endl;
		cout << "3. Exit." << endl;
		cout << " --> ";
		
		cin >> todo;

		switch(todo) {
			case 1 :

				//Encrypting Section
				//call the file 
				cout << "Enter the file name:" <<endl;
				cin >> script;

				ftin.open(script, fstream::in);

				ftout.open("tmp.txt", fstream::out);

				// Raise error
				if(!ftin){cout << "Error --> No file: " << script << " is present." << endl;}
				if(!ftout){cout << "Error --> Internal issue, enter the source to fix "<< endl;}


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

				// Raise error
				if(!ftin){cout << "Error --> Issue during encrypting, enter the source to fix" << endl;}
				if(!ftout){cout << "Error --> Internal issue, enter the source to fix "<< endl;}

				while(ftout>>noskipws>>ch){
					ftin << ch;
				}

				ftin.close();
				ftout.close();

				cout << "\nFile encrypted successfully\n" << endl;
				//remove('tmp.txt');
				break;

			case 2 :

			    //Decrypt Section
				//call the file 
				cout << "Enter the file name:" <<endl;
				cin >> script;

				ftin.open(script, fstream::out);

				ftout.open("tmp.txt", fstream::in);

				// Raise error
				if(!ftin){cout << "Error --> No file: " << script << " is present." << endl;}
				if(!ftout){cout << "Error --> Internal issue, enter the source to fix "<< endl;}

				// encrypt message loop
				while(ftout>>noskipws>>ch){
					
					// encrypting key
					ch = ch - key;
					ftin << ch;
				}

				ftout.close();
				ftin.close();

				// Raise error
				if(!ftin){cout << "Error --> Issue during encrypting, enter the source to fix" << endl;}
				if(!ftout){cout << "Error --> Internal issue, enter the source to fix "<< endl;}

				cout << "\nFile decrypted successfully\n" << endl;
				break;

			case 3 :
				loop=false;
				break;

			default:
				cout << "Invalid choice. please select one of the listed\n." <<endl;
			}
	}

	remove("tmp.txt");
	return 0;
}
