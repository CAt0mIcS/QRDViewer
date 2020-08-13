#include "stdafx.h"
#include "Application.h"


namespace QRDViewer
{
	Application::Application(const std::string& filePath, int argc, char** argv)
		: m_QApp(argc, argv), m_Database(filePath), m_Win()
	{
		m_Win.show();
	}

	int Application::Run()
	{
		return m_QApp.exec();
	}
}


