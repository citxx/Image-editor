#include "ScaleDialog.hpp"

ScaleDialog::ScaleDialog(QWidget *parent): QDialog(parent) {
    this->ui.setupUi(this);

    this->connect(this->ui.pushButtonOk, SIGNAL(released()), this, SLOT(ok()));
    this->connect(this->ui.pushButtonCancel, SIGNAL(released()), this, SLOT(cancel()));
}

void ScaleDialog::ok() {
    this->factor = this->ui.doubleSpinBoxFactor->value();
    this->center = QPointF(
        this->ui.doubleSpinBoxX->value(),
        this->ui.doubleSpinBoxY->value()
    );

    this->accept();
}

void ScaleDialog::cancel() {
    this->reject();
}

qreal ScaleDialog::getFactor() {
    return this->factor;
}

QPointF ScaleDialog::getCenter() {
    return this->center;
}
