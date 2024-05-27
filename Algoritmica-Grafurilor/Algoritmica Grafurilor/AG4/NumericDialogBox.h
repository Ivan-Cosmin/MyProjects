#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>

class NumericDialogBox : public QDialog {
	Q_OBJECT
public:
	NumericDialogBox(QWidget* parent = nullptr);

	int getEnteredValue() const;

private slots:
	void onLineEditReturnPressed();

private:
	void setupUi();

	QLineEdit* numericInput;
};
