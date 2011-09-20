#ifndef FILTER_HPP
#define FILTER_HPP

#include <QVector>

class Filter {
    QVector <QVector <qreal> > body;

  public:
    Filter(int width, int height);

    const qreal & at(int x, int y) const;
    qreal & at(int x, int y);

    int width() const;
    int height() const;
};

#endif  // FILTER_HPP
