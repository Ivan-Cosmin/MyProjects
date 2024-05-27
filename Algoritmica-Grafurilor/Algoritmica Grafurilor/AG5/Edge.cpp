#include "Edge.h"

Arch::Arch()
{}

Arch::Arch(std::shared_ptr<Node> fN, std::shared_ptr<Node> sN, uint32_t cost)
{
	m_first = fN;
	m_second = sN;
	m_cost = cost;
}

Arch::Arch(int n1, int n2, int cost)
{
	m_first = std::make_shared<Node>(n1);
	m_second = std::make_shared<Node>(n2);
	m_cost = cost;
}
Arch::Arch(std::shared_ptr<Node> fN, std::shared_ptr<Node> sN)
{
	m_first = fN;
	m_second = sN;
}

bool Arch::operator>(const Arch& other) const {
	return m_cost > other.m_cost;
}

bool Arch::operator==(const Arch& other) const
{
	return m_cost == other.m_cost;
}

bool Arch::operator<(const Arch& other) const
{
	return m_cost < other.m_cost;
}


std::shared_ptr<Node> Arch::getFirstNodePtr() const
{
	return m_first;
}

std::shared_ptr<Node> Arch::getSecondNodePtr() const
{
	return m_second;
}

uint32_t Arch::getCost() const
{
	return m_cost;
}
