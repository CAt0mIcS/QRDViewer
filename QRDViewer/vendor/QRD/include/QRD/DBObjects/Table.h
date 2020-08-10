#pragma once

#include "../Base.h"
#include "../pch.h"
#include "Field.h"
#include "Record.h"


namespace QRD
{

	class QRD_API Table
	{
	public:
		/**
		* Constructor for Table object
		*
		* @param tableName is the name under which the table will be stored
		*/
		Table(const std::string& tableName, const int id);

		/**
		* Adds a new field to the current table
		*
		* @param fieldName is the name of the field
		* @returns a reference to the new field
		* @warning if the vector which stores the field gets resized, all references will be invalid
		*/
		template<DbTypes FIELD_DATA_TYPE>
		Field& AddField(const std::string& fieldName);
		
		/**
		* Finds the field with specified name
		*
		* @param fieldName is the name of the searched field
		* @returns the found field, if it does not find anything it doesn't return
		*/
		Field& GetField(const std::string_view fieldName);

		/**
		* Getter for all fields
		*
		* @returns all fields in this table
		*/
		const std::vector<Field>& GetFields() const { return m_Fields; }

		/**
		* Deletes the field and updates indices
		*
		* @param field is the field which will be deleted
		*/
		void DeleteField(const Field& field);

		/**
		* Deletes the field and updates indices
		*
		* @param fieldName is the name of the field which will be deleted
		*/
		void DeleteField(const std::string& fieldName);

		/**
		* Adds a record to the current table
		*
		* @param data is the data corresponding to the fields to insert
		* @returns a reference to the new record
		* @warning if the vector which stores the records gets resized, all references will be invalid
		*/
		template<typename... Args>
		Record& AddRecord(const Args&... data);

		/**
		* Finds all records with specific values
		*
		* @param commandStrs are the search specifications, e.g. "field1:MyName", "field3:32"...
		* @returns a vector of all found records with specifications
		*/
		template<typename... Args>
		std::vector<Record> GetRecordsByValues(const Args&... commandStrs);

		/**
		* Returns the record by id
		*
		* @param is is the id in m_Records
		* @rreturns the record in m_Records with id
		*/
		Record& GetRecordById(const unsigned int id);

		/**
		* Getter for all records
		*
		* @returns all records in m_Records
		*/
		const auto& GetRecords() const { return m_Records; }

		/**
		* Edits the record
		*
		* @param record is the record to be edited
		* @param newData is the new data to insert into the record
		*/
		template<typename... Args>
		void EditRecord(const Record& record, const Args&... newData);

		/**
		* Deletes the record and updates indices
		*
		* @param record is the record to delete
		*/
		void DeleteRecord(const Record& record);

		/**
		* Deletes the found records with search specifications and updates indices
		*
		* @param commandStrs are the search specifications, e.g. "field1:MyName", "field3:32"...
		*/
		template<typename... Args>
		void DeleteRecord(const Args&... commandStrs);

		/**
		* Compares record ids
		*
		* @param other is the other table object
		* @returns true if the ids match else false
		*/
		bool operator==(const Table& other) const;

		/**
		* Getter for table name
		*
		* @returns the table's name
		*/
		const std::string& GetTableName() const { return m_TableName; }

		/**
		* Getter for table id
		*
		* @returns the table's id
		*/
		unsigned short GetTableId() const { return m_Id; }
		
		/**
		* Updates record id's after deleting a record
		*
		* @param indexOfDeletedElement is the index where the element was before it's deletion
		*/
		void UpdateRecordIds(unsigned int indexOfDeletedElement);

		/**
		* Updates field id's after deleting a field
		*
		* @param indexOfDeletedElement is the index where the element was before it's deletion
		*/
		void UpdateFieldIds(unsigned short indexOfDeletedElement);

	private:

	private:
		/**
		* The table's name
		*/
		std::string m_TableName;

		/**
		* List of all records in this table, gets populated in Database::Read()
		*/
		std::vector<Record> m_Records;

		/**
		* List of all fields in this table, gets populated in Database::Read()
		*/
		std::vector<Field> m_Fields;

		/**
		* Represents the index of the table
		*/
		unsigned short m_Id;
	};


	template<DbTypes FIELD_DATA_TYPE>
	inline Field& Table::AddField(const std::string& fieldName)
	{
		Field field(fieldName, FIELD_DATA_TYPE, (unsigned short)m_Fields.size());
		m_Fields.emplace_back(std::move(field));
		return m_Fields[m_Fields.size() - 1];
	}

	template<typename ...Args>
	inline Record& Table::AddRecord(const Args& ...data)
	{
		Record rec((unsigned int)m_Records.size());
		(rec.AddData(data), ...);
		m_Records.emplace_back(std::move(rec));
		return m_Records[m_Records.size() - 1];
	}

	template<typename... Args>
	inline std::vector<Record> Table::GetRecordsByValues(const Args&... commandStrs)
	{
		std::vector<Record> recs = m_Records;
		std::vector<std::string_view> commands{ commandStrs... };

		/**
		* Add this and remove recs = m_Records copy if you want to avoid copying all records
		*/

		//for (auto& cmd : commands)
		//{
		//	unsigned short dataIdx = cmd.find(":") + 1;
		//	std::string_view searchData = cmd.substr(dataIdx);
		//	std::string_view fieldName = cmd.substr(0, dataIdx - 1);

		//	Field& field = this->GetField(fieldName);
		//	unsigned short fieldIdx = field.GetFieldId();

		//	for (auto& record : m_Records)
		//	{
		//		for (auto& data : record.GetData())
		//		{
		//			if (data == searchData)
		//			{
		//				if (!std::count(recs.begin(), recs.end(), record))
		//				{
		//					recs.emplace_back(record);
		//				}
		//			}
		//		}
		//	}
		//}

		unsigned short dataIdx;
		std::string_view searchData;
		std::string_view fieldName;
		for (auto& cmd : commands)
		{
			dataIdx = cmd.find(":") + 1;
			searchData = cmd.substr(dataIdx);
			fieldName = cmd.substr(0, dataIdx - 1);
		}

		for (unsigned int i = 0; i < recs.size(); ++i)
		{
			Field& field = this->GetField(fieldName);
			unsigned short fieldId = field.GetFieldId();
			for (auto& cmd : commands)
			{
				if (recs[i].GetRecordData()[fieldId] != searchData)
				{
					recs.erase(recs.begin() + i);
					--i;
				}
			}
		}

		return recs;
	}

	template<typename... Args>
	void Table::EditRecord(const Record& record, const Args&... newData)
	{
		
	}

	template<typename... Args>
	void Table::DeleteRecord(const Args&... commandStrs)
	{
		std::vector<Record> recs = GetRecordsByValues(commandStrs...);

		for (const auto& rec : recs)
		{
			unsigned int recId = rec.GetRecordId();
			m_Records.erase(m_Records.begin() + recId);
			UpdateRecordIds(recId);
		}

	}

}
