#ifndef ICONLIST_H
#define ICONLIST_H

#include <QListWidget>

class IconList : public QListWidget
{
	Q_OBJECT
	
	public:
		IconList( QString filePath, QWidget *parent = 0 );
		
	private:
		QStringList fileList;
		QStringList filePreviewList;
		
	private slots:
		void showIcon( QListWidgetItem *item );
};

#endif
