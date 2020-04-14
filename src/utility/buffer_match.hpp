#pragma once
#include <cstdint>
#include <vector>

namespace pixl
{
	inline bool buffer_match(const std::vector<uint8_t>& A,const std::vector<uint8_t>& B)
	{
		if(A.size() != B.size()) return false;

		for(std::size_t itr = 0; itr < A.size(); ++itr)
		{
			if(A[itr] != B[itr]) return false;
		}
		
		return true;
	}
}
