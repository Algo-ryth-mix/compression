#pragma once
#include <lzma.h>
#pragma warning(disable:26812)

namespace detail
{

	inline bool init_decoder(lzma_stream* stream,const uint64_t max_memuse = UINT64_MAX)
	{
		const auto result = lzma_stream_decoder(stream,max_memuse,LZMA_CONCATENATED);
		return result == LZMA_OK;
	}

	inline std::vector<uint8_t> decompress(lzma_stream* stream,const std::vector<uint8_t>& data)
	{
		std::vector<uint8_t> ret;

		if(code(stream,data,&ret))
		{
			return ret;			
		}
		return {};
		
	}
	
}
