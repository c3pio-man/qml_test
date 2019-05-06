#include "pbtranslator.h"
#include "inkview.h"

using namespace pocketbook::utils;

PBTranslator::PBTranslator()
{

}

QString PBTranslator::translate(const char *context, const char *sourceText,
                          const char *disambiguation, int n) const
{
    Q_UNUSED(context);
    Q_UNUSED(disambiguation);
    //Q_UNUSED(n);

    const char *plural = (n == -1) ? NULL : GetLangTextPlural(sourceText, n);
    return plural == NULL ? QString::fromUtf8(GetLangText(sourceText)) : QString::fromUtf8(plural);
}
