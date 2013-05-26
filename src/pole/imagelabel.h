#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

class QPixmap;

class ImageLabel : public QLabel
{
	Q_OBJECT
			
	public:
		ImageLabel(QString fileName, int x = 0, int y = 0, QWidget *parent = 0);
		int X();
		int Y();
		QString pixmap();
		
	signals:
		void clicked();
	
	public slots:
		void changePixmap(int i);
		bool changePixmap(QString name);
		int currentIndex();
		int count();
		
		void clickedSlot();
		
	private:
		int xVal;
		int yVal;
		int index;
		QVector<QPixmap> *vector;
		QStringList fileList;
		bool mLeftPressed;
		QPoint mPosition;
		
//   	private slots:
//   		virtual void mousePressEvent(QMouseEvent *pe);
};

#endif
