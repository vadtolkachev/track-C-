#include "VBool.hpp"


const unsigned UINT64_BIT_SIZE = 64;
const unsigned BYTE_SIZE = 8;


template <>
class VVector<VBool>
{
public:
	VVector() noexcept;
	VVector(const VVector &vec);
	VVector(VVector &&vec) noexcept;

	~VVector() noexcept;

	[[gnu::pure]] unsigned getSize() const noexcept;
	[[gnu::pure]] bool isEmpty() const noexcept;

	VBool at(const unsigned index);
	bool at(const unsigned index) const;

	VBool operator[](const unsigned index) noexcept;
	bool operator[](const unsigned index) const noexcept;

	VVector<VBool> &operator=(const VVector &vec) noexcept;
	VVector<VBool> &operator=(VVector &&vec) noexcept;

	void swap(VVector &vec) noexcept;
	void push(const bool data);
	void pop();
	void clear() noexcept;

private:
	unsigned m_size;
	unsigned m_capacity;
	uint64_t *m_data;
};


#include "VVectorBoolDef.hpp"
