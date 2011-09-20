#include "Filter.hpp"

#include <QtCore/qmath.h>

Filter::Filter():
    kernel(0) {
}

Filter::Filter(int width, int height):
    kernel(width, QVector <qreal>(height, 0.0)) {
}

Filter::Filter(const Filter &filter):
    kernel(filter.kernel) {
}

const qreal & Filter::at(int x, int y) const {
    return this->kernel[x][y];
}

qreal & Filter::at(int x, int y) {
    return this->kernel[x][y];
}

int Filter::width() const {
    return this->kernel.size();
}

int Filter::height() const {
    return this->kernel[0].size();
}

Filter Filter::normalized() const {
    qreal sum = 0.0;
    for (int x = 0; x < this->width(); x++) {
        for (int y = 0; y < this->height(); y++) {
            sum += this->at(x, y);
        }
    }

    if (qAbs(sum) < 1e-5) {
        return *this;
    }
    else {
        Filter normalizedFilter(this->width(), this->height());
        for (int x = 0; x < this->width(); x++) {
            for (int y = 0; y < this->height(); y++) {
                normalizedFilter.at(x, y) = this->at(x, y) / sum;
            }
        }

        return normalizedFilter;
    }
}

Filter Filter::transposed() const {
    Filter transposedFilter(this->height(), this->width());
    for (int x = 0; x < this->width(); x++) {
        for (int y = 0; y < this->height(); y++) {
            transposedFilter.at(y, x) = this->at(x, y);
        }
    }

    return transposedFilter;

}

Filter & Filter::operator =(const Filter &filter) {
    this->kernel = filter.kernel;
    return *this;
}
