#include "lab1011.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "MySweetyGUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	lab1011 w;
	ProdusRepository repo;
	ProdusValidator val;
	ProdusService service{ repo,val };
	MySweetyGUI gui{ service };
	
	return a.exec();
}
