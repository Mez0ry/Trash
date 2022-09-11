#include <iostream>
#include "CircularBuffer2.hpp"

//* CIRCULAR BUFFER2 TEST#1
/**
 
int main() {
	try {
		CircularBuffer2 buff(5);

		buff.push(1);
		buff.push(2);
		buff.push(3);
		buff.push(3);
		buff.push(3);
		buff.push(6);
		std::cout << buff.read() << '\n';
		std::cout << buff.read() << '\n';
		std::cout << buff.read() << '\n';
		std::cout << buff.read() << '\n';
		std::cout << buff.read() << '\n';
		std::cout << buff.read() << '\n';
		std::cout << buff << '\n';

	}
	catch(BufferException& ex){
		std::cout << ex.what() << '\n';
		std::cout << ex.get_func() << '\n';
	}


	return 0;
}
*/