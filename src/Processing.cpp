#include "Processing.hpp"
#include <QtGlobal>
#include <QDebug>

qreal brightness(QRgb color) {
    return 0.2125 * qRed(color) + 0.7154 * qGreen(color) + 0.0721 * qBlue(color);
}

int expand(qreal minBrightness, qreal maxBrightness, int value) {
    return (int)((value - minBrightness) * 256.0 / (maxBrightness - minBrightness));
}

QImage Processing::linearContrastCorrection(const QImage &img) {
    qreal minBrightness, maxBrightness;
    minBrightness = maxBrightness = brightness(img.pixel(0,0));
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            qreal br = brightness(img.pixel(x, y));
            minBrightness = qMin(minBrightness, br);
            maxBrightness = qMax(maxBrightness, br);
        }
    }

    qDebug() << "Linear contrast correction: minBrightness(" << minBrightness <<
                ") maxBrightness(" << maxBrightness << ")";

    QImage answer(img.width(), img.height(), img.format());
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            int r = expand(minBrightness, maxBrightness, qRed(color));
            int g = expand(minBrightness, maxBrightness, qGreen(color));
            int b = expand(minBrightness, maxBrightness, qBlue(color));
            answer.setPixel(x, y, qRgb(r, g, b));
        }
    }

    return answer;
}

QImage Processing::rgbContrastCorrection(const QImage &img) {
    // TODO: implement
}

QImage Processing::applyFilter(const QImage &img, const Processing::Filter &kernel) {
    // TODO: implement
}
