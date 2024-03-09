//this
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "dns_bank_api.hpp"

int main () {
	std::cout<<dns::bank_transfer("2090946417312688765", "4214609853660062373", "1946434610", "0.1112")<<std::endl;
	
	return 0;
}
