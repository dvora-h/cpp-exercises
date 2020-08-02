#include <iostream>
#include <limits>
static const size_t MAX_SIZE=std::numeric_limits<size_t>::max();
template<typename T>
class Vector
{
public:
	Vector();
	explicit Vector(size_t size, const T& val);
	Vector(Vector<T>& vector);
	~Vector();
	Vector<T>& operator=(const Vector<T>& vector);
	size_t size()const;
	size_t max_size()const;
	size_t capacity()const;
	void resize(size_t size, const T& val=T());
	void push_back(const T& add);
	void pop_back();
	bool empty()const;
	void reserve(size_t capacity);
	T& operator[](size_t index);
	const T& operator[](size_t index)const;
	T& at(size_t index);
	const T& at(size_t index)const;
	T& front();
	const T& front()const;
    T& back();
    const T& back()const;
    T* data();
    const T* data()const;
    void insert (size_t position, size_t n, const T& val);
    void erase (size_t position);
    void erase (size_t first, size_t last);
    void swap (Vector<T>& x);
    void clear();
private:
    void changeCapacity();
	T* m_vector;
	size_t m_size;
	size_t m_capacity;




};
template<typename T>
inline Vector<T>::Vector():m_vector(NULL), m_size(0), m_capacity(0){}
template<typename T>
inline Vector<T>::Vector(size_t size, const T& val):m_vector(new T[size]),m_size(size),m_capacity(size)
{
	for(size_t i=0;i<size;i++)
	{
		m_vector[i]=val;
	}

}
template<typename T>
inline Vector<T>::Vector(Vector<T>& vector):m_vector(new T[vector.m_capacity]),m_size(vector.size()),m_capacity(vector.capacity())
{
	for(size_t i=0;i<m_size;i++)
	{
		m_vector[i]=vector.m_vector[i];
	}
}
template<typename T>
inline Vector<T>::~Vector()
{
	delete[]m_vector;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
	T* original=m_vector;
	m_vector=new T[vector.m_capacity];
	delete[] original;
	for(size_t i=0;i<vector.m_size;i++)
	{
		m_vector[i]=vector.m_vector[i];
	}
	m_size=vector.m_size;
	m_capacity=vector.m_capacity;
	return *this;

}
template<typename T>
inline size_t Vector<T>::size()const
{
	return m_size;
}
template<typename T>
inline size_t Vector<T>::max_size()const
{
	return MAX_SIZE;
}
template<typename T>
inline size_t Vector<T>::capacity()const
{
	return m_capacity;
}
template<typename T>
inline void Vector<T>::resize(size_t size, const T& val)
{
    if (size<m_size){
        for (size_t i=size; i<m_size; i++){
            m_vector[i].~T();
        }
    }
    if (size > m_capacity){
        T* temp = new T[size];
        for(size_t i = 0; i<m_size; i++){
            temp[i] = m_vector[i];
        }
        delete[](m_vector);
        m_vector = temp;
        m_capacity = size;
    }
    for (size_t i = m_size; i<size; i++){
        m_vector[i] = val;
    }
    m_size = size;

}
template<typename T>
inline bool Vector<T>::empty()const
{
    return m_size == 0;
}
template<typename T>
inline void Vector<T>::reserve(size_t capacity)
{
	if(capacity > m_capacity)
	{
		T* original=m_vector;
		m_vector=new T[capacity];
		for(size_t i=0;i<m_size;i++)
		{
			m_vector[i]=original[i];
		}
		delete[] original;
		m_capacity=capacity;
	}
	
}
template<typename T>
inline T& Vector<T>::operator[](size_t index)
{
	return m_vector[index];
}
template<typename T>
inline const T& Vector<T>::operator[](size_t index)const
{
	return m_vector[index];
}
template<typename T>
inline T& Vector<T>::at(size_t index)
{
	if(index>=m_size)
		throw std::out_of_range("out of range!!");
	return m_vector[index];
}
template<typename T>
inline const T& Vector<T>::at(size_t index)const
{
	if(index>=m_size)
		throw std::out_of_range("out of range!!");
	return m_vector[index];
}
template<typename T>
inline T& Vector<T>::front()
{
	return m_vector[0];
}
template<typename T>
inline const T& Vector<T>::front()const
{
	return m_vector[0];
}
template<typename T>
inline T& Vector<T>::back()
{
	return m_vector[m_size-1];
}
template<typename T>
inline const T& Vector<T>::back()const
{
	return m_vector[m_size-1];
}
template <typename T>
inline T* Vector<T>::data() { return m_vector;}
template <typename T>
inline const T* Vector<T>::data() const { return m_vector;}
template <typename T>
inline void Vector<T>::push_back(const T& add){
    if(m_size==m_capacity){
        changeCapacity();
    }
    m_vector[m_size] = add;
    m_size++;
}
template <typename T>
inline void Vector<T>::changeCapacity() {
    T* temp = m_capacity!=0 ? new T[m_capacity*2]: new T[1];
    delete[](m_vector);
    m_vector = temp;
    m_capacity = m_capacity==0? 1: m_capacity*2;
}
template <typename T>
inline void Vector<T>::pop_back() {
    m_vector[m_size-1].~T();
    m_size--;
}
template <typename T>
void Vector<T>::insert (size_t position, size_t n, const T& val){
    size_t i;
    if (m_size+n > m_capacity){
        T* temp = new T[m_size+n];
        for (i = 0; i<m_size; i++){
            temp[i] = m_vector[i];
        }
        delete[](m_vector);
        m_vector = temp;
        m_capacity = m_size+n;
    }
    for (size_t j = 0; j<4; j++){
        m_vector[m_size+n-1-j] = m_vector[m_size-1-j];
    }
    for (i = position; i<position+n; i++){
        m_vector[i+n] = m_vector[i];
        m_vector[i] = val;
    }
    m_size += n;
}
template <typename T>
void Vector<T>::erase (size_t position){
    size_t i;
    for(i = position; i<m_size-1; i++){
        m_vector[position] = m_vector[position+1];
    }
    ~m_vector[m_size-1];
    m_size--;
}
template <typename T>
void Vector<T>::erase (size_t first, size_t last){
    size_t i;
    for(i = first; i<m_size-last-1; i++){
        m_vector[first] = m_vector[first+last];
    }
    for (i; i<m_size; i++){
        m_vector[i].~T();
    }
    m_size-= last-first;
}
template <typename T>
void Vector<T>::swap (Vector<T>& x){
    Vector<T> temp = x;
    x = *this;
    *this = temp;
}
template <typename T>
void Vector<T>::clear(){
    for (size_t i = 0; i< m_size; i++){
        m_vector[i].~T();
    }
    m_size = 0;
}
