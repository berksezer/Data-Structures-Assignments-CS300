#include <iostream>
#include <string>
#include "bst2.h"
#include <fstream>
#include "Avl.h"

using namespace std;


int displayMainMenu(){

	int choice;
	cout <<	"Please enter an input between [1 - 6]:" << endl;
	cout << "1- Display the sections [AVL]" << endl;
	cout << "2- Display the sections [BST]" << endl;
	cout << "3- Select a section" << endl;
	cout << "4- Add new section" << endl;
	cout << "5- Delete a section" << endl;
	cout << "6- Exit" << endl;
	cout << "Input: ";
	cin >> choice;
	cout << endl;

	return choice;

}

int displaySectionMenu() {
	int choice;
	cout <<	"Please enter an input between [1 - 7]:" << endl;
	cout << "1- Display the items [AVL]" << endl;
	cout << "2- Display the items [BST]" << endl;
	cout << "3- Display the information of a item" << endl;
	cout << "4- Add new item" << endl;
	cout << "5- Update the information of a item"  << endl;
	cout << "6- Delete an item" << endl;
	cout << "7- Return to main menu" << endl;
	cout << "Input: ";
	cin >> choice;
	cout << endl;

	return choice;
}

void useSectionMenu(BinarySearchTree<BinarySearchTree<string> > & bstnotebook, AvlTree<AvlTree<string>> & avlnotebook, string sec_title) {
	int choice = 0;
	choice = displaySectionMenu();
	while(choice != 7) {
		if(choice == 1) {
			cout << "******" << endl;
			avlnotebook.find(sec_title).printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		if(choice == 2) {
			cout << "******" << endl;
			bstnotebook.find(sec_title).printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		if(choice == 3) {
			string title;
			cout << "Enter the title of the item: ";
			cin >> title;

			if(!bstnotebook.find(sec_title).isThere(title)) {
				cout << "Invalid title."<< endl;
			}

			else {
				string data;
				data = bstnotebook.find(sec_title).find(title);
				cout << data << endl;
			}

			cout << "Input: ";
			cin >> choice;

		}

		if(choice == 4) {
			string newtitle;
			cout << "Enter a title for the item: " << endl;
			cin>> newtitle;

			if(bstnotebook.find(sec_title).isThere(newtitle)) {
				cout << "Item " << newtitle << " already exists in the " << sec_title << "." << endl;
			}
			else {
				string description;
				cout << "Enter a description for the item: " << endl;
				cin >> description;
				bstnotebook.find(sec_title).insert(description,newtitle);
				avlnotebook.find(sec_title).insert(description,newtitle);
				cout << "The new item " << newtitle <<	" has been inserted" << endl;

			}

			cout << "Input: ";
			cin >> choice;

		}
	}

}


void useMainMenu(BinarySearchTree<BinarySearchTree<string>> & bstNotebook, AvlTree<AvlTree<string>> & avlNotebook) {
	int choice = 0;
	choice = displayMainMenu();
	while(choice != 6) {
		if(choice == 1) {
			cout << "******" << endl;
			avlNotebook.printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		else if(choice == 2) {
			cout << "******" << endl;
			bstNotebook.printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}

		else if (choice == 3) {
			string sec_title;
			cout << "Enter the title of the section: " << endl;
			cin >> sec_title;

			if(!bstNotebook.isThere(sec_title)) {
				cout << "Invaild title!" << endl;
				cout << "Input: ";
				cin >> choice;
			}

			else {
				cout << "Selected section -> " << sec_title << endl;
				BinarySearchTree<string> binarySecTree = bstNotebook.find(sec_title);
				AvlTree<string> avlSecTree = avlNotebook.find(sec_title);

				cout << avlNotebook.root->element.findMax() << endl;

				useSectionMenu(bstNotebook, avlNotebook, sec_title);
				
			}
			cout << "Input: ";
			cin >> choice;
		}
	}

}

int main(){


	
	AvlTree<AvlTree<string>> avlNotebook;
	BinarySearchTree<BinarySearchTree<string>> bstNotebook;
	BinarySearchTree<string> newsec;
	AvlTree<string>newAvlSec;

	string title, info;
	int counter = 0;
	string line, sec_name;
	int index;
	ifstream in;
	string fname = "data.txt";

	in.open(fname.c_str());


	while(getline(in,line)) {
		

		index = line.find("-");

		if(index != 0) {
			if(counter == 0) {
				sec_name = line;
				counter++;

			}
			else {
				if(counter > 1) {
					int asda= 0;
					asda ++;
					cout << "aaaaaaa" << endl;
				}
				bstNotebook.insert(newsec, sec_name);
				avlNotebook.insert(newAvlSec, sec_name);

				counter++;
				
				//newsec.makeEmpty(); // bu sefer de burada 
				//newAvlSec.makeEmpty();

				newsec.root = nullptr;
				newAvlSec.root = nullptr;

				cout << "aaaaaa" << endl;
				
				
				sec_name = line;
			}
		}

		else {
			
			line = line.substr(1);
			
			index = line.find("-");
			title = line.substr(0,index);

			info = line.substr(index+1);
			
			newsec.insert(info,title);
			newAvlSec.insert(info,title);


		}


	}

	in.close();



	bstNotebook.insert(newsec,sec_name);
	/*bstNotebook.printTree();*/

	/*bstNotebook.root->element.printTree();*/
	/*bstNotebook.root->right->left->element.printTree();*/


	/*cout << "-----------------------" << endl; */

	avlNotebook.insert(newAvlSec,sec_name);
	/*avlNotebook.printTree();*/

	cout << avlNotebook.root->right->title << endl;
	/*cout << avlNotebook.root->element.findMax();*/

	//cout << k << endl;
	int choice;

	cout << "Welcome to the Notes" << endl;
	cout << endl;
	useMainMenu(bstNotebook, avlNotebook);

	//bstNotebook.printTree();

	return 0;
}