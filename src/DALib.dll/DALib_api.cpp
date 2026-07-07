// DALib.dll -- the DALib:: namespace API (data-file system lifecycle).
#include "DALib.h"

extern "C" char __delink_ida_data_start[];

namespace DALib {

IFileSystem* Data;   // ?Data@DALib@@3PAUIFileSystem@@A

// CloseData: release the mounted data file-system and clear the global.
void CloseData() {
    if (Data) {
        *(long*)(__delink_ida_data_start + 0xbc) = Data->Release();
        Data = 0;
    }
}

}  // namespace DALib
