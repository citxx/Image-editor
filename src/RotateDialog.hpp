#ifndef ROTATE_DIALOG_HPP
#define ROTATE_DIALOG_HPP

#include <QDialog>
#include <QPointF>

#include "ui_RotateDialog.h"

class RotateDialog: public QDialog {
    Q_OBJECT

    Ui::RotateDialog ui;

    qreal angle;
    QPointF center;

  private slots:
    void ok();
    void cancel();

  public:
    RotateDialog(QWidget *parent = NULL);

    qreal getAngle();
    QPointF getCenter();
};

#endif  // ROTATE_DIALOG_HPP
