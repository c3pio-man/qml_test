#ifndef RESOURCEIMAGEPROVIDER_H
#define RESOURCEIMAGEPROVIDER_H

#include "QtQuick/QQuickImageProvider"

namespace pocketbook { namespace utils {

class IImageProvider {
public:
    virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) = 0;
};

class ResourceImageProvider:public QQuickImageProvider
{
public:
    ResourceImageProvider(bool invert = false);
    ResourceImageProvider(IImageProvider *provider);
    QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) override;

private:
    IImageProvider *provider_ = nullptr;
    ushort xor_value_ = 0;
};

}} // namespace

#endif // RESOURCEIMAGEPROVIDER_H
