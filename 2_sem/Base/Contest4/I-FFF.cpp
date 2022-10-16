#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <cstddef>

struct out_of_range
{

};

template <class ForwardIterator, class T>
ForwardIterator lw_bound (ForwardIterator first, ForwardIterator last, const T& val) {
  
    ForwardIterator it;
    iterator_traits<ForwardIterator>::difference_type count, step;
    count = distance(first,last);
    while (count>0) {
        it = first; step=count/2; std::advance(it,step);
        if (*it<val) {                 
            first=++it;
            count-=step+1;
        } else {
            count=step;
        }
    }
    return first;
}

template <class ForwardIterator, class T>
ForwardIterator up_bound (ForwardIterator first, ForwardIterator last, const T& val) {
    ForwardIterator it;
    iterator_traits<ForwardIterator>::difference_type count, step;
    count = std::distance(first,last);
    while (count>0) {
        it = first; step=count/2; 
        std::advance (it,step);
        if (!(val<*it)) { 
            first=++it; count-=step+1;  
        } else { 
            count=step;
        }
    }
    return first;
}


template<class T> class Vector
{
public:
	/* ----- Constructors ----- */

	// Default constructor
	Vector();

	explicit Vector(int s);

	// Copy constructor
	Vector(const Vector& arg);

	// Copy Assingment
	Vector<T>& operator=(const Vector<T>& arg);

	// Destructor
	~Vector();

	/*----------------------------*/





	/* -------- ITERATORS --------*/

	class iterator;

	iterator begin();

	iterator begin() const;

	iterator end();
	
	iterator end() const;

	iterator cbegin() const;

	iterator cend() const;

	/*----------------------------*/





	/* -------- CAPACITY -------- */

	bool empty() const;

	// Returns size of allocated storate capacity
	size_t capacity() const;

	// Requests a change in capacity
	// reserve() will never decrase the capacity.
	void reserve(int newmalloc);

	// Changes the Vector's size.
	// If the newsize is smaller, the last elements will be lost.
	// Has a default value param for custom values when resizing.
	void resize(int newsize, T val = T());

	// Returns the size of the Vector (number of elements). 
	size_t size() const;

	// Returns the maximum number of elements the Vector can hold
	size_t max_size() const;

	// Reduces capcity to fit the size
	void shrink_to_fit();

	/*----------------------------*/





	/* -------- MODIFIERS --------*/

	// Removes all elements from the Vector
	// Capacity is not changed.
	void clear();

	// Inserts element at the back
	void push_back(const T& d);

	// Removes the last element from the Vector
	void pop_back();

	/*----------------------------*/





	/* ----- ELEMENT ACCESS ----- */

	// Access elements with bounds checking
	T& at(int n);

	// Access elements with bounds checking for constant Vectors.
	const T& at(int n) const;

	// Access elements, no bounds checking
	T& operator[](int i);

	// Access elements, no bounds checking
	const T& operator[](int i) const;

	// Returns a reference to the first element
	T& front();

	// Returns a reference to the first element
	const T& front() const;

	// Returns a reference to the last element
	T& back();

	// Returns a reference to the last element
	const T& back() const;

	// Returns a pointer to the array used by Vector
	T* data();

	// Returns a pointer to the array used by Vector
	const T* data() const;

	/*----------------------------*/

private:
	size_t	_size;		// Number of elements in Vector
	T*		_elements;	// Pointer to first element of Vector
	size_t	_space;		// Total space used by Vector including
						// elements and free space.
};



template<class T> class Vector<T>::iterator
{
public:
	iterator(T* p)
		:_curr(p)
	{}

	iterator& operator++()
	{
		_curr++;
		return *this;
	}

	iterator& operator--()
	{
		_curr--;
		return *this;
	}

	T& operator*()
	{
		return *_curr;
	}

	bool operator==(const iterator& b) const
	{
		return *_curr == *b._curr;
	}

	bool operator!=(const iterator& b) const
	{
		return *_curr != *b._curr;
	}

    int64_t operator- (const interator& b) const {
        return this->_curr - b._curr;
    }

    int64_t operator- (interator b) {
        return this->_curr - b._curr;
    }

private:
	T* _curr;
};



// Constructors/Destructor
template<class T>
Vector<T>::Vector()
	:_size(0), _elements(0), _space(0)
{}

template<class T>
inline Vector<T>::Vector(int s)
	:_size(s), _elements(new T[s]), _space(s)
{
	for (int index = 0; index < _size; ++index)
		_elements[index] = T();
}

template<class T>
inline Vector<T>::Vector(const Vector & arg)
	:_size(arg._size), _elements(new T[arg._size])
{
	for (int index = 0; index < arg._size; ++index)
		_elements[index] = arg._elements[index];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
	if (this == &a) return *this;	// Self-assingment not work needed

									// Current Vector has enough space, so there is no need for new allocation
	if (a._size <= _space)
	{
		for (int index = 0; index < a._size; ++index)
		{
			_elements[index] = a._elements[index];
			_size = a._size;
			return *this;
		}
	}

	T* p = new T[a._size];

	for (int index = 0; index < a._size; ++index)
		p[index] = a._elements[index];

	delete[] _elements;
	_size = a._size;
	_space = a._size;
	_elements = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] _elements;
}



// Iterators
template<class T>
inline typename Vector<T>::iterator Vector<T>::begin()
{	
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::begin() const
{
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return Vector<T>::iterator(&_elements[_size]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::end() const
{
	return Vector<T>::iterator(&_elements[_size]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::cbegin() const
{
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::cend() const
{
	return Vector<T>::iterator(&_elements[_size]);
}



// Capacity
template<class T>
inline bool Vector<T>::empty() const
{
	return (_size == 0);
}

template<class T>
inline size_t Vector<T>::capacity() const
{
	return _space;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
	if (newalloc <= _space) return;

	T* p = new T[newalloc];

	for (int i = 0; i < _size; ++i)
		p[i] = _elements[i];

	delete[] _elements;

	_elements = p;

	_space = newalloc;
}

template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
	reserve(newsize);

	for (int index = _size; index < newsize; ++index)
		_elements[index] = T();

	_size = newsize;
}

template<class T>
inline size_t Vector<T>::size() const
{
	return _size;
}



// Modifiers
template<class T>
inline void Vector<T>::push_back(const T& d)
{
	if (this->_space == 0)
		reserve(8);
	else if (_size == _space)
		reserve(2 * _space);

	_elements[_size] = d;

	++_size;
}



// Accessors
template<class T>
inline T & Vector<T>::at(int n)
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T>
inline const T & Vector<T>::at(int n) const
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T>
inline T & Vector<T>::operator[](int i)
{
	return _elements[i];
}

template<class T>
inline const T & Vector<T>::operator[](int i) const
{
	return _elements[i];
}

template<class T>
inline T& Vector<T>::front()
{
	return _elements[0];
}

template<class T>
inline const T& Vector<T>::front() const
{
	return _elements[0];
}

template<class T>
inline T& Vector<T>::back()
{
	return _elements[_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const
{
	return _elements[_size - 1];
}

template<class T>
inline T* Vector<T>::data()
{
	return _elements;
}

template<class T>
inline const T* Vector<T>::data() const
{
	return _elements;
}

#endif


#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int n;
struct node {
    int x, y, w;
    int id;
    bool operator<(node b) { return x < b.x; }
};


Vector<node> elem;
Vector<Vector<ll> > tree;
Vector<Vector<int> > sorted_y;


struct pr {
    int first;
    int second;
};

int comp (const void* lft, const void* rht) {
    return *(int*)rht - *(int*)lft;
}

void add(int i, int id, int delta);
void build(Vector<pr>& elem, int id) {
    // sort(sorted_y[id].begin(), sorted_y[id].end());
    qsort(sorted_y[id].data(), sorted_y[id].size(), sizeof(int), comp);

    //tree[id].assign(sorted_y[id].size(),0);
    tree[id].resize(sorted_y[id].size());
    for (size_t it = 0; it < tree[id].size(); ++it) {
        tree[id][it] = 0;
    }

    unique(sorted_y[id].begin(), sorted_y[id].end());


    for (pr e : elem) {
        int pos =
            lower_bound(sorted_y[id].begin(), sorted_y[id].end(), e.first) -
            sorted_y[id].begin();
        add(pos, id, e.second);
    }
}
ll sum(int l, int r, int id) {
    if (r < 0) return 0;
    ll result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) result += tree[id][r];
    return result;
}
ll sum(int r, int y) {
    if (r < 0) return 0;
    ll result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        int pos = upper_bound(sorted_y[r].begin(), sorted_y[r].end(), y) -
                  sorted_y[r].begin();
        if (pos < sorted_y[r].size() && sorted_y[r][pos] != y ||
            pos == sorted_y[r].size())
            pos--;
        result += sum(0, pos, r);
    }
    return result;
}
void add(int i, int id, int delta) {
    for (; i < tree[id].size(); i = (i | (i + 1))) tree[id][i] += delta;
}
void add(int l, int i, int y, int delta) {
    for (; i < n; i = (i | (i + 1))) {
        int pos = lower_bound(sorted_y[i].begin(), sorted_y[i].end(), y) -
                  sorted_y[i].begin();
        add(pos, i, delta);
    }
}
int main() {
    int m;
    string command;
    cin >> n;
    tree.resize(n), sorted_y.resize(n), elem.resize(n);
    vector<int> sorted_x(n);
    for (int i = 0; i < n; ++i) {
        cin >> elem[i].x >> elem[i].y >> elem[i].w;
        elem[i].id = i;
        sorted_x[i] = elem[i].x;
        // sorted_y[i] = elem[i].y;
    }
    sort(elem.begin(), elem.end());
    sort(sorted_x.begin(), sorted_x.end());
    // sort(sorted_y.begin(),sorted_y.end());
    Vector<int> pos_x(n);
    for (int i = n - 1; i >= 0; --i) {
        pos_x[elem[i].id] = i;
        int len = i - (i & (i + 1)) + 1;
        sorted_y[i].resize(len);
        Vector<pr> tmp(len);
        int id = 0;
        for (int j = i - len + 1; j <= i; ++j) {
            sorted_y[i][id] = elem[j].y;
            tmp[id] = {elem[j].y, elem[j].w};
            id++;
        }
        build(tmp, i);
    }
    cin >> m;
    while (m--) {
        cin >> command;
        if (command == "change") {
            int i, value;
            cin >> i >> value;
            --i;
            add(0, pos_x[i], elem[pos_x[i]].y, value - elem[pos_x[i]].w);
            elem[pos_x[i]].w = value;
        } else {
            int x, y;
            cin >> x >> y;
            int pos = upper_bound(sorted_x.begin(), sorted_x.end(), x) -
                      sorted_x.begin();
            if (pos < n && sorted_x[pos] != x || pos == n) pos--;
            cout << sum(pos, y) << '\n';
        }
    }
    return 0;
}