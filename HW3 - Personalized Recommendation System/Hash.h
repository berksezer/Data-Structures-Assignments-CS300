#ifndef _HASH_H
#define _HASH_H

#include<iostream>
#include <string>
#include <vector>
#include "List.h"
#include "Hash.h"

using namespace std;

//Berk Sezer

struct series { // series struct is used for storing the names and support values inside hash

	vector<string> names;
	double support;
	double confidence;

	bool operator!=(series rhs) {
		if (names == rhs.names ) {
			return false;
		}

		return true;
	}

};



struct seriesConf { // seriesConf struct is used for storing the names, names in left and names in right of the arrow and the confidence values inside the hash
	vector<string> names;
	vector<string> namesLeft;
	vector<string> namesRight;
	
	double confidence;

	bool operator!=(seriesConf rhs) {
		if (namesLeft == rhs.namesLeft && namesRight == rhs.namesRight ) {
			return false;
		}


		return true;
	}

};


int hasher (const string & key, int tableSize);
int hasher (const series & key, int tableSize);

template <class HashedObj>
class HashTable{
public:
	HashTable(int size=101);
	HashTable (const HashTable & rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), theLists (rhs.theLists) {}

	const HashedObj & find (const HashedObj & x) const; //

	bool isThere(const HashedObj & x);

	void makeEmpty(); //
	void insert(const HashedObj & x); //
	void remove(const HashedObj & x); //

	const HashTable & operator= (const HashTable & rhs);

	vector<HashedObj> allElements();

private:

	
	vector<List<HashedObj>> theLists;
	
	int ITEM_NOT_FOUND;
	
	
};






int hasher(const string & key, int tableSize) {
	int hashVal = 0;

	for (int i = 0; i < key.length(); i++) {
		hashVal = 37 * hashVal + key[i];
	}

	hashVal = hashVal % tableSize;

	if(hashVal < 0) {
		hashVal = hashVal + tableSize;
	}

	return (hashVal);
}


int hasher(const series & key, int tableSize) { // hasher for series struct
	int hashVal = 0;
	string newkey = "";

	for (int i = 0; i < key.names.size(); i++) {
		newkey = newkey + key.names[i];
	}

	for (int i = 0; i < newkey.length(); i++) {
		hashVal = 37 * hashVal + newkey[i];
	}

	hashVal = hashVal % tableSize;

	if(hashVal < 0) {
		hashVal = hashVal + tableSize;
	}

	return (hashVal);
}

int hasher(const seriesConf & key, int tableSize) { // hasher for seriesConf struct
	int hashVal = 0;
	string newkey = "";

	for (int i = 0; i < key.names.size(); i++) {
		newkey = newkey + key.names[i];
	}

	for (int i = 0; i < newkey.length(); i++) {
		hashVal = 37 * hashVal + newkey[i];
	}

	hashVal = hashVal % tableSize;

	if(hashVal < 0) {
		hashVal = hashVal + tableSize;
	}

	return (hashVal);
}



template<class HashedObj>
bool HashTable<HashedObj>::isThere (const HashedObj & x) {
	
	ListItr<HashedObj> itr;

	itr = theLists[hasher(x, theLists.size())].find(x);
	
	if(itr.isPastEnd()) {
		return false;
	}

	return true;
}

template<class HashedObj>
HashTable<HashedObj>::HashTable (int size) :theLists(nextPrime(size)) {
	ITEM_NOT_FOUND = 99999;
	
}


bool isPrime(int n) {
	if(n == 2 || n == 3) {
		return true;
	}

	if(n == 1 || n % 2 == 0) {
		return false;
	}

	for (int i = 3; i * i <= n; i += 2) {
		if(n % i == 0) {
			return false;
		}
	}

	return true;

}

int nextPrime(int n) {

	if(n % 2 == 0) {
		n++;
	}

	for(; !isPrime(n); n+=2) {
		;
	}

	return n;
}

template<class HashedObj>
void HashTable<HashedObj>::makeEmpty() {
	for (int i = 0; i < theLists.size(); i++) {
		theLists[i].makeEmpty();
		
	}

}

template <class HashedObj>
vector<HashedObj> HashTable<HashedObj>::allElements() {
	vector<HashedObj> all;

	for(int i = 0; i < theLists.size(); i++) {
		List<HashedObj> currList = theLists[i];
		ListItr<HashedObj> itr = currList.first();

		while(!itr.isPastEnd()) {
			all.push_back(itr.retrieve());
			itr.advance();
		}
	}

	return all;

}

template<class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x) {
	
	List<HashedObj> & whichList = theLists[ hasher(x, theLists.size() )];

	ListItr<HashedObj> itr = whichList.find(x);

	if(itr.isPastEnd()) {
		whichList.insert(x, whichList.zeroth());
	}

}

template<class HashedObj>
void HashTable<HashedObj>::remove (const HashedObj & x) {

	theLists[hasher (x, theLists.size())].remove(x);
}

template<class HashedObj>
const HashedObj & HashTable<HashedObj>::find (const HashedObj & x) const {

	ListItr<HashedObj> itr;

	itr = theLists[hasher(x, theLists.size())].find(x);
	
	if(itr.isPastEnd()) {
		return ITEM_NOT_FOUND;
	}

	return itr.retrieve();
}
#endif