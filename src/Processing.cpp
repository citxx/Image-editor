#include "Processing.hpp"
#include <QtGlobal>
#include <QDebug>

qreal brightness(QRgb color) {
    return 0.2125 * qRed(color) + 0.7154 * qGreen(color) + 0.0721 * qBlue(color);
}

int expand(qreal minX, qreal maxX, int x) {
    int result = (x - minX) * 256.0 / (maxX + 1 - minX);
    if (result < 0 || 255 < result) {
        qDebug() << "expand(" << minX << ", " << maxX << ", " << x <<
                           "): invalid return value (" << result << ")";
    }
    return result;
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
    int minR, maxR;
    int minG, maxG;
    int minB, maxB;
    QRgb initColor = img.pixel(0,0);
    minR = maxR = qRed(initColor);
    minG = maxG = qGreen(initColor);
    minB = maxB = qBlue(initColor);
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);

            minR = qMin(minR, qRed(color));
            maxR = qMax(maxR, qRed(color));
            minG = qMin(minG, qGreen(color));
            maxG = qMax(maxG, qGreen(color));
            minB = qMin(minB, qBlue(color));
            maxB = qMax(maxB, qBlue(color));
        }
    }

    qDebug() << "RGB contrast correction: minR(" << minR <<") maxR(" << maxR << ")";
    qDebug() << "RGB contrast correction: minG(" << minG <<") maxG(" << maxG << ")";
    qDebug() << "RGB contrast correction: minB(" << minB <<") maxB(" << maxB << ")";

    QImage answer(img.width(), img.height(), img.format());
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            int r = expand(minR, maxR, qRed(color));
            int g = expand(minG, maxG, qGreen(color));
            int b = expand(minB, maxB, qBlue(color));
            answer.setPixel(x, y, qRgb(r, g, b));
        }
    }

    return answer;
}

QImage Processing::applyFilter(const QImage &img, const Processing::Filter &kernel) {
    // TODO: implement
}
