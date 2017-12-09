#pragma once
#include<iostream>
template<class T>
struct HuffNode {
	T key;
	int weight;
	HuffNode*left;
	HuffNode*right;
	HuffNode*parent;
};
template<class T>
class HuffTree {

};