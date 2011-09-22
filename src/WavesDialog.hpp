#ifndef WAVES_DIALOG_HPP
#define WAVES_DIALOG_HPP

#include <QDialog>
#include <QPointF>

#include "ui_WavesDialog.h"

class WavesDialog: public QDialog {
    Q_OBJECT

    Ui::WavesDialog ui;

    QPointF amplitude;
    qreal length;

  private slots:
    void ok();
    void cancel();

  public:
    WavesDialog(QWidget *parent = NULL);

    QPointF getAmplitude();
    qreal getLength();
};

#endif  // WAVES_DIALOG_HPP
