#include "RotateDialog.hpp"

RotateDialog::RotateDialog(QWidget *parent): QDialog(parent) {
    this->ui.setupUi(this);

    this->connect(this->ui.pushButtonOk, SIGNAL(released()), this, SLOT(ok()));
    this->connect(this->ui.pushButtonCancel, SIGNAL(released()), this, SLOT(cancel()));
}

void RotateDialog::ok() {
    this->angle = this->ui.doubleSpinBoxAngle->value();
    this->center = QPointF(
        this->ui.doubleSpinBoxX->value(),
        this->ui.doubleSpinBoxY->value()
    );

    this->accept();
}

void RotateDialog::cancel() {
    this->reject();
}

qreal RotateDialog::getAngle() {
    return this->angle;
}

QPointF RotateDialog::getCenter() {
    return this->center;
}
