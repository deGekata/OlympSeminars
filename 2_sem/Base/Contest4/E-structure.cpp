#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <cstddef>

struct out_of_range
{

};

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

#include <vector>
#include <algorithm>
#include <iostream> 

struct pr {
    int64_t first;
    int64_t second;
};

struct pr_char {
    char first;
    int64_t second;
};


 
Vector<pr> a;
 
Vector<int64_t> sm_plus(400000);
Vector<int64_t> sm_minus(400000);
 
 
void build(int64_t id, int64_t L, int64_t R, Vector<int64_t>& sm){
    if (R - L == 1){
        sm[id] = a[L].first;
        return;
    }
    int64_t m = (L + R) / 2;
    build(id * 2 + 1, L, m, sm);
    build(id * 2 + 2, m, R, sm);
    sm[id] = sm[id * 2 + 1] + sm[id * 2 + 2];
}
 
 
void upd(int64_t id, int64_t L, int64_t R, int64_t i, int64_t val, Vector<int64_t>& sm){
    if (R - L == 1){
        sm[id] = val;
        return;
    }
    int64_t m = (L + R) / 2;
    if (i < m)
        upd(id * 2 + 1, L, m, i, val, sm);
    else
        upd(id * 2 + 2, m, R, i, val, sm);
    sm[id] = sm[id * 2 + 1] + sm[id * 2 + 2];
}
 
 
int64_t get_sum(int64_t id, int64_t L, int64_t R, int64_t s_l, int64_t s_r, Vector<int64_t>& sm){
    if (R <= s_l || s_r <= L)
        return 0;
    if (s_l <= L && R <= s_r)
        return sm[id];
    int64_t m = (L + R) / 2;
    int64_t sm1 = get_sum(id * 2 + 1, L, m, s_l, s_r, sm);
    int64_t sm2 = get_sum(id * 2 + 2, m, R, s_l, s_r, sm);
    return sm1+sm2;
}
 
int comp(const void* lft_, const void* rht_) {
    pr* lft = (pr*) lft_;
    pr* rht = (pr*) rht_;
    if (lft->first != rht->first) {
        return lft->first - rht->first;
    }

    return lft->second - rht->second;
}
 
int main()
{
    
    int64_t q;
    scanf("%ld", &q);
    // std::cin >> q;
    Vector<pr_char> operations(q);
    a.push_back({0, 0});
    for (int64_t i = 0; i < q; i++){
        scanf("\n%c %ld", &(operations[i].first), &(operations[i].second));
        // std::cin >> operations[i].first >> operations[i].second;
        if (operations[i].first == '+') {
            a.push_back({operations[i].second, 0});
        }
		printf("'%c'\n", operations[i].first);
    }

	printf("-----------------------");
    qsort(a.data(), a.size(), sizeof(pr), comp);
	for (size_t it = 0; it < a.size(); ++it) {
		printf("%ld %ld --\n", a[it].first, a[it].second);
	}
    // sort(a.begin(), a.end());
    // reverse(operations.begin(), operations.end());
 
    int64_t n = a.size();
    build(0, 1, n+1, sm_plus);
    Vector<int64_t> ans;
    for (int64_t i = 0; i < q; ++i) {
        if (operations[i].first == '+') {
            int64_t x = operations[i].second;
            int64_t l = 0;
            int64_t r = n;
            while (l + 1 < r) {
                int64_t mid = (l+r) >> 1;
                if (a[mid].first < x) l = mid;
                else r = mid;
            }
            int64_t ind = r+a[r].second++;
            upd(0, 1, n+1, ind, x, sm_minus);
        } else {
            int64_t x = operations[i].second;
            int64_t l = 0;
            int64_t r = n;
            while (l + 1 < r) {
                int64_t mid = (l+r) >> 1;
                if (a[mid].first <= x) l = mid;
                else r = mid;
            }
            int64_t question = get_sum(0, 1, n+1, 1, l+1, sm_plus) - get_sum(0, 1, n+1, 1, l+1, sm_minus);
            ans.push_back(question);
        }
    }
    for (int64_t i = ans.size()-1; i >= 0; --i) {
        printf("%ld\n", ans[i]);
    }
 
    return 0;
}