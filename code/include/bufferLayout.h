/** \file bufferLayout.h */
#pragma once

#include "shaderDataType.h"
#include <vector>


/**
\class VertexBufferElement
A class which holds data about a single element in a vertex buffer layout
*/
class VertexBufferElement
{
public:
	ShaderDataType m_dataType;
	uint32_t m_size;
	uint32_t m_offset;
	bool m_normalised;
	uint32_t m_instanceDivisor;

	VertexBufferElement() {} //!< Default constructor
	VertexBufferElement(ShaderDataType dataType, uint32_t instanceDivisor = 0, bool normalised = false) :
		m_dataType(dataType),
		m_size(SDT::size(dataType)),
		m_offset(0),
		m_instanceDivisor(instanceDivisor),
		m_normalised(normalised)
	{} //!< Constructor with params
};

/**
\class UniformBufferElement
A class which holds data about a single element in a uniform buffer layout
*/
class UniformBufferElement
{
public:
	const char* m_name;
	ShaderDataType m_dataType;
	uint32_t m_size;
	uint32_t m_offset;

	UniformBufferElement() {} //!< Default constructor
	UniformBufferElement(const char* name, ShaderDataType dataType) :
		m_name(name),
		m_dataType(dataType),
		m_size(SDT::STD140Alignment(dataType)),
		m_offset(0)
	{} //!< Constructor with params
};

/** \class BufferLayout
* Abstraction of the notion of a buffer layout
*/
template <class G>
class BufferLayout
{
public:
	BufferLayout<G>() {};
	BufferLayout<G>(const std::initializer_list<G>& element, uint32_t stride = 0) : m_elements(element), m_stride(stride) { calcStrideAndOffset(); }
	inline uint32_t getStride() const { return m_stride; }
	void addElement(G element);
	inline typename std::vector<G>::iterator begin() { return m_elements.begin(); }
	inline typename std::vector<G>::iterator end() { return m_elements.end(); }
	inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); }
	inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); }
private:
	std::vector<G> m_elements; //!< Buffer elements
	uint32_t m_stride; //!< Width is bytes of the a buffer line
	void calcStrideAndOffset(); //!< Calculate stride and offsets based on elements
};

template <class G>
void BufferLayout<G>::addElement(G element)
{
	m_elements.push_back(element);
	calcStrideAndOffset();
}

template <class G>
void BufferLayout<G>::calcStrideAndOffset()
{
	uint32_t l_offset = 0;

	for (auto& element : m_elements)
	{
		element.m_offset = l_offset;
		l_offset += element.m_size;
	}

	if (m_stride == 0) m_stride = l_offset;
}

using VertexBufferLayout = BufferLayout<VertexBufferElement>;
using UniformBufferLayout = BufferLayout<UniformBufferElement>;

