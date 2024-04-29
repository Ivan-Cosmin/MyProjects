#pragma once

#include <QDialog>
#include <concepts>

#include "Button.h"

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

class Dialog : public QDialog
{
public:
	Dialog(QWidget* parent = nullptr);

	template<typename T> requires arithmetic<T>
	std::string LoadDialog(T field)
	{
		return std::to_string(field);
	}

	template<typename T>
	std::string LoadDialog(T field)
	{
		return std::string(field);
	}

	template <typename T, typename...Ts>
	std::string LoadDialog(T field, Ts...fields)
	{
		 return field + std::string("\n") + LoadDialog(fields...);
	}

	bool ExecuteDialog(std::string result, bool buttons);

private:
	QGridLayout* m_layout;
	QLabel* m_label;

};