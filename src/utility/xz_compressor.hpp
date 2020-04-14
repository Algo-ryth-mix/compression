#pragma once
#include "compressor.hpp"
#include "compress_xz.hpp"
#include "decompress_xz.hpp"


class xz_compressor final : public pixl::compressor_base
{
public:
	xz_compressor(std::uint32_t preset = 5,bool extreme = false) : m_preset(preset), m_extreme(extreme){}
	
protected:
	data_type_t compress(const_data_ptr_t data) const override
	{
		lzma_stream stream= LZMA_STREAM_INIT;
		detail::init_encoder(&stream,m_preset | (m_extreme ? LZMA_PRESET_EXTREME : LZMA_PRESET_DEFAULT));
		return detail::compress(&stream,*data);

	}
		
	data_type_t decompress(const_data_ptr_t data) const override
	{
		lzma_stream stream= LZMA_STREAM_INIT;
		detail::init_decoder(&stream);
		return detail::decompress(&stream,*data);
	}

private:
	std::uint32_t m_preset;
	bool m_extreme;
	
};