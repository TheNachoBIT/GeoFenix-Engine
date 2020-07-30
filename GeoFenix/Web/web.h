#pragma once
#include "curl/curl.h"
#include <iostream>
#include 

namespace geofenix {
	namespace web {
		/*
		How to use:
		std::string string;
		get("http://google.com", string);
		
		Returns a vector*/
		void get(char const*  url, std::string& response_string);
	}
}