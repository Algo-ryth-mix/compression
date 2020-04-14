#pragma once

#define PIXL_GUARD_BAD_ALLOC(X) try { (X); }catch(std::bad_alloc& e) {std::printf("ran out of memory!");exit(1);}

namespace pixl
{

}