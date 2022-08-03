#include<iostream>
#include<string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "Hash.h"
#include <iomanip>

using namespace std;


//Berk Sezer

bool isThere(vector<string> curr, string name1) { // checks if the vector contains the given string name
	for(int i = 0; i < curr.size(); i++) {
		if(curr[i] == name1) {
			return true;
		}
	}
	return false;

}



int main(){

	string fName, s;
	double support, confidence;
	int lineCounter = 0;
	
	

	cout << "Please enter the transaction file name: ";
	cin >> fName;

	cout << "Please enter support and confidence values between 0 and 1: ";
	cin >> support >> confidence;
	
	ifstream in;
	in.open(fName.c_str());
	map<string, double> members;

	while(getline(in,s)) { // for single element constructed a map to store the number of occurences
		lineCounter++;
		string word;
		istringstream istr(s);

		while(istr >> word) {
		
			members[word]++;
		}

	}
	int distinctSeries = members.size();
	int hashSize = ((distinctSeries * (distinctSeries - 1)) / 2) + distinctSeries; // playing safe to get the size of the hash table to not exceed the load factor 1
	HashTable<series> lookupTable(hashSize);										// taking all the 2 combinations of the distinct elements and adding the number of distinct elements

	map<string, double>::iterator i;
	for(i = members.begin(); i != members.end(); i++) { // iterating through the map and inserting the signle elements with their support values to the hash table

		series tmpserie;
		tmpserie.names.push_back(i->first);
		tmpserie.support = i->second / lineCounter;

		if (tmpserie.support >= support) {
			lookupTable.insert(tmpserie);
		}

	}

	in.close();



	in.open(fName.c_str());
	vector<vector<string>> memberVec;

	while(getline(in,s)) { // having another input file read to read the txt file to a vector for future use
		vector<string> singleMember; 
		string word;
		istringstream istr(s);

		while(istr >> word) {
			singleMember.push_back(word);
		}

		memberVec.push_back(singleMember);

	}

	for (int i = 0; i < memberVec.size(); i++) { // looking for all possible pairs in the txt file
		vector<string> curr;
		curr = memberVec[i];

		for (int k = 0; k < curr.size()-1; k++) {
			string name1 = curr[k];
			

			for (int j = k + 1; j < curr.size(); j++) {
				
				string name2;
				name2 = curr[j]; 
				double lines = 0;
				series tmp;
				series n1, n2;
				n1.names.push_back(name1);
				n2.names.push_back(name2);

				if(lookupTable.isThere(n1) && lookupTable.isThere(n2)) { // if one of these names doesn't exist in the hash table
																		//that means none of the combinations also cannot pass the threshold
																		//So we can pass them
					if(name1 > name2){
						tmp.names.push_back(name1);
						tmp.names.push_back(name2);
					}

					else {
						tmp.names.push_back(name2);
						tmp.names.push_back(name1);					
					}


					if(!lookupTable.isThere(tmp)){ // checks if the hashtable already has the elements in it. If has not continues

						for (int q = i; q < memberVec.size(); q++) { // finding total lines which include the pair
							if(isThere(memberVec[q],name1) && isThere(memberVec[q], name2)) {
								lines++;
							}
						}

						double doubleSupport = lines / lineCounter;

						if (doubleSupport >= support) {
							tmp.support = doubleSupport;
																	
							lookupTable.insert(tmp); // insert into the hash table
						
						}
					}
				}
			}
		}

	}

	in.close();

	vector<series> everySupport;
	everySupport = lookupTable.allElements(); // getting every element of the hash table to look for possible pairs of these elements to calculate confidence values
	int maxPer = everySupport.size() * (everySupport.size() - 1); // stores the max number of permutations possible

	HashTable<seriesConf> confidenceTable(maxPer); // new Hashtable which will store the confidence values 

	for (int i = 0; i < everySupport.size(); i++) { //looking at the vector for pairs 
		series left = everySupport[i];
		for (int j = 0; j < everySupport.size(); j++) {
			bool flag = true;
			
			for(int k = 0; k < left.names.size(); k++) { // if the second element has any element of the left set the falg false to prevent the calculations
				if(isThere(everySupport[j].names, left.names[k])) {
					flag = false;
				}
			}

			if(flag == true) {
				double lines = 0;
				int elementNum = left.names.size() + everySupport[j].names.size();
				vector<string> currentElements;

				for(int p = 0; p < left.names.size(); p++) {
					currentElements.push_back(left.names[p]);
				}

				for(int p = 0; p < everySupport[j].names.size(); p++) {
					currentElements.push_back(everySupport[j].names[p]);
				}

				if (elementNum == 2) {
					string name1 = currentElements[0];
					string name2 = currentElements[1];

					seriesConf tmp;
					tmp.names = currentElements;
					tmp.namesLeft = left.names;
					tmp.namesRight = everySupport[j].names;

					if(!confidenceTable.isThere(tmp)) { // check if already this element exists in the hashtable

						for (int q = 0; q < memberVec.size(); q++) {
							if(isThere(memberVec[q], name1) && isThere(memberVec[q], name2)) {
								lines++;
							}
						}
						double bigSupport = lines / lineCounter;
						double currConfidence = bigSupport / left.support;

						if(currConfidence >= confidence) {
							tmp.confidence = currConfidence;
							confidenceTable.insert(tmp); // insert it into the hash table

						}
					}
				}

				else if (elementNum == 3) {
					string name1 = currentElements[0];
					string name2 = currentElements[1];
					string name3 = currentElements[2];

					seriesConf tmp;
					tmp.names = currentElements;
					tmp.namesLeft = left.names;
					tmp.namesRight = everySupport[j].names;
					

					if(!confidenceTable.isThere(tmp)) { // check if already this element exists in the hashtable
						for (int q = 0; q < memberVec.size(); q++) {
							if(isThere(memberVec[q], name1) && isThere(memberVec[q], name2) && isThere(memberVec[q], name3)) {
								lines++;
							}
						}

						double bigSupport = lines / lineCounter;
						double currConfidence = bigSupport / left.support;

						if(currConfidence >= confidence) {
							tmp.confidence = currConfidence;
							confidenceTable.insert(tmp); // insert it into the hash table
							
						}
					}
				}

				else if (elementNum == 4) {
					string name1 = currentElements[0];
					string name2 = currentElements[1];
					string name3 = currentElements[2];
					string name4 = currentElements[3];

					seriesConf tmp;
					tmp.names = currentElements;
					tmp.namesLeft = left.names;
					tmp.namesRight = everySupport[j].names;

					if(!confidenceTable.isThere(tmp)) { // check if already this element exists in the hashtable

						for (int q = 0; q < memberVec.size(); q++) {
							if(isThere(memberVec[q], name1) && isThere(memberVec[q], name2) && isThere(memberVec[q], name3) && isThere(memberVec[q], name4)) {
								lines++;
							}
						}

						double bigSupport = lines / lineCounter;
						double currConfidence = bigSupport / left.support;

						if(currConfidence >= confidence) {

							tmp.confidence = currConfidence;
							confidenceTable.insert(tmp); // insert it into the hash table
						
						}
					}
				}
				

			}
			
		}
	
	}

	vector<seriesConf> allConfidence = confidenceTable.allElements(); // get all the elements of the confidence hash table to write them into a output txt file



	if(allConfidence.size() == 0) { // there are no elements
		cout << "There is no rule for the given support and confidence values." << endl;
	
	}
	else { // write all the above treshold confidence valued pairs to results.txt
		cout << allConfidence.size() << " rules are written to results.txt" << endl;
		ofstream output;
		output << fixed << setprecision(2); 
		string fname = "results.txt";

		output.open(fname.c_str());

		for (int k = 0; k < allConfidence.size(); k++) {
			string ofLine;
			int counter = 0;
			for (int j = 0; j < allConfidence[k].namesLeft.size(); j++) {
				if (counter == 0) {
					ofLine = ofLine + allConfidence[k].namesLeft[j];
					counter++;
				}
				else {
					ofLine = ofLine + "," + allConfidence[k].namesLeft[j];
				}
			}
			ofLine = ofLine + ";";
			counter = 0;
			for (int j = 0; j < allConfidence[k].namesRight.size(); j++) {
				if (counter == 0) {
					ofLine = ofLine + allConfidence[k].namesRight[j];
					counter++;
				}

				else {
					ofLine = ofLine + "," + allConfidence[k].namesRight[j];
				}
			}
			
			ofLine = ofLine + ";";

			output << ofLine;
			output << allConfidence[k].confidence;
			output << endl;
		}

		output.close();
	}

	
	return 0;
}