#include "UnsharpDialog.hpp"

UnsharpDialog::UnsharpDialog(QWidget *parent): QDialog(parent) {
    this->ui.setupUi(this);

    this->connect(this->ui.pushButtonOk, SIGNAL(released()), this, SLOT(ok()));
    this->connect(this->ui.pushButtonCancel, SIGNAL(released()), this, SLOT(cancel()));
}

void UnsharpDialog::ok() {
    this->sigma = this->ui.doubleSpinBoxSigma->value();
    this->alpha = this->ui.doubleSpinBoxAlpha->value();

    this->accept();
}

void UnsharpDialog::cancel() {
    this->reject();
}

qreal UnsharpDialog::getSigma() {
    return this->sigma;
}

qreal UnsharpDialog::getAlpha() {
    return this->alpha;
}
