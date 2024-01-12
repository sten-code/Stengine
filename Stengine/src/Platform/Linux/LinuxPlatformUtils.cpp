#include "stpch.h"
#ifdef ST_PLATFORM_LINUX
#include "Stengine/Utils/PlatformUtils.h"

#include <osdialog.h>

namespace Sten
{
    std::string FileDialogs::OpenFile(const char* filter)
    {
      char* filename = osdialog_file(OSDIALOG_OPEN, NULL, NULL, NULL);
      return std::string(filename);
    }

    std::string FileDialogs::SaveFile(const char* filter)
    {
      char* filename = osdialog_file(OSDIALOG_SAVE, NULL, NULL, NULL);
      return std::string(filename);
    }
}

#endif
