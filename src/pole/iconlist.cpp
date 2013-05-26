#include <QDir>

#include "iconlist.h"
#include "icondialog.h"

IconList::IconList( QString filePath, QWidget *parent) : QListWidget(parent)
{
	setViewMode(QListView::IconMode);
	setMovement(QListView::Static);
	setGeometry(100,170,520,280);
	setIconSize( QSize(150,150) );
	setGridSize( QSize(160, 160) );
	
	QPalette palette = this->palette();
	palette.setColor(QPalette::Active, QPalette::Text, QColor(0, 165, 200));
	palette.setColor(QPalette::Active, QPalette::Base, QColor(0, 0, 0));
	setPalette(palette);
	
	QStringList filter;
	filter << "*.png" << "*.PNG" << "*.jpg" << "*.JPG" ;
	
	QDir dir(filePath);
	if( !dir.exists() )
		return;
	
	dir.setNameFilters(filter);
	fileList = dir.entryList();
	
	for(int i = 0; i < fileList.size(); i++)
	{
		filePreviewList << dir.absolutePath() + "//small//" + fileList[i];
		fileList[i] = dir.absolutePath() + "//" + fileList[i];
	}
	
	for(int i = 0; i < fileList.size(); i++)
		addItem(new QListWidgetItem(QIcon(filePreviewList[i]),
			QString::number(i+1),this));
	
	connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), 
		this, SLOT(showIcon( QListWidgetItem*)));
	
	this->show();
}

void IconList::showIcon( QListWidgetItem *item )
{
	QString s = item->text();
	bool ok = false;
	int num = s.toInt(&ok, 10);
	if(!ok)
		return;
	
	IconDialog *dialog = new IconDialog(fileList[num-1], this);
	dialog->show();
}


