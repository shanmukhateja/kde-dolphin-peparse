#pragma once

#include <pe-parse/parse.h>
#include <pe-parse/nt-headers.h>

#include <memory>

#include <QString>

#define MAX_MSG 81

using namespace std;

using ParsedPeRef =
unique_ptr<peparse::parsed_pe, void (*)(peparse::parsed_pe *)>;

class PEParserWrapper {

public:
  struct VS_FIXEDFILEINFO {
    uint32_t dwSignature;
    uint32_t dwStrucVersion;
    uint32_t dwFileVersionMS;
    uint32_t dwFileVersionLS;
    uint32_t dwProductVersionMS;
    uint32_t dwProductVersionLS;
    uint32_t dwFileFlagsMask;
    uint32_t dwFileFlags;
    uint32_t dwFileOS;
    uint32_t dwFileType;
    uint32_t dwFileSubtype;
    uint32_t dwFileDateMS;
    uint32_t dwFileDateLS;
  };

  PEParserWrapper();
  virtual ~PEParserWrapper();
  string parseFile(QString filePath);
};

