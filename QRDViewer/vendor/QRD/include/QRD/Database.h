#pragma once

#include "Base.h"
#include "pch.h"

#include "DBObjects/Table.h"
#include "DBObjects/Record.h"
#include "DBObjects/Field.h"


namespace QRD
{


	class QRD_API Database
	{
	public:

		/**
		* Constructor for Database object
		*
		* @param filePath is the path to the .dbs file
		* @param tableAmnt is the total amount of tables the program will allocate memory for
		*/
		Database(const std::string& filePath, unsigned short tableAmnt = 10);

		/**
		* Creates a new table, adds it to m_Data
		*
		* @param tableName is the name the table will have
		* @returns the newly created table
		*/
		Table& CreateTable(const std::string& tableName);

		/**
		* Finds the table by name
		* 
		* @param tableName is the name of the table to search for
		* @returns the found table, empty table object if not found
		*/
		Table& GetTable(const std::string& tableName);

		/**
		* Deletes the table
		*
		* @param table is the table to delete
		*/
		void DeleteTable(const Table& table);

		/**
		* Deletes the table
		*
		* @param tableName is the table's name
		*/
		void DeleteTable(const std::string& tableName);

		/**
		* Reads database stored in file into memory
		*/
		void ReadDb();

		/**
		* Writes the database stored in memory to file
		*/
		void WriteDb();

		/**
		* Writes everything stored in memory to file and destroys all database object in memory
		*/
		void ExitDb();

		/**
		* Function should be called before creating any tables to allocate more memory for the vector of tables
		*
		* @param tableAmnt is the amount of tables the client is going to create
		*/
		void ReserveTables(unsigned int tableAmnt);

		/************************************************************************************
		*****************           DEBUG FUNCTIONS AND VARIABLES           *****************
		************************************************************************************/
		std::vector<Table>& GetTables() { return m_Tables; }

	private:
		void ReadFields(std::ifstream& reader, std::string& line);
		void ReadRecords(std::ifstream& reader, std::string& line);

	private:
		
		/**
		* Datastructure holding all tables and their corresponding records
		*/
		std::vector<Table> m_Tables;
		
		/**
		* File path to the .dbs file
		*/
		const std::string m_DBFilePath;
	};
}


