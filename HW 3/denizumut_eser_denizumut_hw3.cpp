#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

//Deniz Umut Eser

struct contact { string name, surname, number, city, full_name; };

//__operator overloads__//
bool operator > (contact& lhs, contact& rhs) { return lhs.full_name > rhs.full_name; }
bool operator < (contact& lhs, contact& rhs) { return lhs.full_name < rhs.full_name; }
bool operator <= (contact& lhs, contact& rhs) { return lhs.full_name <= rhs.full_name; }
bool operator < (string lhs, contact rhs) { return lhs < rhs.full_name; }
bool operator > (string lhs, contact rhs) { return lhs > rhs.full_name; }
bool operator == (string lhs, contact rhs) { return lhs == rhs.full_name; }
bool operator <= (contact lhs, string rhs) { return lhs.full_name <= rhs; }
bool operator >= (contact lhs, string rhs) { return lhs.full_name >= rhs; }
bool operator > (contact lhs, string rhs) { return lhs.full_name > rhs; }
bool operator < (contact lhs, string rhs) { return lhs.full_name < rhs; }

string toUpper(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 97) //if character is lowercase turn it into upper case
			s[i] -= 32;
	}
	return s;
}

void vector_insert(vector<contact> &v, string filename)
{
	ifstream input;
	string line;
	input.open(filename);
	while (getline(input, line))//insert each person to vector
	{
		stringstream iss(line);
		contact newPerson;
		iss >> newPerson.name >> newPerson.surname >> newPerson.number >> newPerson.city;
		newPerson.full_name = newPerson.name + " " + newPerson.surname;
		v.push_back(newPerson);
	}
}

//__Sorting Algorithms__//

template <class T>
const T& median3(vector<T>& v,
	int left, int right)//median finder
{
	int center = (left + right) / 2;
	if (v[center] < v[left])
		swap(v[left], v[center]);
	if (v[right] < v[left])
		swap(v[left], v[right]);
	if (v[right] < v[center])
		swap(v[center], v[right]);
	// Place pivot at position right - 1
	swap(v[center], v[right - 1]);
	return v[right - 1];
}

//quick sort helper function
template <class T>
void quick_sort(vector<T>& v,
	int left, int right)
{
	if (left + 10 <= right)
	{
		T pivot = median3(v, left, right);
		// Begin partitioning
		int i = left, j = right - 1;
		for (;;)
		{
			while (v[++i] < pivot) {}

			while (pivot < v[--j]) {}

			if (i < j)
				swap(v[i], v[j]);
			else
				break;
		}
		swap(v[i], v[right - 1]);   // Restore pivot

		quick_sort(v, left, i - 1);       // Sort small elements
		quick_sort(v, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertion_sort(v, left, right);
}

//quick sort
template <class T>
void quick_sort(vector<T>& v) 
{
	quick_sort(v, 0, v.size() - 1);
}

//insertion sort
template <class T>
void insertion_sort(vector<T>& v) 
{
	int j;
	// loop over the passes
	for (int p = 1; p < v.size(); p++)
	{
		T tmp = v[p];
		// loop over the elements
		for (j = p; j > 0 && tmp < v[j - 1]; j--)
			v[j] = v[j - 1];
		v[j] = tmp;
	}
}

//insertion sort to be used in quick sort
template <class T>
void insertion_sort(vector<T>& v, int left, int right)
{
	for (int p = left + 1; p <= right; p++)
	{
		T tmp = v[p];
		int j;

		for (j = p; j > left && tmp < v[j - 1]; j--)
			v[j] = v[j - 1];
		v[j] = tmp;
	}
}

//in place merge sort
template <class T>
void merge(vector<T> &v, int start, int middle, int end)
{
	int second_start = middle + 1;
	if (v[middle] <= v[second_start])
		return; //sorted already
	while (start <= middle && second_start <= end) 
	{
		if (v[start] <= v[second_start])
			start = start + 1;
		else 
		{
			int index = second_start;
			T temp = v[second_start];
			
			while (index != start) 
			{
				v[index] = v[index - 1]; //shift elements
				index = index - 1;
			}
			v[start] = temp;
			
			start = start + 1;
			middle = middle + 1;
			second_start = second_start + 1;
		}
	}
}

template<class T>
void mergeSort(vector<T>&v, int left, int right)
{
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergeSort(v, left, middle); //first half
		mergeSort(v, middle + 1, right); //second half
		merge(v, left, middle, right);
	}
}

template <class T>
void merge_sort(vector<T>& v)
{
	mergeSort(v, 0, v.size() - 1);
}

//heap sort helper function
template <class T>
void heap_sort_percDown(vector<T>& v, int i, int n)
{
	int child;
	T tmp;
	for (tmp = v[i]; (2*i+1) < n; i = child)
	{
		child = (2*i+1);
		if (child != n - 1 && v[child] < v[child + 1])
			child++;
		if (v[child] > tmp)
			v[i] = v[child];
		else
			break;
	}
	v[i] = tmp;
}

//heap sort
template <class T>
void heap_sort(vector<T>& v) 
{
	// buildHeap
	for (int i = v.size() / 2; i >= 0; i--)
		heap_sort_percDown(v, i, v.size());
	// sort
	for (int j = v.size() - 1; j > 0; j--)
	{
		swap(v[0], v[j]);    // swap max to the last pos.
		heap_sort_percDown(v, 0, j); // re-form the heap
	}
}

//__Searching Algorithms_//

template <class T>
int lower_bound_b(vector<T>& v, int left, int right, string key) //lower bound finder for partial binary seach
{
	while (right >= left)
	{
		int middle = left + (right - left) / 2;

		if (v[middle] >= key)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return left;
}

template <class T>
int upper_bound_b(vector<T>& v, int left, int right, string key) //upper bound finder for partial binary search
{
	while (right >= left)
	{
		int middle = left + (right - left) / 2;

		if (v[middle].full_name.substr(0, key.length()) == key)
			left = middle + 1;

		else
			right = middle - 1;

	}
	return left;
}

//Binary Search
template <class T>
int binary_search(vector<T>& v, int left, int right, string key, string mode, int& lowerbound, int& upperbound)
{
	if (mode == "FULL") //if query is full name
	{
		while (right >= left)
		{
			int middle = left + (right - left) / 2;

			if (key == v[middle])
				return middle;

			if (key > v[middle])
				left = middle + 1;

			else
				right = middle - 1;
		}
	}
	else if (mode == "PARTIAL") //if query is partial name
	{
		//in order to print between,
		//find first matching key
		lowerbound = lower_bound_b(v, left, right, key);
		//find last matching key
		upperbound = upper_bound_b(v, lowerbound, right, key);
		if (lowerbound == upperbound) 
			return -1; //found nothing
		return -2; //found partial
	}
	//key not found
	return -1;
}
 
//Sequential Search
template <class T>
vector<int> sequential_search(vector<T>& v, int left, int right, string key, string mode)
{
	vector<int> temp;
	if (mode == "FULL") //if query is full name
	{
		while (right >= left)
		{
			if (key == v[left])
			{
				temp.push_back(left);
				break;
			}
			left = left + 1;
		}
	}
	else if (mode == "PARTIAL") //if query is partial name
	{
		while (right >= left)
		{
			if (v[left].full_name.substr(0, key.length()) == key)
				temp.push_back(left);
			
			left = left + 1;
			
		}
	}
	return temp;
}

template <class T>
void printv(vector<T>& v) //vector print for testing purposes
{
	for (int i = 0; i < v.size(); i++)
		cout << v[i].name << " " << v[i].surname << " " << v[i].number << " " << v[i].city << endl;
}

int main()
{
	string filename, query, words, search_type;
	int count = 0;
	long long timer;
	cout << "Please enter the contact file name: ";
	cin >> filename;
	cout << "Please enter the word to be queried: ";
	
	getline(cin >> ws, query); //get input with spaces
	istringstream iss(query);
	while (iss >> words) {count++;} //count words in given name

	//decide if search is partial or full name
	if (count == 1) { search_type = "PARTIAL"; }
	else if (count == 2) { search_type = "FULL"; }

	//__initilazing vectors__//
	vector<contact> temp; //vector for filing the data
	vector_insert(temp, filename); //populate the temp vector
	//vectors for each sorting alggorithm
	vector<contact> quick_vector = temp, insertion_vector = temp, merge_vector = temp, heap_vector = temp;

	
	//__sorting vectors__//
	//quick sort
	cout << endl << "Sorting the vector copies" << endl << "======================================" << endl;
	auto start = chrono::high_resolution_clock::now();
	quick_sort(quick_vector);
	auto end = chrono::high_resolution_clock::now();
	long long timer_quick = (end - start).count();
	cout << "Quick Sort Time: " << timer_quick << " Nanoseconds" << endl;
	//insertion sort
	start = chrono::high_resolution_clock::now();
	insertion_sort(insertion_vector);
	end = chrono::high_resolution_clock::now();
	long long timer_insertion = (end - start).count();
	cout << "Insertion Sort Time: " << timer_insertion << " Nanoseconds" << endl;
	//merge sort
	start = chrono::high_resolution_clock::now();
	merge_sort(merge_vector);
	end = chrono::high_resolution_clock::now();
	long long timer_merge = (end - start).count();
	cout << "Merge Sort Time: " << timer_merge << " Nanoseconds" << endl;
	//heap search
	start = chrono::high_resolution_clock::now();
	heap_sort(heap_vector);
	end = chrono::high_resolution_clock::now();
	long long timer_heap = (end - start).count();
	cout << "Heap Sort Time: " << timer_heap << " Nanoseconds" << endl;
	cout << endl;

	//__searching vectors__//
	int upperbound = 0, lowerbound = 0, index;
	cout << "Searching for " << query << endl << "======================================" << endl << "Search results for Binary Search:" << endl;

	//Binary Search
	
	start = chrono::high_resolution_clock::now();
	for (int n = 0; n < 100; n++) //taking average time
	{
		index = binary_search(quick_vector, 0, quick_vector.size() - 1, query, search_type, lowerbound, upperbound);
	}
	end = chrono::high_resolution_clock::now();
	long long timer_binary = ((end - start)/100.0).count();

	if (index == -1) //if nothing is found
		cout << toUpper(query) << " does NOT exist in the dataset" << endl;

	else if (search_type == "FULL") //print only the exact matching contact
	{
		contact found = quick_vector[index];
		cout << toUpper(found.full_name) << " " << found.number << " " << found.city << endl;
	}
	else if (search_type == "PARTIAL") //print all matching contacts
	{
		for (int i = lowerbound; i < upperbound; i++)
		{
			contact found = quick_vector[i];
			cout << toUpper(found.full_name) << " " << found.number << " " << found.city << endl;
		}
	}
	cout << endl << "Binary Search Time: " << timer_binary << " nanoseconds" << endl << endl << "Search results for Sequential Search:" << endl;
	
	//Sequential Search
	upperbound = 0, lowerbound = 0;
	vector<int>temp2;
	start = chrono::high_resolution_clock::now();
	for (int n = 0; n < 100; n++) //taking average time
	{
		temp2 = sequential_search(quick_vector, 0, quick_vector.size() - 1, query, search_type);
	}
	end = chrono::high_resolution_clock::now();
	long long timer_sequential = ((end - start)/100.0).count();
	
	if (temp2.size() == 0) //if nothing is found
		cout << toUpper(query) << " does NOT exist in the dataset" << endl;

	else if (search_type == "FULL") //print only the exact matching contact
	{
		contact found = quick_vector[temp2[0]];
		cout << toUpper(found.full_name) << " " << found.number << " " << found.city << endl;
	}
	else if (search_type == "PARTIAL") //print all matching contacts
	{
		for (int i = 0; i < temp2.size(); i++)
		{
			contact found = quick_vector[temp2[i]];
			cout << toUpper(found.full_name) << " " << found.number << " " << found.city << endl;
		}
	}
	cout << endl << "Sequential Search Time: " << timer_sequential << " nanoseconds" << endl << endl;

	//display "speedups"
	cout << "SpeedUp between Search Algorithms" << endl << "======================================" << endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << (double)timer_sequential/timer_binary << endl << endl;
	cout << "SpeedUp between Sorting Algorithms" << endl << "======================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << (double)timer_insertion/timer_quick << endl;
	cout << "(Merge Sort/ Quick Sort) SpeedUp = " << (double)timer_merge/timer_quick << endl;
	cout << "(Heap Sort/ Quick Sort) SpeedUp = " << (double)timer_heap/timer_quick << endl;
	return 0;
}