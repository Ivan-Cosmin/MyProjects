#ifndef ARCH_H
#define ARCH_H

#include <memory>
#include "Node.h"

class Arch
{
public:
	Arch();
	Arch(std::shared_ptr<Node> fN, std::shared_ptr<Node> sN, uint32_t cost);
	Arch(std::shared_ptr<Node> fN, std::shared_ptr<Node> sN);
	Arch(int n1, int n2, int cost);

	NodePtr getFirstNodePtr() const;
	NodePtr getSecondNodePtr() const;
	uint32_t getCost() const;

	bool operator>(const Arch& other) const;
	bool operator<(const Arch& other) const;
	bool operator==(const Arch& other) const;

private:
	NodePtr m_first;
	NodePtr m_second;
	uint32_t m_cost;
};
#endif // ARCH_H
