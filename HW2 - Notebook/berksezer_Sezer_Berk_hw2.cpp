#include <iostream>
#include <string>
#include "bst.h"
#include <fstream>
#include "Avl.h"
#include <chrono>

using namespace std;
//Berk Sezer

int displayMainMenu(){ // displays the main menu and takes the choice

	int choice;
	cout << "MENU" << endl;
	cout <<	"Please enter an input between [1 - 6]:" << endl;
	cout << "1- Display the sections [AVL]" << endl;
	cout << "2- Display the sections [BST]" << endl;
	cout << "3- Select a section" << endl;
	cout << "4- Add new section" << endl;
	cout << "5- Delete a section" << endl;
	cout << "6- Exit" << endl;
	cout << "Input: ";
	cin >> choice;

	return choice;

}

int displaySectionMenu() { // displays the section menu and takes the choice
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
	

	return choice;
}

void useSectionMenu(string sec_title, BinarySearchTree<BinarySearchTree<string>> &bstnotebook, AvlTree<AvlTree<string>> &avlnotebook) { // operates the selections in the section menu
	int choice = 0;
	choice = displaySectionMenu();
	while(choice != 7) {

		if (choice > 7 || choice < 1) { // input check
			cout << "Please enter a valid number" << endl;
			cout << "Input: ";
			cin >> choice;
		}


		else if(choice == 1) { // avl print
			cout << endl;
			cout << "******" << endl;
			avlnotebook.find(sec_title).printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		if(choice == 2) { // bst print
			cout << endl;
			cout << "******" << endl;
			bstnotebook.find(sec_title).printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		if(choice == 3) { // shows the information 
			
			string title;
			long long timer1 = 0;
			long long timer2 = 0;
			bool flag1, flag2;
			cout << "Enter the title of the item: ";
			cin >> title;



			auto start = std::chrono::high_resolution_clock::now();
			flag1 = bstnotebook.find(sec_title).isThere(title);
			auto end = std::chrono::high_resolution_clock::now();
			timer1 = (end - start).count() / 1000.0;

			auto start2 = std::chrono::high_resolution_clock::now();
			flag2 = avlnotebook.find(sec_title).isThere(title);
			auto end2 = std::chrono::high_resolution_clock::now();
			timer2 = (end2 - start2).count() / 1000.0;

			cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;
			cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;

			if(!flag2) {

				cout << "Invalid title."<< endl;
			}

			else {
				string data;
				data = bstnotebook.find(sec_title).find(title); // first finds the right section than the right title
				data = avlnotebook.find(sec_title).find(title);
				cout << data << endl;
			}



			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}

		if(choice == 4) { // inserts new item
			string newtitle;
			long long timer1 = 0;
			long long timer2 = 0;

			cout << "Enter a title for the item: ";
			cin>> newtitle;




			if(bstnotebook.find(sec_title).isThere(newtitle)) {
				cout << "Item \"" << newtitle << "\" already exists in the \"" << sec_title << "\"." << endl;
			}
			else {
				string description;
				cout << "Enter a description for the item: ";
				
				cin.ignore();
				getline(cin,description); 


				auto start = std::chrono::high_resolution_clock::now();
				bstnotebook.find(sec_title).insert(description,newtitle);
				auto end = std::chrono::high_resolution_clock::now();
				timer1 = (end - start).count() / 1000.0;

				start = std::chrono::high_resolution_clock::now();
				avlnotebook.find(sec_title).insert(description,newtitle); //finds the section and inserts
				end = std::chrono::high_resolution_clock::now();
				timer2 = (end - start).count() / 1000.0;

				cout << "[AVL] Elapsed time: " << timer2 << " microseconds." << endl;
				cout << "[BST] Elapsed time: " << timer1 << " microseconds." << endl;


				cout << "The new item \"" << newtitle << "\" has been inserted." << endl;

			}
			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}

		if(choice == 5) { // updates the information
			string toDelete;
			long long timer1 = 0;
			long long timer2 = 0;
			bool flag1, flag2;
			cout << "Enter the title of the item: ";
			cin >> toDelete;

			auto start = std::chrono::high_resolution_clock::now();
			flag1 = bstnotebook.find(sec_title).isThere(toDelete);
			auto end = std::chrono::high_resolution_clock::now();
			timer1 = (end - start).count() / 1000.0;

			start = std::chrono::high_resolution_clock::now();
			flag2 = avlnotebook.find(sec_title).isThere(toDelete);
			end = std::chrono::high_resolution_clock::now();
			timer2 = (end - start).count() / 1000.0;

			cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;
			cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;


			if(!flag1) {
				cout << "Item \"" << toDelete << "\" does not exist in the \"" << sec_title << "\"." << endl;
			}

			else {
				string newData;
				cout << "Enter the new information: ";
				cin.ignore();
				getline(cin, newData);

				bstnotebook.find(sec_title).changedata(newData, toDelete); // finds the section and updates the information
				avlnotebook.find(sec_title).changeData(newData, toDelete);

				cout << "The content " << toDelete << " has updated." << endl;

			}
			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}

		if(choice == 6) { // deletes a item
			string title;
			long long timer1 = 0;
			long long timer2 = 0;
			cout << "Enter the title of the item: ";
			cin >> title;

			if(!bstnotebook.find(sec_title).isThere(title)) {
				cout << "Item \"" << title << "\" does not exist in the \"" << sec_title <<"\"." << endl; 		
			}

			else {
				
				auto start = std::chrono::high_resolution_clock::now();
				bstnotebook.find(sec_title).remove(title); // finds the section and deletes the item
				auto end = std::chrono::high_resolution_clock::now();
				timer1 = (end - start).count() / 1000.0;

				start = std::chrono::high_resolution_clock::now();
				avlnotebook.find(sec_title).remove(title);
				end = std::chrono::high_resolution_clock::now();
				timer2 = (end - start).count() / 1000.0;
				
				cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;
				cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;


				cout << "The item \"" << title << "\" has been deleted." << endl;

			}
			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}
	}


}


void useMainMenu(BinarySearchTree<BinarySearchTree<string>> & bstNotebook, AvlTree<AvlTree<string>> & avlNotebook) { // operates the selections in the main menu
	int choice = 0;
	choice = displayMainMenu();
	while(choice != 6) {
		if (choice > 6 || choice < 1) {
			cout << "Please enter a valid number" << endl;
			cout << "Input: ";
			cin >> choice;
		}

		else if(choice == 1) { // print avl
			cout << endl;
			cout << "******" << endl;
			avlNotebook.printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		}

		else if(choice == 2) { // print bst
			cout << endl;
			cout << "******" << endl;
			bstNotebook.printTree();
			cout << "******" << endl;
			cout << endl;
			cout << "Input: ";
			cin >> choice;

		}

		else if (choice == 3) { // wents into the section menu if there exists such section
			string sec_title;
			cout << "Enter the title of the section: ";
			cin >> sec_title;

			if(!bstNotebook.isThere(sec_title)) {
				cout << "Invaild title!" << endl;
				
			cout << endl;
			cout << "Input: ";
			cin >> choice;
			

			}
			
			else {
				string a = "";
				cout << endl;
				cout << "Selected section -> " << sec_title << endl;
			

				useSectionMenu(sec_title, bstNotebook, avlNotebook);

				cout << endl;
				choice = displayMainMenu();
			}

			
		}

		else if (choice == 4) { //inserts new section
			string newsec;
			cout << "Enter a title for the section: ";
			cin >> newsec;

			if(bstNotebook.isThere(newsec)) {
				cout << "Section \"" << newsec << "\" already exists." << endl;
			}

			else {
				BinarySearchTree<string> newbst;
				AvlTree<string> newavl;

				bstNotebook.insert(newbst, newsec);
				avlNotebook.insert(newavl, newsec);
				
				cout << "The new section \"" << newsec << "\" has been inserted." << endl;

			}
			cout << endl;
			cout << "Input: ";
			cin >> choice;
		
		}

		else if (choice == 5) { // deletes a section
			string toDelete;
			cout << "Enter the title of the section: ";
			cin >> toDelete;

			if(!bstNotebook.isThere(toDelete)) {
				cout << "Section \""  <<  toDelete << "\" does not exists." << endl;
			}
			else {
				bstNotebook.remove(toDelete);
				avlNotebook.remove(toDelete);

				cout << "The section has been deleted." << endl;

			}
			cout << endl;
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

	long long timer1 = 0;
	long long timer2 = 0;

	string title, info;
	int counter = 0;
	string line, sec_name;
	int index;
	ifstream in;
	string fname = "data.txt";

	cout << "Welcome to the Notes" << endl;
	cout << endl;

	in.open(fname.c_str());


	while(getline(in,line)) {
		

		index = line.find("-");

		if(index != 0) {
			if(counter == 0) { // takes the first section name
				sec_name = line;
				counter++;

			}
			else { // if the section is finished inserts the tree inside the tree


				auto start = std::chrono::high_resolution_clock::now();
				bstNotebook.insert(newsec, sec_name);
				auto end = std::chrono::high_resolution_clock::now();
				timer1 = timer1 + (end-start).count()/1000.0;

				start = std::chrono::high_resolution_clock::now();
				avlNotebook.insert(newAvlSec, sec_name);
				end = std::chrono::high_resolution_clock::now();
				timer2 = timer2 + (end - start).count() / 1000.0;

				counter++;

				cout << "Section \"" << sec_name << "\" has been inserted to AVL notebook." << endl;
				cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;
			
				cout << "Section \"" << sec_name << "\" has been inserted to BST notebook." << endl;
				cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;
				cout << endl;

				newsec.rootNull();
				newAvlSec.rootNull();

				timer1 = 0;
				timer2 = 0;

				
				
				sec_name = line;
			}
		}

		else {
			
			line = line.substr(1);
			
			index = line.find("-");
			title = line.substr(0,index); // finds the title

			info = line.substr(index+1); // finds the info
			

			auto start = std::chrono::high_resolution_clock::now();
			newsec.insert(info,title); // performs insertion on the little tree
			auto end = std::chrono::high_resolution_clock::now();
			timer1 = timer1 + (end - start).count() / 1000.0;


			start = std::chrono::high_resolution_clock::now();
			newAvlSec.insert(info,title);
			end =  std::chrono::high_resolution_clock::now();
			timer2 = timer2 + (end - start).count() / 1000.0;


		}


	}

	in.close();


	auto start = std::chrono::high_resolution_clock::now(); // the last tree is inserted outside since the while loop is terminated
	bstNotebook.insert(newsec,sec_name);
	auto end = std::chrono::high_resolution_clock::now();
	timer1 = timer1 + (end - start).count() / 1000.0;

	start = std::chrono::high_resolution_clock::now();
	avlNotebook.insert(newAvlSec,sec_name);
	end = std::chrono::high_resolution_clock::now();
	timer2 = timer2 + (end - start).count() / 1000.0;
	
	cout << "Section \"" << sec_name << "\" has been inserted to AVL notebook." << endl;
	cout << "[AVL] Elapsed time: " << timer2 << " microseconds" << endl;


	cout << "Section \"" << sec_name << "\" has been inserted to BST notebook." << endl;
	cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;
	cout << endl;


	int choice;
	string s;
	
	

	useMainMenu(bstNotebook, avlNotebook);


	cout << endl;
	cout << "Terminating..." << endl;
	cout << "Program ended with exit code: 0" << endl;
	

	return 0;
}