#include <cstring>


VVector<VBool>::VVector() noexcept:
	m_size(0),
	m_capacity(0),
	m_data(nullptr)
{}


VVector<VBool>::VVector(const VVector &vec):
	m_size(vec.m_size),
	m_capacity(vec.m_capacity),
	m_data(static_cast<uint64_t *>(malloc(m_capacity/BYTE_SIZE)))
{
	if(!m_data)
		throw std::bad_alloc();

	memcpy(static_cast<void *>(m_data), vec.m_data, m_capacity/BYTE_SIZE);
}


VVector<VBool>::VVector(VVector &&vec) noexcept:
	m_size(vec.m_size),
	m_capacity(vec.m_capacity),
	m_data(vec.m_data)	
{
	vec.m_data = nullptr;
}


VVector<VBool>::~VVector() noexcept
{
	clear();
}


unsigned VVector<VBool>::getSize() const noexcept
{
	return m_size;
}


bool VVector<VBool>::isEmpty() const noexcept
{
	return m_size == 0;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"


VBool VVector<VBool>::at(const unsigned index)
{
	if(index > m_size)
		throw std::runtime_error("Index overflow");

	VBool tmp(m_data[index/64], index%64);
	return tmp;
}


bool VVector<VBool>::at(const unsigned index) const
{
	if(index > m_size)
		throw std::runtime_error("Index overflow");
	
	VBool tmp(m_data[index/64], index%64);
	return static_cast<bool>(tmp);
}


VBool VVector<VBool>::operator[](const unsigned index) noexcept
{
	VBool tmp(m_data[index/64], index%64);
	return tmp;
}


bool VVector<VBool>::operator[](const unsigned index) const noexcept
{
	VBool tmp(m_data[index/64], index%64);
	return static_cast<bool>(tmp);	
}


#pragma GCC diagnostic pop


VVector<VBool> &VVector<VBool>::operator=(const VVector &vec) noexcept
{
	this->~VVector();
	new(this) VVector(vec);

	return *this;	
}


VVector<VBool> &VVector<VBool>::operator=(VVector &&vec) noexcept
{
	swap(vec);
	return *this;	
}


void VVector<VBool>::swap(VVector &vec) noexcept
{
	std::swap(m_size, vec.m_size);
	std::swap(m_capacity, vec.m_capacity);
	std::swap(m_data, vec.m_data);
}


void VVector<VBool>::push(const bool data)
{	
	if(!m_capacity)
	{
		m_data = static_cast<uint64_t *>(malloc(sizeof(uint64_t)*VECTOR_SIZE));
		if(!m_data)
			throw std::bad_alloc();

		m_capacity = UINT64_BIT_SIZE*VECTOR_SIZE;
	}
	else if(m_size == m_capacity)
	{
		uint64_t *tmp = static_cast<uint64_t *>(realloc(static_cast<void *>(m_data), 2*m_capacity/BYTE_SIZE));
		if(!tmp)
			throw std::bad_alloc();

		m_data = tmp;
		m_capacity *= 2;
	}

	VBool tmp(m_data[m_size/64], m_size%64);
	tmp = data;
	m_size++;
}


void VVector<VBool>::pop()
{
	if(!m_size)
		throw std::runtime_error("Pop: underflow");

	if(m_capacity == 4*m_size)
		m_data = static_cast<uint64_t *>(realloc(static_cast<void *>(m_data), m_capacity/(2*BYTE_SIZE)));
	
	m_size--;
}


void VVector<VBool>::clear() noexcept
{
	free(m_data);
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}

