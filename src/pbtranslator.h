#ifndef PBTRANSLATOR_H
#define PBTRANSLATOR_H

#include <qtranslator.h>

namespace pocketbook { namespace utils {

class PBTranslator: public QTranslator
{
public:
    PBTranslator();

    QString translate(const char *context, const char *sourceText,
                              const char *disambiguation = 0, int n = -1) const override;
};

}} // namespace

#endif // PBTRANSLATOR_H
