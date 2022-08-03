#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include <string>
#include "Avl.h"

using namespace std;


//Berk Sezer

template<class Comparable>
struct AvlNode {
	Comparable element;
	AvlNode *left;
	AvlNode *right;
	int height;
	string title;

	AvlNode(const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h , string t) {
		element = theElement;
		left = lt;
		right = rt;
		height = h;
		title = t;
	}


};


template <class Comparable>
class AvlTree {
public:
	explicit AvlTree(); 
	AvlTree(const AvlTree & rhs);
	~AvlTree(); 


	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const; 
	Comparable & find( string name ) const; 
	bool isEmpty( ) const; 
	void printTree( ) const; 
	void makeEmpty( ); 
	void insert( const Comparable & x, string name );  
	void remove( const string name );
	const AvlTree & operator=( const AvlTree & rhs ); 
	bool isThere(string name);
	void rootNull();
	void changeData(const Comparable &x, string name);

	
private:
	AvlNode<Comparable> *root;
	Comparable ITEM_NOT_FOUND;

	Comparable & elementAt( AvlNode<Comparable> *t ) const; 
	void insert( const Comparable & x, AvlNode<Comparable> * & t , string title) const; 
	void remove(const string name, AvlNode<Comparable> * & t ) const;
	AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const; 
	AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const; 
	AvlNode<Comparable> * find( string name, AvlNode<Comparable> *t) const; 

	void makeEmpty( AvlNode<Comparable> * & t ) const; 
	void printTree( AvlNode<Comparable> *t ) const; 
	AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const; 

	int height( AvlNode<Comparable> *t ) const; 
	int max( int lhs, int rhs ) const; 
	void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const; 
	void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const; 
	void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const; 
	void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const; 
};

template<class Comparable>
AvlTree<Comparable>::AvlTree() : ITEM_NOT_FOUND(), root(NULL) {}


template<class Comparable>
void AvlTree<Comparable>::rootNull() {
	root = nullptr;
}

template<class Comparable>
Comparable & AvlTree<Comparable>::elementAt(AvlNode<Comparable> *t) const {
	
	return t->element;

}

template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const {
	if(t == NULL) {
		return -1;
	}

	return t->height;
}

template<class Comparable>
void AvlTree<Comparable>::changeData(const Comparable & x, string name) {
	AvlNode<Comparable> * ptr = find(name, root);

	ptr->element = x;
}


template<class Comparable>
Comparable & AvlTree<Comparable>::find(string name) const {
	return elementAt(find(name,root));
}

template<class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::find(string name, AvlNode<Comparable> * t) const {
	if(t == NULL) {
		return NULL;
	}

	else if (name < t->title){
		return find(name,t->left);
	}

	else if(t->title < name) {
		return find(name, t->right);
	}
	else {
		return t;
	}
} 

template<class Comparable>
const Comparable & AvlTree<Comparable>::findMin() const {
	return elementAt(findMin(root));
}

template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const {
	if(lhs > rhs) {
		return lhs;
	}

	return rhs;

}

template<class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable> *t) const {
	if(t == NULL) {
		return NULL;
	}

	if(t->left == NULL) {
		return t;
	}
	return findMin(t->left);
} 

template<class Comparable>
const Comparable & AvlTree<Comparable>::findMax() const {
	return elementAt(findMax(root));
}

template<class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMax(AvlNode<Comparable>* t) const {
	if(t != NULL) {
		while(t->right != NULL) {
			t = t->right;
		}
	return t; 
	} 
}


template<class Comparable>
bool AvlTree<Comparable>::isThere(string name) {
	AvlNode<Comparable>* ptr = root;

	while(ptr != NULL) {
		if(name < ptr->title) {
			ptr = ptr->left;
		}

		else if (name > ptr ->title) {
			ptr = ptr->right;
		}

		else {
			return true;
		}

	}

	return false;

}




template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, string name) {
	insert(x,root,name);
}

template <class Comparable>
void AvlTree<Comparable>::insert (const Comparable & x, AvlNode<Comparable>* & t, string name) const {
	if(t == NULL) {
		t = new AvlNode<Comparable>(x, NULL, NULL,0, name);
	}

	else if (name < t->title) {
		insert(x, t->left, name); 

		if(height(t->left) - height(t->right) == 2) {
			if(name < t->left->title) {
				rotateWithLeftChild(t);
			}

			else {
				doubleWithLeftChild(t);
			}
		}

	}

	else if (t->title < name) {
		insert(x,t->right, name);
		if(height(t->right) - height(t->left) == 2) {
			if(t->right->title < name) {
				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}
	}
	else 
		;

	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> *& k2) const {
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

template<class Comparable>
void AvlTree<Comparable>::makeEmpty() {

	makeEmpty(root);

}

template<class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable> *& t) const {
	


	if(t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;

}

template<class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable> *t) const {
	if(t != NULL) {
		printTree(t->left);
		cout << t->title << endl;
		printTree(t->right);
	}
}

template<class Comparable>
void AvlTree<Comparable>::printTree() const {
	if(isEmpty()) {
	}
	else {
		printTree(root);
	}
}

template<class Comparable>
AvlTree<Comparable>::~AvlTree() {

	makeEmpty();

}

template<class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree<Comparable> & rhs) {
	*this = rhs;
}


template<class Comparable>
bool AvlTree<Comparable>::isEmpty() const {
	if(root == NULL) {
		return true;
	}

	return false;
}


template<class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::clone(AvlNode<Comparable> *t) const {
	if(t == NULL) {
		return NULL;
	}

	else {
		return new AvlNode<Comparable>(t->element,clone(t->left),clone(t->right), t->height, t->title);
	
	}
}

template<class Comparable>
const AvlTree<Comparable>& AvlTree<Comparable>::operator=(const AvlTree<Comparable> &rhs) {
	if(this != &rhs) {

		
		root = clone(rhs.root);

		return *this;
	}

}


template<class Comparable>
void AvlTree<Comparable>::remove(const string name) {
	remove(name, root);
}

template<class Comparable>
void AvlTree<Comparable>::remove(const string name, AvlNode<Comparable> * & t) const{
	if(t == NULL) {
		return;
	}

	if(name < t->title) {
		remove(name, t->left);

	}

	else if (name > t->title) {
		remove(name, t->right);
	}

	else {
		if((t->left == NULL) || (t->right == NULL) ) {
			AvlNode<Comparable> *temp = t->left ? t->left : t->right;

			if(temp == NULL){
				temp = t;
				t = NULL;
			}
			else {
				*t = *temp;
			}

			delete temp;
		
		}

		else {
			AvlNode<Comparable> *temp = findMin(t->right);
			t->title = temp->title;
			t->element = temp->element;

			remove(temp->title, t->right);
		
		}
		

	}

	if(t == NULL) {
		return;
	}

	t->height = 1 + max(height(t->left), height(t->right));

	int bal = height(t->left) - height(t->right);

	if(bal > 1) {
		int bal2 = height(t->left->left) - height(t->left->right);

		if(bal2 >= 0) {
			
			rotateWithLeftChild(t);
		}

		else {
			rotateWithRightChild(t->left);
			rotateWithLeftChild(t);
			
		}

	}

	else if (bal < -1) {
		int bal2 = height(t->right->left) - height(t->right->right);
		
		if(bal2 <= 0) {
			
			rotateWithRightChild(t);
		}

		else {
			rotateWithLeftChild(t->right);
			rotateWithRightChild(t);
		}
	
	}

	return;


}





template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable> *& k1) const {
	AvlNode<Comparable> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode<Comparable> *& k3) const {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
	
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode<Comparable> *& k1) const {
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );


}




#endif