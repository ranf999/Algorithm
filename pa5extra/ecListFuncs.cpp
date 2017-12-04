/*  Name: Zhuoya Shi
 *  USC NetID: zhuoyash
 *  CS 455 Spring 2017
 *
 *  See ecListFuncs.h for specification of each function.
 */

#include <iostream>

#include <cassert>

#include "ecListFuncs.h"

using namespace std;


int lastIndexOf(ListType list, int val) {
	int latestIndex = -1;
	int index = 0;
	while(list) {
		if(list->data == val) {
			latestIndex = index;
		}
		list = list->next;
		index++;
	}
	return latestIndex;  // stub code to get it to compile
}



void removeNode(ListType& list, Node* node) {
	ListType tmp = list;
	Node* prev = NULL;
	while(tmp) {
		if(tmp == node) {
			if(prev == NULL) {
				list = list->next;
			}
			else {
				prev->next = tmp->next;
			}
			delete tmp;
			return;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void removeFollowingEvens(ListType &list) {
	bool hasEven = false;
	ListType tmp = list;
	while(tmp) {
		if(tmp->data % 2 == 0) {
			if(hasEven == false) {
				hasEven = true;
			}
			else {
				Node* nextNode = tmp->next;
				removeNode(list, tmp);
				tmp = nextNode;
				continue;
			}
		}
		tmp = tmp->next;
	}
}



void mirrorList(ListType & list) {
	ListType tmp = list;
	Node* mirror = NULL;
	if(!tmp) return;
	while(tmp) {
		if(mirror == NULL) {
			mirror = new Node(tmp->data);
		}
		else {
			Node* node = new Node(tmp->data, mirror);
			mirror = node;
		}
		if(tmp->next == NULL) {
			tmp->next = mirror;
			break;
		}
		tmp = tmp->next;
	}
}



void rotateRight(ListType &list, int k) {
	int length = 0;
	ListType tmp = list;
	while(tmp) {
		length++;
		tmp = tmp->next;
	}

	int remain = length - k;
	int index = 1;
	tmp = list;
	Node* prev = NULL;
	ListType newList = NULL;
	if(remain <= 0) return;
	while(tmp) {
		if(index > remain) {
			newList = tmp;
			prev->next = NULL;
			while(tmp->next) {
				tmp = tmp->next;
			}
			tmp->next = list;
			list = newList;
			break;
		}
		prev = tmp;
		tmp = tmp->next;
		index++;
	}
}
