#pragma once
#include "common_zip.hpp"

namespace detail
{
	inline bool init_encoder(mz_stream* stream,uint32_t level)
	{
		const auto ret = mz_deflateInit(stream,level);
		if(ret == MZ_OK)
		{
			return true;
		}
		return false;
	}
	inline std::vector<std::uint8_t> compress(mz_stream* stream,const std::vector<uint8_t>& data)
	{
		std::vector<uint8_t> ret;

		if(code(mz_deflate,stream,data,&ret))
		{
			return ret;			
		}
		return {};
	}
	
}
