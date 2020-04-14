#pragma once
#include "common_zip.hpp"

namespace detail
{
	inline bool init_decoder(mz_stream* stream)
	{
		const auto ret = mz_inflateInit(stream);
		if(ret == MZ_OK)
		{
			return true;
		}
		return false;
	}
	inline std::vector<std::uint8_t> decompress(mz_stream* stream,const std::vector<uint8_t>& data)
	{
		std::vector<uint8_t> ret;

		if(code(mz_inflate,stream,data,&ret))
		{
			return ret;			
		}
		return {};
	}
	
}
