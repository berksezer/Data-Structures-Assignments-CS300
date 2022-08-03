//#ifndef _BST_H
//#define _BST_H
//
//#include <iostream>
//#include <string>
//#include "bst2.h"
//#include "Stack.h"
//
//
//using namespace std;
//
//
//
//
//
////template <class Comparable>
////struct BinaryNode {
////	Comparable element;
////	BinaryNode *left;
////	BinaryNode *right;
////	string title;
////
////	BinaryNode(const Comparable & theElement, BinaryNode* lt, BinaryNode *rt, string t){
////		element = theElement;
////		left = lt;
////		right = rt;
////		title = t;
////	
////	}
////
////};
//
//template<class Comparable>
//class BinarySearchTree {
//public:
//	explicit BinarySearchTree(); // 
//	BinarySearchTree(const BinarySearchTree & rhs);//
//	~BinarySearchTree(); //
//
//	const Comparable & findMin() const; //
//	const Comparable & findMax() const; //
//	Comparable & find(string name) const; //
//	bool isEmpty() const; //
//	void printTree() const; //
//	void makeEmpty(); //
//	void insert(const Comparable & x, string name); // 
//	void remove(string name); //
//	const BinarySearchTree & operator=(const BinarySearchTree & rhs); //
//	bool operator< (const BinarySearchTree& rhs); 
//	bool operator> (const BinarySearchTree& rhs); 
//	bool isThere(string name);
//
//	void changedata(const Comparable &, string name);
//
//	template<class Comparabale>
//	friend ostream& operator<<(ostream &, const BinarySearchTree<Comparable> &);
//	BinaryNode<Comparable>* root;
//	
//private:
//
//
//
//	
//	Comparable ITEM_NOT_FOUND;
//	
//
//	Comparable & elementAt(BinaryNode<Comparable> *t)  const; //
//	//void insert(const Comparable & x, BinaryNode<Comparable> * & t, string name) const; // 
//	void remove(string name, BinaryNode<Comparable> * & t) const; //
//	BinaryNode<Comparable> * findMin(BinaryNode<Comparable> *t) const; //
//	BinaryNode<Comparable> * findMax(BinaryNode<Comparable> *t) const; //
//	BinaryNode<Comparable> * find(string name, BinaryNode<Comparable>* t ) const; //
//	void makeEmpty(BinaryNode<Comparable> * & t) const; //
//	void printTree(BinaryNode<Comparable> *t) const; //
//	BinaryNode<Comparable> * clone(BinaryNode<Comparable> *t) const; //
//
//	bool isThere(string name, BinaryNode<Comparable> * t);
//
//};
//
//
//template <class itemType>
//class Iterator{
// public:
//  //Constructor
//  Iterator();
//
//  void Init(const BinarySearchTree<itemType>& );
//  bool hasNext();
//  BinaryNode<itemType>* Next(); //Actually the same with InOrderNext()
//  BinaryNode<itemType>* InOrderNext(); 
//  BinaryNode<itemType>* PreOrderNext(); 
//  
// private:
//  BinaryNode<itemType>* myCurrent;
//  Stack<itemType>* stack;
//  Stack<itemType>* stack2;
//};
//
//template<class Comparable>
//BinarySearchTree<Comparable>::BinarySearchTree(): ITEM_NOT_FOUND(), root(NULL){
//	
//}
//
//template<class Comparable>
//Comparable & BinarySearchTree<Comparable>:: elementAt(BinaryNode<Comparable> *t) const {
//	/*return t == NULL ? ITEM_NOT_FOUND : t->element;*/
//
//	return t->element;
//}
//
//template<class Comparable>
//bool BinarySearchTree<Comparable>::isThere(string name) {
//	BinaryNode<Comparable>* ptr = root;
//
//	while(ptr != NULL) {
//		if(name < ptr->title) {
//			ptr = ptr->left;
//		}
//
//		else if (name > ptr ->title) {
//			ptr = ptr->right;
//		}
//
//		else {
//			return true;
//		}
//
//	}
//
//	return false;
//
//}
//
//template <class Comparable>
//bool BinarySearchTree<Comparable>::isThere(string name, BinaryNode<Comparable> * t) {
//	if(t == NULL) {
//		return false;
//	}
//
//	else if(name < t->title) {
//		return isThere(name, t->left);
//	}
//
//	else if (name > t->title) {
//		return isThere(name, t->right);
//	}
//
//	else {
//		return true;
//	}
//}
//
//
//template<class Comparable>
//Comparable & BinarySearchTree<Comparable>::find(string name) const {
//	return elementAt(find(name,root));
//} 
//
//template<class Comparable> 
//void BinarySearchTree<Comparable>::changedata(const Comparable & x, string name) {
//	BinaryNode<Comparable> * ptr = find(name, root);
//
//	ptr->element = x;
//}
//
//template<class Comparable>
//BinaryNode<Comparable> * BinarySearchTree<Comparable>::find(string name, BinaryNode<Comparable> * t) const {
//	//if(t == NULL) {
//	//	return NULL;
//	//}
//
//	//else if (name < t->title){
//	//	return find(name,t->left);
//	//}
//
//	//else if(t->title < name) {
//	//	return find(name, t->right);
//	//}
//	//else {
//	//	return t;
//	//}
//
//	while(t != NULL) {
//		if(name < t->title) {
//			t = t ->left;
//		}
//
//		else if (name > t->title) {
//			t = t ->right;
//		}
//
//		else {
//			return t;
//		}
//
//	}
//	return NULL;
//	
//} 
//
//template<class Comparable>
//const Comparable & BinarySearchTree<Comparable>::findMin() const {
//	return elementAt(findMin(root));
//}
//
//template<class Comparable>
//BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> *t) const {
//	if(t == NULL) {
//		return NULL;
//	}
//
//	if(t->left == NULL) {
//		return t;
//	}
//	return findMin(t->left);
//} 
//
//template<class Comparable>
//const Comparable & BinarySearchTree<Comparable>::findMax() const {
//	return elementAt(findMax(root));
//}
//
//template<class Comparable>
//BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t) const {
//	if(t != NULL) {
//		while(t->right != NULL) {
//			t = t->right;
//		}
//	return t; 
//	} 
//}
//
////template<class Comparable>
////void BinarySearchTree<Comparable>::insert(const Comparable & x, string name) {
////	insert(x,root, name);
////}
////
////template<class Comparable>
////void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode<Comparable>* & t, string name) const {
////	if(	t==NULL) {
////		t = new BinaryNode<Comparable> (x, NULL, NULL, name);
////	}
////
////	else if (t->element > x) {
////		insert(x, t->left, name);
////	}
////
////	else if (t->element < x) {
////		insert(x, t->right, name);
////	}
////
////	else
////		;
////}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::insert(const Comparable & x, string name) {
//	BinaryNode<Comparable>* newnode = new BinaryNode<Comparable> (x, NULL, NULL, name);
//
//	BinaryNode<Comparable>* ptr = root;
//	BinaryNode<Comparable>* temp = nullptr;
//
//	while(ptr != NULL) {
//		temp = ptr;
//
//		if(ptr->title > name) {
//			ptr = ptr->left;
//		}
//		else {
//			ptr = ptr->right;
//		}
//	}
//
//	if(temp == NULL) {
//		temp = newnode;
//		root = temp;
//	}
//
//	else if (temp->title > name) {
//		temp->left = newnode;
//	}
//
//	else {
//		temp->right = newnode;
//	}
//
//
//
//}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::remove (string name) {
//	remove(name,root);
//}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::remove(string name, BinaryNode<Comparable> *& t) const {
//	if(t == NULL) {
//		return;
//	}
//	if(name < t->title) {
//		remove(name , t->left);
//	}
//
//	else if (t->title < name){
//		remove(name, t->right);
//	}
//
//	
//
//	else if (t->left != NULL && t->right !=NULL) {
//		t->title = findMin(t->right)->title;
//		remove(t->title, t->right);
//	}
//
//	else {
//		BinaryNode<Comparable> *oldnode = t;
//		t = (t->left != NULL) ? t->left : t->right;
//		delete oldnode;
//
//	}
//}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::makeEmpty() {
//
//	makeEmpty(root);
//
//}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable> *& t) const {
//	
//	Stack<BinaryNode<Comparable>* > s;
//
///*	if(t != NULL) {
//		makeEmpty(t->left);
//		makeEmpty(t->right);
//		delete t;
//	}
//	t = *//*NULL;*/
//
//	Iterator<Comparable> iter;
//	iter.Init(*this);
//    
//	while(iter.hasNext()){
//		delete iter.InOrderNext();
//	}
//
//}
//
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable> *t) const {
//	if(t != NULL) {
//		printTree(t->left);
//		cout << t->title << endl;
//		printTree(t->right);
//	}
//}
//
//template<class Comparable>
//void BinarySearchTree<Comparable>::printTree() const {
//	if(isEmpty()) {
//		cout << "Empty Tree" << endl;
//	}
//	else {
//		printTree(root);
//	}
//}
//
//template<class Comparable>
//BinarySearchTree<Comparable>::~BinarySearchTree() {
//
//	makeEmpty();
//
//}
//
//template<class Comparable>
//BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable> & rhs) {
//	*this = rhs;
//}
//
//
//template<class Comparable>
//bool BinarySearchTree<Comparable>::isEmpty() const {
//	if(root == NULL) {
//		return true;
//	}
//
//	return false;
//}
//
//
//template<class Comparable>
//BinaryNode<Comparable>* BinarySearchTree<Comparable>::clone(BinaryNode<Comparable> *t) const {
//	if(t == NULL) {
//		return NULL;
//	}
//
//	else {
//		/*return new BinaryNode<Comparable>(t->element,clone(t->left),clone(t->right), t->title);*/
//		BinaryNode<Comparable> * root = new BinaryNode<Comparable>(t->element, nullptr, nullptr, t->title);
//		BinaryNode<Comparable> * clone = root;
//
//		while(t != NULL) {
//			if(t->left != NULL && clone->left == NULL) {
//				clone->left = new BinaryNode<Comparable>(t->left->element, nullptr, nullptr, t->left->title);
//			} 
//		}
//	}
//}
//
//
//template<class Comparable>
//const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable> &rhs) {
//	//if(this != &rhs) {
//	//	this->~BinarySearchTree();
//	//	this->root = nullptr;
//
//	//	root = clone(rhs.root);
//
//	//	return *this;
//
//	/*}*/
//
//	if(this!=&rhs)
//    {
//		
//		/*this->~BinarySearchTree();*/
//	
//		BinaryNode<Comparable>* ptr= rhs.root;
//		this->root = ptr;
//      
//		//Iterator<Comparable> iter;
//		//iter.Init(rhs);
//		//while (iter.hasNext()) {
//		//	BinaryNode<Comparable>* tmp = iter.Next();
//		//	this->insert(tmp->element, tmp->title);
//		//}
//    }
//	return *this;
//}
//
//template<class Comparable>
//bool BinarySearchTree<Comparable>::operator<(const BinarySearchTree<Comparable> &rhs) {
//	if(root->element < rhs.root->element) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//
//template<class Comparable>
//bool BinarySearchTree<Comparable>::operator>(const BinarySearchTree<Comparable> &rhs) {
//	if(root->element > rhs.root->element) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//
//template <class Comparable>
//void writeOS(ostream & os, BinaryNode<Comparable> * t) {
//	if(t != NULL) {
//		writeOS(os, t->left);
//		os << t->element << " ";
//		writeOS(os, t->right);
//	}
//
//}
//
//
//template <class Comparable>
//ostream & operator << (ostream& os, const BinarySearchTree<Comparable> & rhs) {
//	
//	writeOS(os , rhs.root);
//
//	return os;
//
//}
//
//
//template <class itemType>
//Iterator<itemType>::Iterator()
//  :myCurrent(nullptr), stack(nullptr), stack2(nullptr)
//{}
//template <class itemType>
//void Iterator<itemType>::Init(const BinarySearchTree<itemType> &tree)
//{
//  myCurrent = tree.root;
//  stack = new Stack<itemType>();
//}
//template <class itemType>
//bool Iterator<itemType>::hasNext()
//{
//  return (!stack->isEmpty() || myCurrent != nullptr);
//}
//
//template <class itemType>
//BinaryNode<itemType>* Iterator<itemType>::Next()
//{
//  while (myCurrent != nullptr) {
//    stack->push(myCurrent);
//    myCurrent = myCurrent->left;
//  }
//  
//  myCurrent = stack->pop();
//  BinaryNode<itemType>* node = myCurrent;
//  myCurrent = myCurrent->right;
//  
//  return node;
//}
//
//
//template <class itemType>
//BinaryNode<itemType>* Iterator<itemType>::InOrderNext()
//{
//  while (myCurrent != nullptr) {
//    stack->push(myCurrent);
//    myCurrent = myCurrent->left;
//  }
//  
//  myCurrent = stack->pop();
//  BinaryNode<itemType>* node = myCurrent;
//  myCurrent = myCurrent->right;
//  
//  return node;
//}
//
//
////This is just to show. Iterative post-order is much more complex.
//template <class itemType>
//BinaryNode<itemType>* Iterator<itemType>::PreOrderNext()
//{
//  if(myCurrent->left != nullptr || myCurrent->right != nullptr){
//    stack->push(myCurrent);
//  }
//  
//  BinaryNode<itemType>* node = myCurrent;
//
//  if(myCurrent->left == nullptr && myCurrent->right == nullptr){
//    if(!stack->isEmpty()){
//      myCurrent = stack->pop();
//    }
//    else{
//      myCurrent = nullptr;
//      return node;
//    }
//    if(myCurrent->right){
//      myCurrent = myCurrent->right;
//    }
//    else{
//      while(!myCurrent->right){
//	myCurrent = stack->pop();
//	myCurrent = myCurrent->right;
//      }
//    }   
//  }
//  else if(myCurrent->left){
//    myCurrent = myCurrent -> left;
//  }
//  else if(myCurrent->right){
//    myCurrent = stack->pop();
//    myCurrent = myCurrent -> right;
//  }
//
//  return node;
//}
//
//
//
//#endif