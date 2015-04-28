#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <time.h>
#include <conio.h>
#include <functional>
#include <algorithm> 
#include <iterator>

#define N 10 //number of initial sequence elements
#define max_random_value 9 //values' max bound
#define deleted_numbers 8 //max number of deleted elements

std::vector<int> vec;
std::map<int, int> mmap;

//get random number
int getRandomNumber(int min_value, int max_value)
{
	return min_value + rand() % max_value;
}

//rearrange vector to begin with survived elements and get iterator to "erase from" position class T, class Alloc = allocator<T>
template<typename SampleType>
std::vector<int>::iterator deleteMismatches(std::vector<int>& vec_to_process, const SampleType& set_to_compare)
{
	std::vector<int>::iterator delim_pos = std::remove_if(vec_to_process.begin(), vec_to_process.end(), [set_to_compare](int i)->bool
	{
		for (SampleType::const_iterator iset = set_to_compare.cbegin(); iset != set_to_compare.cend(); ++iset)
		{
			if (*iset == i)
				return false;
		}
		return true;
	});
	return delim_pos;
}

int main(int, char*[])
{
	//1. Initialize sequences
	srand(time(NULL));

	for (int i = 0; i < N; i++)
	{
		vec.resize(N);
		vec[i] = getRandomNumber(1, max_random_value);
		mmap[i] = getRandomNumber(1, max_random_value);
	}

	/*Debug info****************************************************************/
	std::cout << "Initialize sequences: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
	std::cout << *itv << ' ';
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << "Map: ";
	for (std::map<int, int>::iterator itm = mmap.begin(); itm != mmap.end(); ++itm)
	std::cout << itm->second << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Debug info***************************************************************

	//2. Delete random number of values
	int deleted_number_vec = getRandomNumber(0, deleted_numbers);
	int deleted_number_mmap = getRandomNumber(0, deleted_numbers);

	vec.resize(N - deleted_number_vec);
	vec.shrink_to_fit();

	std::map<int, int>::iterator it = mmap.find(N - deleted_number_mmap);
	mmap.erase(it, mmap.end());

	/*Debug info****************************************************************/
	std::cout << "Deleting elements: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
		std::cout << *itv << ' ';
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << "Map: ";
	for (std::map<int, int>::iterator itm = mmap.begin(); itm != mmap.end(); ++itm)
		std::cout << itm->second << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Debug info***************************************************************

	//3. Delete mismatches

	//transform mmap to vector to fit deleteMismatches function (remove_if )
	std::vector<int> map_copy;
	std::vector<int> vec_copy(vec.begin(), vec.end());

	std::transform(mmap.begin(), mmap.end(),
		std::back_inserter(map_copy),
		[](std::pair<const int, int> const & m)
	{
		return m.second;
	});

	//apply remove_if and delete elements starting from delimeter position
	std::vector<int>::iterator delim_pos_vec = deleteMismatches<std::vector<int>>(vec, map_copy);

	/*Debug info***************************************************************
	std::cout << "Remove if: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
		std::cout << *itv << ' ';
	std::cout << std::endl;
	//Debug info****************************************************************/

	vec.erase(delim_pos_vec, vec.end());

	std::vector<int>::iterator delim_pos_map = deleteMismatches<std::vector<int>>(map_copy, vec);

	/*Debug info***************************************************************
	std::cout << std::setw(10) << std::right << "Map_copy: ";
	for (std::vector<int>::iterator itm = map_copy.begin(); itm != map_copy.end(); ++itm)
		std::cout << *itm << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Debug info****************************************************************/

	map_copy.erase(delim_pos_map, map_copy.end());

	/*Debug info***************************************************************
	std::cout << "Erase Map_copy: " << std::endl;
	std::cout << std::setw(10) << std::right << "Map_copy: ";
	for (std::vector<int>::iterator itm = map_copy.begin(); itm != map_copy.end(); ++itm)
		std::cout << *itm << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Debug info****************************************************************/
	
	//transofrm back to map
	mmap.clear();
	for (std::vector<int>::iterator it = map_copy.begin(); it != map_copy.end(); ++it)
	{
		mmap[it - map_copy.begin()] = *it;
	}

	/*Debug info****************************************************************/
	std::cout << "Remove distinct: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
		std::cout << *itv << ' ';
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << "Map: ";
	for (std::map<int, int>::iterator itm = mmap.begin(); itm != mmap.end(); ++itm)
		std::cout << itm->second << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Debug info***************************************************************

	_getch();
	return 0;
}
