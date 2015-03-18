#include <iostream>
#include "oct/octree.hpp"

void cllbck(const oct::octree<float>& t, const oct::dim<float>& p){
	std::cout << p.x << ", " << p.y << ", " << p.z << std::endl;
}

int main(){
	const auto bounds = oct::bounds<float>(oct::dim<float>(0, 0, 0), oct::dim<float>(10, 10, 10));
	const auto p1 = oct::dim<float>(5, 5, 5), p2 = oct::dim<float>(6, 7, 10), p3 = oct::dim<float>(8, 7, 2);

	oct::octree<float> tree(bounds);
	tree.insert(p1);
	tree.insert(p2);
	tree.insert(p3);

	std::cout << std::boolalpha << (tree.find(p2) != nullptr) << std::endl;

	tree.remove(p2);

	oct::for_each(tree, &cllbck);

	tree.clear();
}
