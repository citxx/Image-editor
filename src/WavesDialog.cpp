#include "WavesDialog.hpp"

WavesDialog::WavesDialog(QWidget *parent): QDialog(parent) {
    this->ui.setupUi(this);

    this->connect(this->ui.pushButtonOk, SIGNAL(released()), this, SLOT(ok()));
    this->connect(this->ui.pushButtonCancel, SIGNAL(released()), this, SLOT(cancel()));
}

void WavesDialog::ok() {
    this->amplitude = QPointF(
        this->ui.doubleSpinBoxAmplitudeX->value(),
        this->ui.doubleSpinBoxAmplitudeY->value()
    );
    this->length = this->ui.doubleSpinBoxLength->value();

    this->accept();
}

void WavesDialog::cancel() {
    this->reject();
}

QPointF WavesDialog::getAmplitude() {
    return this->amplitude;
}

qreal WavesDialog::getLength() {
    return this->length;
}
