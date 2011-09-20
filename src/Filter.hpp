#ifndef FILTER_HPP
#define FILTER_HPP

#include <QVector>

class Filter {
    QVector <QVector <qreal> > kernel;

  public:
    Filter(int width, int height);
    Filter(const Filter &filter);

    const qreal & at(int x, int y) const;
    qreal & at(int x, int y);

    int width() const;
    int height() const;

    Filter normalized() const;
    Filter transposed() const;
};

#endif  // FILTER_HPP
