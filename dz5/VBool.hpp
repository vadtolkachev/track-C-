#pragma once
#include <cstdint>

const unsigned UINT64_BIT_SIZE = 64;
const unsigned BYTE_SIZE = 8;


class VBool
{
public:
	VBool() = delete;
	VBool(const VBool &bit) = delete;
	VBool(VBool &&bit) = default;
	VBool(uint64_t &byte, const uint64_t &index);

	VBool &operator=(const VBool &bit) noexcept;
	VBool &operator=(const bool byte) noexcept;

	[[gnu::pure]] explicit operator bool() const noexcept;

private:
	uint64_t &m_mem;
	const uint64_t m_index; /* uint64_t - to avoid implicit padding */
};