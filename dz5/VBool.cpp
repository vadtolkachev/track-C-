#include "VBool.hpp"
#include <stdio.h>
#include <stdexcept>


VBool::VBool(uint64_t &mem, const uint64_t &index):
	m_mem(mem),
	m_index(index)
{
	if(index >= UINT64_BIT_SIZE)
		throw std::runtime_error("Index overflow");
}


VBool &VBool::operator=(const VBool &bit) noexcept
{
	m_mem |= ((bit.m_mem >> bit.m_index) & 1) << m_index;
	
	return *this;
}


VBool &VBool::operator=(const bool byte) noexcept
{
	uint64_t tmp = static_cast<uint64_t>(byte);
	m_mem |= tmp << m_index;

	return *this;
}


VBool::operator bool() const noexcept
{
	return static_cast<bool>((m_mem >> m_index) & 1);
}
