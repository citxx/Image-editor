#ifndef SCALE_DIALOG_HPP
#define SCALE_DIALOG_HPP

#include <QDialog>
#include <QPointF>

#include "ui_ScaleDialog.h"

class ScaleDialog: public QDialog {
    Q_OBJECT

    Ui::ScaleDialog ui;

    qreal factor;
    QPointF center;

  private slots:
    void ok();
    void cancel();

  public:
    ScaleDialog(QWidget *parent = NULL);

    qreal getFactor();
    QPointF getCenter();
};

#endif  // SCALE_DIALOG_HPP
