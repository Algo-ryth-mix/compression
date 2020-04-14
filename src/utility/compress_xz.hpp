#pragma once
#include <lzma.h>
#include <vector>

#include "common_xz.hpp"
#pragma warning(disable:26812)
namespace detail {
	inline uint32_t create_preset(uint32_t level,bool extreme)
	{
		return level | (extreme ? LZMA_PRESET_EXTREME : LZMA_PRESET_DEFAULT);
	}
	inline bool init_encoder(lzma_stream* stream, uint32_t preset = 5 | LZMA_PRESET_DEFAULT)
	{
		const auto ret = lzma_easy_encoder(stream,preset,LZMA_CHECK_CRC64);
		if(ret == LZMA_OK)
		{
			return true;
		}

		return false;
	}
	inline std::vector<std::uint8_t> compress(lzma_stream * stream, const std::vector<uint8_t>& data)
	{
		std::vector<uint8_t> ret;

		if(code(stream,data,&ret))
		{
			return ret;			
		}
		return {};
	}
}

