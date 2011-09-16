#ifndef FILTER_DIALOG_HPP
#define FILTER_DIALOG_HPP

#include <QWidget>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include "ui_FilterDialog.h"
#include "Processing.hpp"

class FilterDialog: public QDialog {
    Q_OBJECT

    Ui::FilterDialog ui;

    QVector <QVector <QDoubleSpinBox *> > inputMatrix;
    QVector <QVector <QLabel *> > normalizedMatrix;

    Processing::Filter result;

    void resize(int width, int height);

  public slots:
    void resizeWidth(int width);
    void resizeHeight(int height);
    void normalize();

    void apply();
    void applyNormalized();
    void cancel();

  public:
    FilterDialog(QWidget *parent = NULL);

    Processing::Filter getFilter();
};

#endif  // FILTER_DIALOG_HPP
