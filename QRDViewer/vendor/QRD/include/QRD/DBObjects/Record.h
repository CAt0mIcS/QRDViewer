#pragma once

#include "../Base.h"
#include "../pch.h"


namespace QRD
{
	class QRD_API Record
	{
	public:
		/**
		* Default constructor for Record
		*/
		Record() = default;

		/**
		* Constructor for Record
		*
		* @param id is the id of the new record
		*/
		Record(unsigned int id) : m_Id(id) {}

		/**
		* Adds data to existing record
		*
		* @param data is the data to add to the record
		*/
		template<typename T/*, class Enable = std::enable_if_t<std::is_convertible_v<T, std::string>>*/>
		void AddData(const T& data);

		/**
		* Getter for record data
		*
		* @returns all the data in this record
		*/
		const std::vector<std::string>& GetRecordData() const { return m_Data; }

		/**
		* Compares m_Data
		*
		* @param other is the other Record
		* @returns true if m_Data = other.m_Data, else false
		*/
		bool operator==(const Record& other) const;

		/**
		* Getter for record id
		*
		* @returns the record's id
		*/
		unsigned int GetRecordId() const { return m_Id; }

		/**
		* Setter for record id, automatically called when deleting a record
		*
		* @param index is the new record id
		*/
		void SetRecordId(unsigned int index) { m_Id = index; }

		/**
		* Deletes the data at fieldId
		*
		* @param fieldId is the id of the field where the data is stored
		*/
		void DeleteData(unsigned short fieldId);

	private:
		/**
		* Datastructure for data in Record
		*/
		std::vector<std::string> m_Data;

		/**
		* Represents id in Table::m_Records
		*/
		unsigned int m_Id;
	};


	template<typename T>
	inline void Record::AddData(const T& data)
	{
		std::stringstream ss;
		ss << data;
		m_Data.emplace_back(ss.str());
	}
}



