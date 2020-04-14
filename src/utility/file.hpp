#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

inline void write_file(const std::string& path,const std::vector<uint8_t>& container)
{
	const std::unique_ptr<FILE,decltype(&fclose)> file(
		fopen(std::string(path).c_str(),"wb"),
		fclose
	);
	if(container.size() == 0) __debugbreak();

	assert(file);

	fwrite(container.data(),sizeof(uint8_t),container.size(),file.get());

}

inline  std::vector<uint8_t> read_file(const std::string& path)
	{
		const std::unique_ptr<FILE,decltype(&fclose)> file(
			fopen(path.c_str(),"rb"),
			fclose
		);

		assert(file);

		fseek(file.get(),0L,SEEK_END);
		std::vector<uint8_t> container(ftell(file.get()));

		if(container.size() == 0) __debugbreak();

		fseek(file.get(),0L,SEEK_SET);
	

		fread(container.data(),sizeof(uint8_t),container.size(),file.get());

		return container;
}