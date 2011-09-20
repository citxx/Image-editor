#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <QImage>
#include <QVector>

namespace Processing {
    typedef QVector <QVector <qreal> > Filter;

    Processing::Filter normalized(Processing::Filter filter);
    Processing::Filter transposed(Processing::Filter filter);

    QImage linearContrastCorrection(const QImage &img);
    QImage rgbContrastCorrection(const QImage &img);

    QImage applyFilter(const QImage &img, const Processing::Filter &kernel);
    QImage gaussianBlur(qreal sigma);
}

#endif  // PROCESSING_HPP
