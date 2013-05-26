#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QFile>
#include <QMessageBox>

#include "mainform.h"

int checkFiles()
{
	QString fileList = ".//data/journal.txt	.//data/main.txt	.//data/maps.txt	.//data/news.txt	.//data/status.txt	";
	fileList += ".//data//db//ammunition_descr.txt	.//data//db//equipment_descr.txt	.//data//db//grenades.txt	.//data//db//tech_descr.txt	.//data//db//ammunition.txt	.//data//db//equipment.txt	.//data//db//people_descr.txt	.//data//db//tech.txt	.//data//db//armors_descr.txt	.//data//db//forces.txt	.//data//db//people_trans.txt	.//data//db//weapons_descr.txt	.//data//db//armors.txt	.//data//db//grenades_descr.txt	.//data//db//people.txt	.//data//db//weapons.txt";
	
	QStringList l = fileList.split("\t");
	QFile f(l[0]);
	QString error;
	
	for(int i = 0; i < l.size(); i++)
	{
		f.setFileName( l[i] );
		if( !f.exists() )
			error += l[0] + "\n";
	}
	
	if( !error.isEmpty() )
	{
		QMessageBox::critical(0, "Power of Law Encyclopedia", "Some files are corrupted or missed.\nThe application will exit now.", QMessageBox::Close );
		
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	if(checkFiles() == 1)
		return -1;
	
	QTranslator appTranslator;
	appTranslator.load(":/translations/pole_" + QLocale::system().name(), qApp->applicationDirPath());
	app.installTranslator(&appTranslator);

	MainForm *mainForm = new MainForm;
	mainForm->show();
	return app.exec();
}
