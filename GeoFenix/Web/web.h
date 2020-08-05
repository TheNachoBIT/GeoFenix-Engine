#pragma once
#include "curl/curl.h"
#include <iostream>

namespace geofenix {
	namespace web {
		/*
		How to use:
		std::string string;
		get("http://google.com", string);
		
		Returns a vector*/
		std::string get(char const*  url, std::string& response_string);

		void post(char const* url, const char*, std::string& string);
	}
}