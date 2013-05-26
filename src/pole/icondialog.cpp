#include <QFile>

#include <icondialog.h>

IconDialog::IconDialog(QString &fileName, QWidget *parent, Qt::WindowFlags fl) : QDialog(parent, fl)
{
	QFile file(fileName);
	if( !file.exists() )
		reject();
	
	QPalette palette = this->palette();
	palette.setColor(QPalette::Active, QPalette::Window, QColor(20,6,60));
	setPalette(palette);
	
	QPixmap pixmap(fileName);
	
	label = new QLabel(this);
	label->setPixmap( pixmap );
	label->setFrameStyle(QFrame::Box);
	label->setGeometry( 5, 5, 800, 600 );
	
	resize( 810, 610 );
	move(100, 100);
	
	setWindowTitle("Power of Law image");
	
	setModal(true);
}

