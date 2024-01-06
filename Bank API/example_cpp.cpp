//this
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "dns_bank_api.hpp"

int main () {
	std::cout<<dns::bank_status()<<std::endl;
	return 0;
}
