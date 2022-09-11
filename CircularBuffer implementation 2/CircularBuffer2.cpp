#include "CircularBuffer2.hpp"

CircularBuffer2::CircularBuffer2(size_t size) : m_size(size), m_head(NULL), m_tail(NULL)
{
	m_data = new int[size];
	if (m_size <= NULL) {
		throw  BufferException("Error: size must be more 0", "Function: CircularBuffer(size_t size)");
	}
}

CircularBuffer2::~CircularBuffer2()
{
	delete[] m_data;
}

int CircularBuffer2::read()
{
	int res_ = 0;
	if (m_tail < m_size)
		res_ = m_data[m_tail++ % m_size];

	if (m_tail == m_head)
		m_bIsEmpty = 1;
	
	return res_ ? res_ : BUFFER_FAILURE;
}

void CircularBuffer2::reset()
{
	m_tail = 0;
	m_head = 0;
	m_bIsEmpty = 1;
}

int CircularBuffer2::push(int data)
{
	m_data[m_head++] = data;
	if (m_head >= m_size) {
		m_head = NULL;
	}
	if (m_head == m_tail)
		m_bIsEmpty = 1;
	return BUFFER_SUCCESS;
}

int CircularBuffer2::pop()
{
 
	return BUFFER_SUCCESS;
}
