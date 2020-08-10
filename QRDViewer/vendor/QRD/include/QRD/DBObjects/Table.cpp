#include "../pch.h"
#include "Table.h"


namespace QRD
{
    Table::Table(const std::string& tableName, const int id)
        : m_TableName(tableName), m_Records{}, m_Fields{}, m_Id(id)
    {
    }

    Field& Table::GetField(const std::string_view fieldName)
    {
        for (auto& field : m_Fields)
        {
            if (field.GetFieldName() == fieldName)
                return field;
        }
    }

    void Table::DeleteField(const Field& field)
    {
        unsigned int fieldId = field.GetFieldId();
        m_Fields.erase(m_Fields.begin() + fieldId);
        UpdateFieldIds(fieldId);

        for (auto& rec : m_Records)
        {
            rec.DeleteData(fieldId);
        }
    }

    void Table::DeleteField(const std::string& fieldName)
    {
        unsigned int fieldId;
        for(const auto& field : m_Fields)
        {
            if (field.GetFieldName() == fieldName)
            {
                fieldId = field.GetFieldId();
                m_Fields.erase(m_Fields.begin() + fieldId);
                break;
            }
        }
        UpdateFieldIds(fieldId);
    }

    Record& Table::GetRecordById(const unsigned int id)
    {
        if (id > m_Records.size())
            throw std::invalid_argument("Vector subscription out of range");

        return m_Records[id];
    }

    void Table::DeleteRecord(const Record& record)
    {
        unsigned int recId = record.GetRecordId();
        m_Records.erase(m_Records.begin() + recId);
        UpdateRecordIds(recId);
    }

    bool Table::operator==(const Table& other) const
    {
        if(m_Id == other.m_Id)
            return true;
        return false;
    }

    void Table::UpdateRecordIds(unsigned int indexOfDeletedElement)
    {
        for (unsigned int i = indexOfDeletedElement; i < m_Records.size(); ++i)
        {
            m_Records[i].SetRecordId(i);
        }
    }

    void Table::UpdateFieldIds(unsigned short indexOfDeletedElement)
    {
        for (unsigned int i = indexOfDeletedElement; i < m_Fields.size(); ++i)
        {
            m_Fields[i].SetFieldId(i);
        }
    }

}
