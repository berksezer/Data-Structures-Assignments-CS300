#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cctype>

using namespace std;

//Berk Sezer

struct contact { // the struct which contains all the info about the persons
	string name;
	string surname;
	string number;
	string city;
	string fullName;

	contact() {
		name ="";
		surname = "";
		number = "";
		city = "";
		fullName = "";
	}

	contact(string n, string s, string nmbr, string c, string f) {
		name = n;
		surname = s;
		number = nmbr;
		city = c;
		fullName = f;
	}

	bool operator < (contact rhs) {
		string fullName = name + surname;
		string fullName2 = rhs.name + rhs.surname;

		if(fullName < fullName2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator > (contact rhs) {
		string fullName = name + surname;
		string fullName2 = rhs.name + rhs.surname;

		if(fullName > fullName2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator <= (contact rhs) {
		string fullName = name + surname;
		string fullName2 = rhs.name + rhs.surname;

		if(fullName <= fullName2) {
			return true;
		}
		else {
			return false;
		}
	}

};

template <class Comparable>
void insertionSort (vector <Comparable> & a) {
	int j;

	for (int p = 1; p < a.size(); p++) {
		Comparable tmp = a[p];

		for (j = p; j > 0 && tmp < a[j - 1]; j--) { // openning an empty place to store the tmp in the right place
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	
	}
}



inline int leftChild(int i) {
	return 2*i + 1;
}

template <class Comparable>
void percDown(vector<Comparable> & a, int i, int n) { // percolade down just like the heap case
	
	int child;
	Comparable tmp;

	for (tmp = a[i]; leftChild(i) < n; i = child) {
		child = leftChild(i);

		if(child != n-1 && a[child] < a[child + 1]) {
			child++;
		}

		if(a[child] > tmp) {
			a[i] = a[child];
		}

		else {
			break;
		}
	}

	a[i] = tmp;
}



template <class Comparable>
void heapsort(vector<Comparable> & a) {
	
	for(int i = a.size()/2; i >=0; i--) { // building the heap 
		percDown(a,i,a.size());
	}

	for(int j = a.size() - 1; j > 0; j--) { // swap operation
		swap(a[0], a[j]); // max is at the last
		percDown(a,0,j); // heap is arranged again by percolating down
	}
}


template <class Comparable>
void merge(vector<Comparable> & a, int start, int center, int end) {
	int start2 = center + 1;

	if(a[center] <= a[start2]) { // checks if it is sorted
		return;
	}

	while(start <= center && start2 <= end) { // merge starts by having two "pointers" in different halfs of the vector
		
		if(a[start] <= a[start2]) {
			start++;
		}

		else {
			Comparable value = a[start2]; // finding the right position to put the value
			int index = start2;

			while(index != start) {
				a[index] = a[index - 1];
				index--;
			}

			a[start] = value;

			start++;
			center++;
			start2++;
		}
	}
}


template <class Comparable>
void mergeSort(vector<Comparable> & a, int left, int right) {
	
	if(left < right) {
		int center = (left + right) / 2;

		mergeSort(a, left, center); // sorting two halves 
		mergeSort(a, center + 1, right);
		merge(a, left, center, right); // and merging them
	}
}


template <class Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right) { //returns the median which will be used as the pivot
	
	int center = (left + right) / 2;

	if(a[center] < a[left]) {
		swap(a[left], a[center]);
	}

	if(a[right] < a[left]) {
		swap(a[left], a[right]);
	}

	if(a[right] < a[center]) {
		swap(a[center], a[right]);
	}

	swap(a[center], a[right - 1]); // placing the pivot
	return a[right - 1];
}


template <class Comparable> // insertion sort function to be used by the quick sort
void insertionSort(vector<Comparable> & a, int left, int right) {
	
	for(int p = left + 1; p <= right; p++) {
		Comparable tmp = a[p];
		int j;

		for (j = p; j > left && tmp < a[j - 1]; j--) {
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}

template <class Comparable>
void quickSort(vector<Comparable> & a, int left, int right) { // quick sort by using the median as the pivot
	
	if(left + 10 <= right) {
		Comparable pivot = median3(a,left,right);

		int i = left, j = right - 1;
		for(;;) {
			while(a[++i] < pivot) {}

			while(pivot < a[--j]) {}

			if(i < j) {
				swap(a[i], a[j]);
			}

			else {
				break;
			}
		}

		swap (a[i], a[right - 1]); // pivot is being put back

		quickSort(a, left, i - 1); // sort left
		quickSort(a, i + 1, right); // sort right
	}

	else {
		insertionSort(a,left,right); // if the number of elements are below 10 we use insertion sort
	}
}

template <class Comparable>
void quickSort(vector<Comparable> & a) {
	quickSort(a, 0 ,a.size() -1);
}


int binarySearch(const vector<contact>& a, int left, int right, string x, bool isFullName) { 
	int center;
	if (isFullName == true) { // for the full name search

		while (left <= right) {
			center = left + (right - left) / 2;

			if(a[center].fullName == x ) {
				return center;
			}

			if(a[center].fullName < x) {
				left = center + 1;
			}

			else {
				right = center - 1;
			}
		}
	
		return -1;
	
	}

	else { // for the partial search
		int sizex = x.size();
		while (left <= right) {
			center = left + (right - left) / 2;

			
			if(a[center].name.substr(0,sizex) == x ) {
				return center;
			}

			if(a[center].name.substr(0,sizex) < x) {
				left = center + 1;
			}

			else {
				right = center - 1;
			}
		}
	
		return -1;
	
	
	}

}

int sequentialSearch(const vector<contact> &a, string x, bool isFullName) {
	
	if (isFullName == true) { // for full name search
		for(int i = 0; i < a.size(); i++) {
			if(a[i].fullName == x) {
				return i;
			}
		}
		return -1;
	}

	else {// for the partial search
		for(int i = 0; i < a.size(); i++) {
			if(a[i].name.substr(0, x.size()) == x) {
				return i;
			}
		}
		return -1;
	}
}

string makeUpper(string s) { // an fucntion to print out the word as full upper case letters
	for (int i = 0; i < s.size(); i++) {
		s[i] = toupper(s[i]);
	}
	return s;
}

void printContact (contact s) { //prinitng the contacts with all their informations
	cout << makeUpper(s.name) << " " << makeUpper (s.surname) << " " << s.number << " " << s.city << endl;
}

void findEndStart(vector<contact> a, string sWord, int index, int & start, int& end) { // for partial binary search
	bool endLoop = true;
	int wSize = sWord.size();

	for (int i = index; endLoop == true; i--) { //checks if there are any other words before the index that binary search has founded
		if(i < 0 || a[i].name.substr(0,wSize) != sWord) {
			endLoop = false;
			start = i;
		}
	}

	endLoop = true;

	for (int i = index; endLoop == true; i++) {//checks if there are any other words after the index that binary search has founded
		if(i >= a.size() || a[i].name.substr(0,wSize) != sWord) {
			endLoop = false;
			end = i;
		}
	}
}


int main() {
	string fname, sWord,s;
	bool isFullName = false;
	cout << "Please enter the contact file name:" << endl;
	cin >> fname; 
	cin.ignore();
	cout << "Please enter the word to be queried :" << endl;
	
	
	getline(cin, sWord);

	if(sWord.find(" ") != string::npos) { // checks the search type
		isFullName = true;
	}

	ifstream in;
	in.open(fname.c_str());
	vector<contact> iSortVec, qSortVec, mSortVec, hSortVec;

	while(getline(in,s)) { // partitioning the line
		string name, surname, phone, adress, fullName;

		int index = s.find(" ");
		name = s.substr(0,index);
		s = s.substr(index+1);
		
		index = s.find(" ");
		surname = s.substr(0,index);
		s = s.substr(index+1);
		
		index = s.find(" ");
		phone = s.substr(0,index);
		adress = s.substr(index+1);

		fullName = name + " " + surname;

		contact tmp(name, surname,phone,adress, fullName);
		iSortVec.push_back(tmp);
		qSortVec.push_back(tmp);
		mSortVec.push_back(tmp);
		hSortVec.push_back(tmp);
	
	}

	in.close();

	cout << endl;
	cout <<	"Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	
	auto start4 = std::chrono::high_resolution_clock::now();	
	quickSort(qSortVec);
	auto end4 = std::chrono::high_resolution_clock::now();

	auto qSortTime = chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count();
	cout << "Quick Sort Time: " << qSortTime << " Nanoseconds" << endl;

	auto start = std::chrono::high_resolution_clock::now();
	insertionSort(iSortVec);
	auto end = std::chrono::high_resolution_clock::now();
	auto iSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count() ;
	cout << "Insertion Sort Time: " << iSortTime << " Nanoseconds" << endl;
	
	auto start3 = std::chrono::high_resolution_clock::now();
	mergeSort(mSortVec, 0 , mSortVec.size() - 1);
	auto end3 = std::chrono::high_resolution_clock::now();
	auto mSortTime = chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count() ;
	cout << "Merge Sort Time: " << mSortTime << " Nanoseconds" << endl;

	auto start2 = std::chrono::high_resolution_clock::now();
	heapsort(hSortVec);
	auto end2 = std::chrono::high_resolution_clock::now();
	auto hSortTime = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() ;
	cout << "Heap Sort Time: " << hSortTime << " Nanoseconds" << endl;


	cout << endl;
	cout << "Searching for " << makeUpper(sWord) << endl;
	cout << "======================================" << endl;


	int isFoundB = 0;
	int isFoundS = 0;

	int N = 1000;
	auto starts = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N ; i++) {
		isFoundB = binarySearch(qSortVec, 0, iSortVec.size() - 1, sWord, isFullName);
	}
	
	
	auto ends = std::chrono::high_resolution_clock::now();

	auto bTime = chrono::duration_cast<chrono::nanoseconds>(ends - starts).count() /N;
	
	cout << "Search results for Binary Search:" << endl;

	if(isFoundB == -1) {
		cout << makeUpper(sWord) << " does NOT exist in the dataset" << endl;
	}

	else {
		if(isFullName == true) { // there is only one name
			printContact(qSortVec[isFoundB]);
		}

		else {// there can be more than one outcomes	
			int start, end;
			findEndStart(qSortVec, sWord, isFoundB, start, end); 		
			for (int k = start + 1; k < end; k++) {
				printContact(qSortVec[k]);
			}
		}
	}

	cout << endl;

	cout << "Binary Search Time: " << bTime << " Nanoseconds" << endl;
	cout << endl;

	N = 1000;
	auto starts2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		isFoundS = sequentialSearch(qSortVec, sWord, isFullName);
	}


	auto ends2 = std::chrono::high_resolution_clock::now();
	auto sTime = chrono::duration_cast<chrono::nanoseconds>(ends2 - starts2).count() / N;
	
	cout << "Search results for Sequential Search:" << endl;
	if(isFoundS == -1) {
		cout << makeUpper(sWord) << " does NOT exist in the dataset" << endl;
	}
	else {
		if(isFullName == true) {// there is only one name
			printContact(qSortVec[isFoundS]);
		}

		else {// there can be more than one outcomes		
			bool endLoop = true;
			
			for (int k = isFoundS; endLoop == true; k++) {
				if(k < qSortVec.size () && qSortVec[k].name.substr(0, sWord.size()) == sWord) {
					printContact(qSortVec[k]);
				}

				else {
					endLoop = false;
				}
			}
		}
	}

	cout << endl;
	cout << "Sequential Search Time: " << sTime << " Nanoseconds" << endl;
	cout << endl;

	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << float(sTime) / float (bTime) << endl;
	cout << endl;

	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << float(iSortTime) / float (qSortTime) << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << float (mSortTime) / float (qSortTime) << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << float (hSortTime) / float(qSortTime) << endl;

	in.close();

	return 0;
}