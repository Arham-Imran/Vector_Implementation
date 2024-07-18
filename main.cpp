// few tests to check implementation
#include <iostream>
#include "vector.h"
using namespace std;

int main()
{
	vtr::vector<int> V({1, 2, 3});
	vtr::vector<int> Vtr(V);
	Vtr = { 5, 4, 3, 2 };
	V[0]++;
	V.assign(6, 6);
	cout << "V[0] = " << V[0] << '\t' << "V[5] = " << V[5] << endl;
	cout << "Element at front: " << Vtr.front() << '\t' << "Element at back: " << Vtr.back() << endl;
	cout << "Current Capacity: " << Vtr.capacity() << "\tCurrent size: " << Vtr.size() << endl;
	Vtr.reserve(10);
	cout << "New capacity (after reserving 10): " << Vtr.capacity() << "\tCurrent size: " << Vtr.size() << endl;
	Vtr.clear();
	cout << "New capacity (after clearing): " << Vtr.capacity() << "\tCurrent size: " << Vtr.size() << endl;
	vtr::vector<int> test;
	Vtr.insert(Vtr.begin(), 5);
	Vtr.insert(Vtr.end(), 6);
	cout << "After inserting values 5(at begin) and 6(at end)" << endl;
	for (int i = 0; i < Vtr.size(); i++)
	{
		cout << i << ": " << Vtr[i] << endl;
	}
	cout << "Creating new vector. Size = " << test.size() << " capacity: " << test.capacity() << endl;
	test.insert(test.begin(), 1);
	test.insert(test.end(), 3);
	int* it = test.begin();
	it++;
	test.insert(it, 2);
	test.insert(test.end(), 4);
	cout << "After inserting values 1(at begin) and 4(at end)" << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << i << ": " << test[i] << endl;
	}
	it = test.begin();
	it++;
	test.erase(it);
	test.erase(test.end());
	cout << "After erasing value 2(at middle) and 4(at end)" << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << i << ": " << test[i] << endl;
	}
	cout << "Before Capacity: " << test.capacity() << endl;
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	cout << "After pushing back values 4, 5 and 6" << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << i << ": " << test[i] << endl;
	}
	cout << "After Capacity: " << test.capacity() << endl;
	cout << "Before resize, size: " << Vtr.size() << " capacity: " << Vtr.capacity() << endl;
	Vtr.resize(4, 5);
	cout << "After resize(size = 4, val = 5), size: " << Vtr.size() << " capacity: " << Vtr.capacity() << endl;
	for (int i = 0; i < Vtr.size(); i++)
	{
		cout << i << ": " << Vtr[i] << endl;
	}
	cout << "Vtr before:\n";
	for (int i = 0; i < Vtr.size(); i++)
	{
		cout << i << ": " << Vtr[i] << endl;
	}
	cout << "test before:\n";
	for (int i = 0; i < test.size(); i++)
	{
		cout << i << ": " << test[i] << endl;
	}
	test.swap(Vtr);
	cout << "Vtr after:\n";
	for (int i = 0; i < Vtr.size(); i++)
	{
		cout << i << ": " << Vtr[i] << endl;
	}
	cout << "test after:\n";
	for (int i = 0; i < test.size(); i++)
	{
		cout << i << ": " << test[i] << endl;
	}
	return 0;
}