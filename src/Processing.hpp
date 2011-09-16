#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <QImage>
#include <QVector>

namespace Processing {
    typedef QVector <QVector <qreal> > Filter;

    QImage linearContrastCorrection(const QImage &img);
    QImage rgbContrastCorrection(const QImage &img);

    QImage applyFilter(const QImage &img, const Processing::Filter &kernel);
}

#endif  // PROCESSING_HPP
