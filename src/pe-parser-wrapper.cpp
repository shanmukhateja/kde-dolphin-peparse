#include <pe-parse/parse.h>

#include "pe-parser-wrapper.h"

#include <QString>
#include <QDebug>
#include <qlogging.h>

using namespace std;

PEParserWrapper::PEParserWrapper()
{
}


PEParserWrapper::~PEParserWrapper()
{
}

int resource_callback(void *cbd, const peparse::resource &resource)
{
    if (resource.type == peparse::RT_VERSION) {

        // PE offset
        uint8_t pe_offset = 32;

        // This offset allows us to skip to the required VS_FIXEDFILEINFO data
        // which can now be casted to struct.
        uint8_t my_offset = 8;

        auto verInfo = (const PEParserWrapper::VS_FIXEDFILEINFO *) (resource.buf->buf + pe_offset + my_offset);

        // Additional check to make sure we're on the right track.
        if (verInfo->dwSignature == 0xfeef04bd)
        {
            char value[MAX_MSG] = {0};

            sprintf(value, "%u.%u.%u.%u",
                    (uint32_t)(verInfo->dwFileVersionMS & 0xffff0000) >> 16,
                    (uint32_t)verInfo->dwFileVersionMS & 0x0000ffff,
                    (uint32_t)(verInfo->dwFileVersionLS & 0xffff0000) >> 16,
                    (uint32_t)verInfo->dwFileVersionLS & 0x0000ffff);

            // This is used to pass the data back to calling function
            vector<char>& vecPointer = *(vector<char> *)cbd;

            // This is used to store contents of `value`
            vector<char> v2 = {};

            // We insert at the end so that it will return
            // in correct (expected) order when the data is passed back
            for(char c: value)
            {
                // FIXME: Need to ensure only valid ASCII characters are inserted here.
                //        Right now, we are allowing `\x00' chars.
                v2.insert(v2.end(), c);
            }

            // Update reference here so vecPointer points to v2;
            vecPointer = v2;

            return 1;
        }
    }

    return 0;
}


string PEParserWrapper::parseFile(QString filePath)
{
    // The factory function does not throw exceptions!
    ParsedPeRef ref(peparse::ParsePEFromFile(filePath.toUtf8().data()),
                    peparse::DestructParsedPE);
    if (!ref) {
        qWarning() << "Failed to parse file " << filePath;
        return "";
    }

    vector<char> result;

    peparse::IterRsrc(ref.get(), resource_callback, &result);

    if (result.size() == 0)
    {
        return "";
    }

    return string(result.begin(), result.end());
}
