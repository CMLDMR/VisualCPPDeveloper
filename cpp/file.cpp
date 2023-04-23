
#include "file.h"

namespace CPP {

File::File::File(const QString &fileName)
    :CPP::Member(Member::Type::File)
{
    this->insert(Key::fileName,fileName);
}

} // namespace CPP

