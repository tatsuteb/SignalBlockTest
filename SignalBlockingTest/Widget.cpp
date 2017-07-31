#include "Widget.h"
#include "ui_Widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	connect(ui->spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [&](int value)
	{
		ui->textEdit->setText(QString("%1Value Changed : %2\n").arg(ui->textEdit->toPlainText()).arg(value));
	});
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_pushButton_increment_clicked()
{
	// blockerが破棄されるときに、ui->spinBoxのシグナルブロックの状態を元に戻す
	const QSignalBlocker blocker(ui->spinBox);

	ui->spinBox->stepUp();
}

void Widget::on_pushButton_decrement_clicked()
{
	//　QObject の blockSignals は、設定する前のシグナルノブロック状態を返す
	const bool wasBlocked = ui->spinBox->blockSignals(true);

	ui->spinBox->stepDown();

	ui->spinBox->blockSignals(wasBlocked);
}
