#pragma once
#define _CRT_SECURE_NO_WARNINGS // fopen vs fopen_s
#include <cstdint> // std::int32_t
#include <string>  // std::string::c_str
#include <cstdio>  // fopen, fclose, ftell, fseek, SEEK_END, FILE
namespace pixl
{
	inline std::int32_t filesize( const std::string & name)
	{

		//open file ptr
		FILE* f = fopen(name.c_str(),"rb");
		if(!f) return -1;

		//seek to 0 bytes offset to the EOF
		fseek(f,0,SEEK_END);

		//get cursor position
		const std::int32_t len = ftell(f);

		//close file ptr
		fclose(f);

		return len;
	}
}
