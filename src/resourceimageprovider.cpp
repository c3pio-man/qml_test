#include "resourceimageprovider.h"

#include "inkview.h"
#include <QtDebug>

using namespace pocketbook::utils;

ResourceImageProvider::ResourceImageProvider(bool invert)
    :QQuickImageProvider(QQuickImageProvider::Image)
    ,xor_value_(invert ? 0xf : 0)
{
}

ResourceImageProvider::ResourceImageProvider(IImageProvider *provider)
    :QQuickImageProvider(QQuickImageProvider::Image)
    ,provider_(provider)
{
}

QImage ResourceImageProvider::requestImage(const QString &id, QSize *size, const QSize& requestedSize)
{
    if (provider_)
        return provider_->requestImage(id, size, requestedSize);
    Q_UNUSED(requestedSize);
    ibitmap *bmp = GetResource(id.toUtf8().constData(), NULL);
    if (!bmp) return QImage();
    if ((bmp->depth & 0xff) != 4) {
        qWarning() << "Invalid image depth for [" << id << "]";
        return QImage();
    }

    // TODO optimize me!
    // TODO resize me to requestedSize
    // TODO handle transparent bitmaps
    QImage result(bmp->width, bmp->height, bmp->depth & 0x8000 ? QImage::Format_ARGB4444_Premultiplied : QImage::Format_RGB444);

    size->setWidth(bmp->width);
    size->setHeight(bmp->height);

    if (!(bmp->depth & 0x8000)) {
        for (int y = 0; y < bmp->height; ++y) {
            uchar* dst = result.scanLine(y);
            uchar* src = bmp->data + bmp->scanline * y;
            for (int x = 0; x < bmp->width; ++x, dst +=2) {
                ushort v = (x & 1 ? (*src++) & 0x0f : (*src) >> 4) ^ xor_value_;
                *((ushort*)dst) = v << 8 | v << 4 | v;

            }
        }
    } else {
        int ml = (bmp->width + 7) >> 3;

        for (int y = 0; y < bmp->height; ++y) {
            uchar* dst = result.scanLine(y);
            uchar* src = bmp->data + bmp->scanline * y;
            uchar* mask =  bmp->data + bmp->height * bmp->scanline + ml * y;
            for (int x = 0; x < bmp->width; ++x, dst += 2) {
                ushort v = (x & 1 ? (*src++) & 0x0f : (*src) >> 4) ^ xor_value_;
                ushort alpha = (*(mask + (x >> 3)) >> (7 - (x & 0x7))) & 1 ? 0xf000 : 0x00;
                *((ushort*)dst) = v << 8 | v << 4 | v | alpha;
            }
        }
        uchar* dst = result.scanLine(0);
        *((ushort*)dst) = 0xff;
    }

    free(bmp);

    return result;
}
