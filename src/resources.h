#ifndef __TANGY_RESOURCES_H__
#define __TANGY_RESOURCES_H__ 1

#include <string>
#include <exception>

void resources_init (const std::string & argv0);

std::string resource_filename(const std::string & filename);

#endif
