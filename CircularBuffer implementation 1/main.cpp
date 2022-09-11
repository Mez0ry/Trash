#include "CircularBuffer.hpp"
#include <algorithm>
/*
* TEST #1
* Что нового: Перегружен оператор << для ostream 
int main() // main
{
	CircularBuffer<float, 5> buff;

	buff.push_back(2.25);
	buff.push_back(3.25);
	buff.push_back(4.25);
	buff.push_back(5.25);
	buff.push_back(6.25);
	buff.push_back(7.25); // not pushed_back  (isFull)
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n'; // m_isEmpty = true
	buff.push_back(7.25); //we previously read the data and now we can add element again
	std::cout << buff.get_elem() << '\n';
	buff.push_back(8.25); // we can add more elements
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.isEmpty() << '\n';
	std::cout << (char)'\n\n' << buff << '\n'; // output: 7.25 8.25 4.25 5.25 6.25

return 0;
} // !main
*/
/* TEST #2
* Что нового: Перегружен метод push_back использующий fold выражения 
* 
int main() // main
{
 CircularBuffer<int, 1> buff;
buff.isEmpty();
buff.push_back(1); 
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
buff.push_back(8,2,3); // overloaded push_back for using fold expressions
std::cout << buff.get_elem() << '\n';
std::cout << buff << '\n';
}// !main
*
* 
*/

/* TEST #3
* Что нового: Добавлен класс BufferIterator реализующий возможность использования его в range-based for loop
* Минусы не совсестим с функциями стандартной библиотеки такими как std::find, std::sort и подобные
* 
int main() // main
{
CircularBuffer<int, 5> buff;
buff.isEmpty();
buff.push_back(1);
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
buff.push_back(8, 2, 3);
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff.get_elem() << '\n';
std::cout << buff << '\n';

std::cout << (char)'\n\n';
for (const auto& x : buff) {
	std::cout << x << ' ';
}

std::cout << "\n\n";
for (CircularBuffer<int, 5>::Iterator it = buff.begin(); it != buff.end(); it++) {
	std::cout << *it << " ";
}
	 
}// !main
*/
 
int main() {
	CircularBuffer<int, 5> buff;
	buff.isEmpty();
	buff.push_back(1);
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	buff.push_back(8, 2, 3);
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff.get_elem() << '\n';
	std::cout << buff << '\n';

	std::cout << (char)'\n\n';
	for (const auto& x : buff) {
		std::cout << x << ' ';
	}

	std::cout << "\n\n";
	for (CircularBuffer<int, 5>::Iterator it = buff.begin(); it != buff.end(); it++) {
		std::cout << *it << " ";
	}
	
	return 0;
}