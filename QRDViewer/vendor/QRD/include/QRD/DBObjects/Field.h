#pragma once

#include "../Base.h"
#include "../pch.h"


namespace QRD
{
	class QRD_API Field
	{
	public:
		/**
		* Default constructor for field object
		*/
		Field() = default;

		/**
		* Constructor for field object
		*
		* @param fieldName is the name of the field
		* @param dbType is the type of data the field will store
		* @parma fieldId is the id of the field;
		*/
		Field(const std::string& fieldName, const DbTypes& dbType, const unsigned short fieldId);

		/**
		* Getter for field name
		*
		* @returns the field's name
		*/
		const std::string& GetFieldName() const { return m_FieldName; }

		/**
		* Getter for field id
		*
		* @returns the field's id
		*/
		unsigned short GetFieldId() const { return m_Id; }

		/**
		* Getter for field type
		*
		* @returns the field's type
		*/
		const DbTypes GetFieldType() const { return m_FieldType; }

		/**
		* Setter for field id, automatically called when deleting a field
		*
		* @param index is the new field id
		*/
		void SetFieldId(unsigned short index) { m_Id = index; }
	
	private:
		/**
		* The field's name
		*/
		std::string m_FieldName;

		/**
		* The field's type
		*/
		DbTypes m_FieldType;

		/**
		* Represents id in Table::m_Fields
		*/
		unsigned short m_Id;
	};

}

