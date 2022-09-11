#ifndef DATA_STRUCTURE_CIRCULAR_BUFFER2_HPP
#define DATA_STRUCTURE_CIRCULAR_BUFFER2_HPP
#include <iostream>
#include <cassert>
#include <string>
#include <exception>
#define BUFFER_FAILURE -1
#define BUFFER_SUCCESS  1

class BufferException : public std::exception {
private:
	const char* function_;
	const char* error_;
public:
	BufferException(const char* str, const char* function_name) throw() : error_(str), function_(function_name) {  }
	const char* what() const throw() override { return error_; }
	const char* get_func() const { return function_; }
 
};

class CircularBuffer2 {
private:
	size_t m_tail;
	size_t m_head;
	bool m_bIsEmpty;
private:
	size_t m_size;
	int* m_data;

public:
	explicit CircularBuffer2(size_t size);
		 
	~CircularBuffer2();

private:
	int operator[](const std::size_t index) const { if (index >= m_size) throw BufferException("Error: Out of range", "operator[]"); return m_data[index]; }
public:
	friend std::ostream& operator<<(std::ostream& ostr, const CircularBuffer2& buff) {
		for (size_t i  = 0; i < buff.size(); i++) {
			ostr << buff[i] << ' ';
		}
		return ostr;
	}
public:

	/* Element access **/

	/*
	* @brief reads data
	* @return element otherwise -1
	*/
	int read();

	/* !Element access **/

	/** Modifiers */

/**
* @brief inserts element at the top
* @param[in] data to be pushed;
* @return 1 on success and -1 on failure;
*/
	int push(int data);
/**
* @brief removes the front element;
* @return 1 on success and -1 on failure;
*/
	int pop();

	/** !Modifiers */

/*
* @brief Resets tail & head;
*/
	void reset();

	/** Capacity */

/*
* @return returns the number of elements;
*/
	int size() const { return m_size; }
/*
* @brief checks whether the container is empty;
*/
	bool empty() const { return m_bIsEmpty; }

	/** !Capacity */
};

#endif // !DATA_STRUCTURE_CIRCULAR_BUFFER2_HPP
