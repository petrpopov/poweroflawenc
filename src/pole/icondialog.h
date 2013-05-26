#ifndef ICONDIALOG_H
#define ICONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMouseEvent>

class Qlabel;

class IconDialog : public QDialog
{
	Q_OBJECT
			
	public:
		IconDialog(QString &fileName, QWidget *parent = 0, Qt::WindowFlags fl = Qt::Window| Qt::FramelessWindowHint);
		
	private:
		QLabel *label;
};

#endif
