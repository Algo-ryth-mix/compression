#pragma once
#include <cstdint>
#include <vector>

namespace pixl
{
	inline bool buffer_match(const std::vector<uint8_t>& A,const std::vector<uint8_t>& B)
	{
		if(A.size() != B.size()) return false;

		return memcmp(A.data(),B.data(),A.size()) == 0;
	}
}
