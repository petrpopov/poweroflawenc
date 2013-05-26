#ifndef TEXTEDITLIST_H
#define TEXTEDITLIST_H

#include <QTextEdit>

class TextEditList : public QTextEdit
{
	Q_OBJECT
	
	public:
		TextEditList( QWidget *parent = 0, int type = 0);
		void setOwnStyle();
		
	private slots:
 		virtual void mouseMoveEvent(QMouseEvent *pe);
 		virtual void mouseReleaseEvent(QMouseEvent *pe);
 		virtual void mousePressEvent(QMouseEvent *pe);
		virtual void mouseDoubleClickEvent ( QMouseEvent *pe );
		virtual void contextMenuEvent( QContextMenuEvent *e );
		
	private:
		QPoint mPosition;
		bool mLeftPressed;
};

#endif
