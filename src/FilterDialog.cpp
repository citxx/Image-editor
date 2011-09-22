#include "FilterDialog.hpp"

FilterDialog::FilterDialog(QWidget *parent): QDialog(parent) {
    this->ui.setupUi(this);

    this->resize(3, 3);

    this->connect(this->ui.spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(resizeWidth(int)));
    this->connect(this->ui.spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(resizeHeight(int)));
    this->connect(this->ui.pushButtonApply, SIGNAL(released()), this, SLOT(apply()));
    this->connect(this->ui.pushButtonApplyNormalized, SIGNAL(released()), this, SLOT(applyNormalized()));
    this->connect(this->ui.pushButtonCancel, SIGNAL(released()), this, SLOT(cancel()));
}

void FilterDialog::resize(int width, int height) {
    for (int i = 0; i < this->inputMatrix.size(); i++) {
        for (int j = 0; j < this->inputMatrix[i].size(); j++) {
            if (i >= width || j >= height) {
                delete this->inputMatrix[i][j];
                delete this->normalizedMatrix[i][j];
            }
        }
    }

    this->inputMatrix.resize(width);
    this->normalizedMatrix.resize(width);

    for (int i = 0; i < width; i++) {
        this->inputMatrix[i].resize(height);
        this->normalizedMatrix[i].resize(height);
    }

    for (int i = 0; i < this->inputMatrix.size(); i++) {
        for (int j = 0; j < this->inputMatrix[i].size(); j++) {
            if (this->inputMatrix[i][j] == NULL) {
                this->inputMatrix[i][j] = new QDoubleSpinBox(this);
                this->inputMatrix[i][j]->setMinimum(-100.0);
                this->inputMatrix[i][j]->setMaximum(100.0);
                this->inputMatrix[i][j]->setValue(0.0);
                this->inputMatrix[i][j]->setSingleStep(1.0);
                this->ui.layoutInputMatrix->addWidget(this->inputMatrix[i][j], j, i);
                this->connect(this->inputMatrix[i][j], SIGNAL(valueChanged(double)), this, SLOT(normalize()));


                this->normalizedMatrix[i][j] = new QLabel(this);
                this->ui.layoutNormalizedMatrix->addWidget(this->normalizedMatrix[i][j], j, i);
            }
        }
    }

    this->normalize();
}

void FilterDialog::normalize() {
    qreal sum = 0.0;
    for (int i = 0; i < this->inputMatrix.size(); i++) {
        for (int j = 0; j < this->inputMatrix[i].size(); j++) {
            sum += inputMatrix[i][j]->value();
        }
    }

    for (int i = 0; i < this->inputMatrix.size(); i++) {
        for (int j = 0; j < this->inputMatrix[i].size(); j++) {
            if (qAbs(sum) < 1e-5) {
                normalizedMatrix[i][j]->setNum(0.0);
            }
            else {
                normalizedMatrix[i][j]->setNum(inputMatrix[i][j]->value() / sum);
            }
        }
    }
}

void FilterDialog::resizeWidth(int width) {
    this->resize(width, this->ui.spinBoxHeight->value());
}

void FilterDialog::resizeHeight(int height) {
    this->resize(this->ui.spinBoxWidth->value(), height);
}

void FilterDialog::apply() {
    this->result = Filter(this->inputMatrix[0].size(), this->inputMatrix.size());

    for (int x = 0; x < this->result.width(); x++) {
        for (int y = 0; y < this->result.height(); y++) {
            this->result.at(x, y) = this->inputMatrix[x][y]->value();
        }
    }

    this->done(QDialog::Accepted);
}

void FilterDialog::applyNormalized() {
    this->result = Filter(this->inputMatrix[0].size(), this->inputMatrix.size());

    for (int x = 0; x < this->result.width(); x++) {
        for (int y = 0; y < this->result.height(); y++) {
            this->result.at(x, y) = this->inputMatrix[x][y]->value();
        }
    }

    this->result = this->result.normalized();

    this->accept();
}

void FilterDialog::cancel() {
    this->reject();
}

Filter FilterDialog::getFilter() {
    return this->result;
}
