#ifndef DATA_STRUCTURE_CIRCULAR_BUFFER_HPP
#define DATA_STRUCTURE_CIRCULAR_BUFFER_HPP
#include <iostream>
#include <cassert>
template <typename CircularBuffer>
class BufferIterator {
public:
	using ValueType = typename CircularBuffer::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	BufferIterator(PointerType ptr) : m_ptr(ptr) { }
	~BufferIterator() = default;

public:/**Operator overloading*/

	BufferIterator& operator++() {
		m_ptr++;
		return *this;
	}
	BufferIterator operator++(int) {
		BufferIterator it = *this;
		++(*this);
		return it;
	}

	BufferIterator& operator--() {
		m_ptr--;
		return *this;
	}

	BufferIterator operator--(int) {
		BufferIterator it = *this;
		--(*this);
		return it;
	}

	BufferIterator operator[](int index) {
		return *(m_ptr + index);
	}

	ReferenceType operator*() {
		return *m_ptr;
	}

	PointerType operator->() {
		return m_ptr;
	}

	bool operator==(const BufferIterator& other) const {
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const BufferIterator& other) const {
		return m_ptr != other.m_ptr;
	}

private:
	PointerType m_ptr;
};

template <typename _Type, size_t _Size>
class CircularBuffer
{
public:
	using ValueType = _Type;
	using Iterator = BufferIterator<CircularBuffer<_Type, _Size>>;
private:
	int m_WriteIndex = 0;
	int m_ReadIndex = 0;

	bool m_IsFull = false;
	bool m_IsEmpty = false;
private:
	size_t m_size;
	std::unique_ptr<_Type[]> m_data;
public:	/**  Operators overloading; */
	friend std::ostream& operator<<(std::ostream& ostr, const CircularBuffer<_Type, _Size>& data) {
		for (size_t read_index = 0; read_index < data.size(); read_index++) {
			ostr << data.get_elem(read_index) << ' ';
		}
		return ostr;
	}
private:/** Delete copy constructor, move constructor , copy assignment operator */
	CircularBuffer(const CircularBuffer&) = delete;
	CircularBuffer(CircularBuffer&&) = delete;
	CircularBuffer& operator=(const CircularBuffer&) = delete;
	CircularBuffer& operator=(CircularBuffer&&) = delete;
public:
	CircularBuffer();

	~CircularBuffer() = default;
	/**
	* @brief Inserts element in back of the array;
	* @param data[in] - is data to be pushed in the array;
	* @return 1 on success and negative error code on failure;
	*/
	int push_back(_Type data);

	/**
	* @brief Inserts element in back of the array;
	* @tparam args[in] - is values to be pushed in back of the array;
	* @return  1 on success and negative error code on failure;
	*/
	template<typename ... Args >
	int push_back(Args&& ... args);

	/**
	* @return Size of container
	*/
	constexpr size_t size() const noexcept { return m_size; }

	/**
	* @brief Is used for reading elements in the array;
	* @return If successful, it returns a value in the array, depending on what type of data you specified when instantiating the template, otherwise a negative error code;
	*/
	[[nodiscard]] _Type get_elem();
	/**
	* @brief Resets read & write indexies and states ( isEmpty & isFull );
	*/
	void reset() noexcept;
	/**
	* @return Current state of variable m_IsFull;
	*/
	bool isFull() const { return (m_WriteIndex >= _Size); }
	/**
	* @brief Circular buffer isEmpty when every data was read;
	* @return Current state of bool var (m_IsEmpty);
	*/
	bool isEmpty() const;
private:
	/**
	* @brief Is used for reading elements in the array;
	* @return On success returns element in the array at index;
	*/
	[[nodiscard]] _Type get_elem(const size_t index) const;

public:/** @brief Iterator Methods  */

	Iterator begin() {
		return Iterator(m_data.get());
	}

	Iterator end() {
		return Iterator(m_data.get() + m_size);
	}

	Iterator begin() const {
		return Iterator(m_data.get());
	}

	Iterator end() const {
		return Iterator(m_data.get() + m_size);
	}

};

#endif // !DATA_STRUCTURE_CIRCULAR_BUFFER_HPP

template<typename _Type, size_t _Size>
inline CircularBuffer<_Type, _Size>::CircularBuffer() : m_size(_Size), m_WriteIndex(NULL), m_ReadIndex(NULL)
{
	static_assert(_Size > 0 && "Size must be more 0");
	m_data = std::make_unique<_Type[]>(_Size);
}

template<typename _Type, size_t _Size>
inline int CircularBuffer<_Type, _Size>::push_back(_Type data)
{
	if (isEmpty() && m_WriteIndex >= m_size) {
		reset();
	}

	if (isFull()) {
		return -1;
	}
	if (m_WriteIndex >= m_size) {
		m_WriteIndex = 0;
	}
	m_data.get()[m_WriteIndex++ % m_size] = data;

	if (m_WriteIndex == m_ReadIndex) {
		m_IsFull = true;
	}
	else {
		m_IsFull = false;
	}
	return 1;
}

template<typename _Type, size_t _Size>
template <typename ... Args>
int CircularBuffer<_Type, _Size>::push_back(Args&& ... args) {

	if (isEmpty() && m_WriteIndex >= m_size) {
		reset();
	}

	if (isFull()) {
		return -1;
	}
	if (m_WriteIndex >= m_size) {
		m_WriteIndex = 0;
	}

	(void(m_data[m_WriteIndex++ % m_size] = args), ...);

	if (m_WriteIndex == m_ReadIndex) {
		m_IsFull = true;
	}
	else {
		m_IsFull = false;
	}
	return 1;
}

template<typename _Type, size_t _Size>
inline _Type CircularBuffer<_Type, _Size>::get_elem(const size_t index) const {
	if (index >= m_size) {
		throw std::out_of_range("Invalid index");
	}
	return m_data.get()[index];
}

template<typename _Type, size_t _Size>
inline _Type CircularBuffer<_Type, _Size>::get_elem() {
	_Type res_value = {};
	if (isEmpty() || (m_ReadIndex >= _Size)) {
		return -1;
	}
	else {
		res_value = m_data.get()[m_ReadIndex++];
	}

	if (m_ReadIndex == m_WriteIndex) {
		m_IsEmpty = true;
	}
	else {
		m_IsEmpty = false;
	}

	return (res_value) ? res_value : -1;
}

template<typename _Type, size_t _Size>
inline void CircularBuffer<_Type, _Size>::reset() noexcept {
	m_ReadIndex = 0;
	m_WriteIndex = 0;
	m_IsEmpty = 1;
	m_IsFull = 0;
}

template<typename _Type, size_t _Size>
inline bool CircularBuffer<_Type, _Size>::isEmpty() const {

	return (m_ReadIndex == m_WriteIndex);
}