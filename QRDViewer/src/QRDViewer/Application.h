#pragma once

#include "stdafx.h"

#include <QtWidgets/QApplication>


namespace QRDViewer
{
	class Application
	{
	public:
		Application(const std::string& filePath, int argc, char** argv);

		int Run();

	private:
		QApplication m_QApp;

		QRD::Database m_Database;

		bool m_Running;
	};
}


