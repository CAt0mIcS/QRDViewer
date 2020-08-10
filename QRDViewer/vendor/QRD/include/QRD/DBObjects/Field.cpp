#include "../pch.h"
#include "Field.h"


namespace QRD
{
    Field::Field(const std::string& fieldName, const DbTypes& dbType, const unsigned short fieldId)
        : m_FieldName(fieldName), m_FieldType(dbType), m_Id(fieldId)
    {
    }
}

