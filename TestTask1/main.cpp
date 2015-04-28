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
#define min_value 1 //values' min bound
#define max_value 9 //values' max bound
#define deleted_numbers 8 //max number of deleted elements

std::vector<int> vec;
std::map<int, int> mmap;

//get random number
template<typename T>
int getRandomNumber(T min_random_value, T max_random_value)
{
	return min_random_value + rand() % max_random_value;
}

//rearrange vector to begin with survived elements and get iterator to "erase from" position
template<typename T, template <typename, typename> class SampleType>
typename std::vector<T, std::allocator<T>>::iterator deleteMismatches(std::vector<T, std::allocator<T>>& vec_to_process, const SampleType<T, std::allocator<T>>& seq_to_compare)
{	
	typename std::vector<T, std::allocator<T>>::iterator delim_pos = std::remove_if(vec_to_process.begin(), vec_to_process.end(), [seq_to_compare](T i)->bool
	{
		for (typename SampleType<T, std::allocator<T>>::const_iterator it = seq_to_compare.cbegin(); it != seq_to_compare.cend(); ++it)
		{
			if (*it == i)
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
		vec[i] = getRandomNumber<int>(min_value, max_value);
		mmap[i] = getRandomNumber<int>(min_value, max_value);
	}

	/*Result****************************************************************/
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
	//Result***************************************************************

	//2. Delete random number of values
	int deleted_number_vec = getRandomNumber(0, deleted_numbers);
	int deleted_number_mmap = getRandomNumber(0, deleted_numbers);

	vec.resize(N - deleted_number_vec);
	vec.shrink_to_fit();

	std::map<int, int>::iterator it = mmap.find(N - deleted_number_mmap);
	mmap.erase(it, mmap.end());

	/*Result****************************************************************/
	std::cout << "Deletó random elements: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
		std::cout << *itv << ' ';
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << "Map: ";
	for (std::map<int, int>::iterator itm = mmap.begin(); itm != mmap.end(); ++itm)
		std::cout << itm->second << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Result***************************************************************

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
	std::vector<int>::iterator delim_pos_vec = deleteMismatches<int, std::vector>(vec, map_copy);
	vec.erase(delim_pos_vec, vec.end());

	std::vector<int>::iterator delim_pos_map = deleteMismatches<int, std::vector>(map_copy, vec);
	map_copy.erase(delim_pos_map, map_copy.end());
	
	//transofrm back to map
	mmap.clear();
	for (std::vector<int>::iterator it = map_copy.begin(); it != map_copy.end(); ++it)
	{
		mmap[it - map_copy.begin()] = *it;
	}

	/*Result****************************************************************/
	std::cout << "Synchronize: " << std::endl;
	std::cout << std::setw(10) << std::right << "Vector: ";
	for (std::vector<int>::iterator itv = vec.begin(); itv != vec.end(); ++itv)
		std::cout << *itv << ' ';
	std::cout << std::endl;
	std::cout << std::setw(10) << std::right << "Map: ";
	for (std::map<int, int>::iterator itm = mmap.begin(); itm != mmap.end(); ++itm)
		std::cout << itm->second << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
	//Result***************************************************************

	_getch();
	return 0;
}
