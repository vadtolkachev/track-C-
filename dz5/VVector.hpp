#pragma once
#include <new>


const unsigned VECTOR_SIZE = 2;


template <typename DataType>
class VVector
{
public:
	VVector() noexcept;
	VVector(const VVector &vec);
	VVector(VVector &&vec) noexcept;

	~VVector() noexcept;

	[[gnu::pure]] unsigned getSize() const noexcept;
	[[gnu::pure]] bool isEmpty() const noexcept;

	DataType &at(const unsigned index);
	const DataType &at(const unsigned index) const;

	DataType &operator[](const unsigned index) noexcept;
	const DataType &operator[](const unsigned index) const noexcept;

	VVector<DataType> &operator=(const VVector &vec) noexcept;
	VVector<DataType> &operator=(VVector &&vec) noexcept;

	void swap(VVector &vec) noexcept;
	void push(const DataType &data);
	void pop();
	void clear() noexcept;

private:
	unsigned m_size;
	unsigned m_capacity;
	DataType *m_data;
};



#include "VVectorDef.hpp"
#include "VVectorBool.hpp"