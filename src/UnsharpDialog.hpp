#ifndef UNSHARP_DIALOG_HPP
#define UNSHARP_DIALOG_HPP

#include <QDialog>
#include <QPointF>

#include "ui_UnsharpDialog.h"

class UnsharpDialog: public QDialog {
    Q_OBJECT

    Ui::UnsharpDialog ui;

    qreal sigma;
    qreal alpha;

  private slots:
    void ok();
    void cancel();

  public:
    UnsharpDialog(QWidget *parent = NULL);

    qreal getSigma();
    qreal getAlpha();
};

#endif  // UNSHARP_DIALOG_HPP
