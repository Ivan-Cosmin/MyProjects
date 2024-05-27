#include "NumericDialogBox.h"

NumericDialogBox::NumericDialogBox(QWidget* parent) : QDialog(parent) {
	setupUi();

	connect(numericInput, &QLineEdit::returnPressed, this, &NumericDialogBox::onLineEditReturnPressed);

}

int NumericDialogBox::getEnteredValue() const {
	bool ok;  // This boolean indicates whether the conversion was successful
	int value = numericInput->text().toInt(&ok);

	if (ok) {
		return value;
	}
	else {
		// Handle the case where conversion failed (e.g., show an error message)
		return 0;  // You may choose a default value or handle it differently
	}
}

void NumericDialogBox::setupUi() {
	QVBoxLayout* layout = new QVBoxLayout(this);

	numericInput = new QLineEdit(this);
	QValidator* validator = new QIntValidator(this);
	numericInput->setValidator(validator);

	layout->addWidget(numericInput);

	setLayout(layout);
}

void NumericDialogBox::onLineEditReturnPressed() {
	// Trigger the acceptance of the dialog when Enter is pressed
	accept();
}