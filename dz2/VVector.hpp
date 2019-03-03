#pragma once


const unsigned VECTOR_SIZE = 2;


template <typename DataType>
class VVector
{
public:
	VVector();
	VVector(const VVector &vec);

	~VVector();

	unsigned getSize() const;
	bool isEmpty() const;

	DataType &operator[](unsigned index);
	VVector<DataType> &operator=(const VVector<DataType> &vec);

	void push(const DataType &data);
	void pop();
	void clear();

private:
	unsigned m_size;
	unsigned m_capacity;
	DataType *m_data;
};



template <typename DataType>
VVector<DataType>::VVector():
	m_size(0),
	m_capacity(0),
	m_data(nullptr)
{}


template <typename DataType>
VVector<DataType>::VVector(const VVector &vec):
	m_size(vec.m_size),
	m_capacity(vec.m_capacity),
	m_data(new DataType[m_capacity])
{
	for(unsigned i = 0; i < m_size; ++i)
		m_data[i] = vec.m_data[i];
}


template <typename DataType>
VVector<DataType>::~VVector()
{
	delete[] m_data;
}


template <typename DataType>
unsigned VVector<DataType>::getSize() const
{
	return m_size;
}


template <typename DataType>
bool VVector<DataType>::isEmpty() const
{
	return m_size == 0;
}


template <typename DataType>
DataType &VVector<DataType>::operator[](unsigned index)
{
	return m_data[index];
}


template <typename DataType>
VVector<DataType> &VVector<DataType>::operator=(const VVector<DataType> &vec)
{
	delete[] m_data;
	m_size = vec.m_size;
	m_capacity = vec.m_capacity;
	m_data = new DataType[m_size];
	for(unsigned i = 0; i < m_size; ++i)
		m_data[i] = vec.m_data[i];

	return *this;
}


template <typename DataType>
void VVector<DataType>::push(const DataType &data)
{
	//TODO: check bad alloc

	if(!m_capacity)
	{
		m_data = new DataType[VECTOR_SIZE];
		m_capacity = VECTOR_SIZE;
	}
	else if(m_capacity == m_size)
	{
		DataType *tmp = new DataType[2*m_capacity];

		for(unsigned i = 0; i < m_size; ++i)
			tmp[i] = m_data[i];
		
		delete[] m_data;
		m_data = tmp;
		m_capacity *= 2;
	}

	m_data[m_size++] = data;
}


template <typename DataType>
void VVector<DataType>::pop()
{
	//TODO: check null size, check bad alloc

	if(m_capacity == 2*m_size)
	{
		DataType *tmp = new DataType[m_size]();
		m_capacity = m_size;
		m_size--;

		for(unsigned i = 0; i < m_size; ++i)
			tmp[i] = m_data[i];

		delete[] m_data;
		m_data = tmp;
	}
	else
	{
		m_size--;
	}
}


template <typename DataType>
void VVector<DataType>::clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}