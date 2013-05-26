#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class QPixmap;

class ImageButton : public QPushButton
{
	Q_OBJECT
			
	public:
		ImageButton(QString fileName, int x = 0, int y = 0,  QWidget *parent = 0);
		int x();
		int y();
		int pixmapNumber();
		void incPIndex();
		void incPressIndex();
		void setStickBlink(bool stick);
		void setStickPress(bool stick);
		
	private:
		int xVal;
		int yVal;
		int index;
		int bIndex;
		int pIndex;
		QPixmap staticPixmap;
		QPixmap pressPixmap;
		QPixmap blinkPixmap;
		bool mPressed;
		bool stickBlink;
		bool stickPress;
	
	private slots:
		virtual void mousePressEvent(QMouseEvent *pe);
		virtual void mouseReleaseEvent(QMouseEvent *pe);
		virtual void enterEvent( QEvent *e );
		virtual void leaveEvent( QEvent *e );
		
	public slots:
		void changePixmap(int num);
		
	signals:
		void playSoundMove();
		void playSoundPress();
		void statusTextBegin();
		void statusTextEnd();
};

#endif
