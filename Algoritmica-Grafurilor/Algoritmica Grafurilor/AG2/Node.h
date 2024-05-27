#pragma once
#include <QtWidgets/QMainWindow>
#include <cstdint>


class Node
{
public:
    
    Node(const QPoint&, const uint8_t&, const bool& verified = false, const bool& visited = false );
	Node(Node*); 
    Node();
	~Node();

    void setCoord(const QPoint& p);
    void setNode(Node* val);
    void setValue(const uint8_t& value);
    void setSelected(bool);
    void setVerified(bool verified);

    QPoint getCoord() const;
    int getX() const; 
    int getY() const;
    uint8_t getValue() const;
    bool getSelected() const;
    bool getVerified() const;

private:
    QPoint coordinates; 
    uint8_t m_value;
    bool m_selected;
    bool m_verified;
};

