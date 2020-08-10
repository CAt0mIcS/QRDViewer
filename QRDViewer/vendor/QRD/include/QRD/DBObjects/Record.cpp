#include "../pch.h"
#include "Record.h"


namespace QRD
{
    bool Record::operator==(const Record& other) const
    {
        return m_Data == other.GetRecordData();
    }

    void Record::DeleteData(unsigned short fieldId)
    {
        m_Data.erase(m_Data.begin() + fieldId);
    }
}

