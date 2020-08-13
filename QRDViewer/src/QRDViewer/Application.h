#pragma once

#include "stdafx.h"
#include "Windows/MainWindow.h"

#include <QtWidgets/QApplication>


namespace QRDViewer
{
	class Application
	{
	public:
		/**
		* Constructor for Application object
		* 
		* @param filePath is the path to the .dbs file for the database
		* @param argc is the argc in main()
		* @param argv are the argv in main()
		*/
		Application(const std::string& filePath, int argc, char** argv);

		/**
		* Starts the application run loop
		* 
		* @returns the exit code which means it should be called in the main() function with return app.Run()
		*/
		int Run();

	private:
		/**
		* Qt Application object
		*/
		QApplication m_QApp;

		/**
		* QRD Database object4
		*/
		QRD::Database m_Database;

		/**
		* Main window
		*/
		MainWindow m_Win;
	};
}


