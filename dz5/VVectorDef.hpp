#pragma once
#include <stdexcept>


template <typename DataType>
VVector<DataType>::VVector() noexcept:
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
VVector<DataType>::VVector(VVector &&vec) noexcept:
	m_size(vec.m_size),
	m_capacity(vec.m_capacity),
	m_data(vec.m_data)	
{
	vec.m_data = nullptr;
}


template <typename DataType>
VVector<DataType>::~VVector() noexcept
{
	clear();
}


template <typename DataType>
unsigned VVector<DataType>::getSize() const noexcept
{
	return m_size;
}


template <typename DataType>
bool VVector<DataType>::isEmpty() const noexcept
{
	return m_size == 0;
}


template <typename DataType>
DataType &VVector<DataType>::at(const unsigned index)
{
	if(index > m_size)
		throw std::runtime_error("Index overflow");

	return m_data[index];
}


template <typename DataType>
const DataType &VVector<DataType>::at(const unsigned index) const
{
	if(index > m_size)
		throw std::runtime_error("Index overflow");

	return m_data[index];
}


template <typename DataType>
DataType &VVector<DataType>::operator[](const unsigned index) noexcept
{
	return m_data[index];
}


template <typename DataType>
const DataType &VVector<DataType>::operator[](const unsigned index) const noexcept
{
	return m_data[index];
}


template <typename DataType>
VVector<DataType> &VVector<DataType>::operator=(const VVector &vec) noexcept
{
	this->~VVector();
	new(this) VVector(vec);

	return *this;
}

template <typename DataType>
VVector<DataType> &VVector<DataType>::operator=(VVector &&vec) noexcept
{
	swap(vec);
	return *this;
}


template <typename DataType>
void VVector<DataType>::swap(VVector &vec) noexcept
{
	std::swap(m_size, vec.m_size);
	std::swap(m_capacity, vec.m_capacity);
	std::swap(m_data, vec.m_data);
}


template <typename DataType>
void VVector<DataType>::push(const DataType &data)
{
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
	if(!m_size)
		throw std::runtime_error("Pop: underflow");

	if(m_capacity == 4*m_size)
	{
		DataType *tmp = new DataType[2*m_size]();
		m_capacity = 2*m_size;
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
void VVector<DataType>::clear() noexcept
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}