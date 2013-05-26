#include <QBitmap>
#include <QImage>
#include <QMouseEvent>
#include <QEvent>

#include "imagebutton.h"

ImageButton::ImageButton( QString fileName, int x, int y, QWidget *parent) : QPushButton(parent)
{
 	xVal = x;
 	yVal = y;
	
	mPressed = false;
	setMouseTracking( true );
	
	staticPixmap = QPixmap( fileName + "0.png" );
	pressPixmap = QPixmap( fileName + "1.png" );
	blinkPixmap = QPixmap( fileName + "2.png" );
	
	resize( staticPixmap.size() );
   	setMask( staticPixmap.mask() );
	setIcon( staticPixmap );
	setIconSize( staticPixmap.size() ); 
	setGeometry(x, y, staticPixmap.width(), staticPixmap.height() );
	
	setFocusPolicy( Qt::NoFocus );
	
	index = 0;
	bIndex = 0;
	pIndex = 0;
	stickBlink = false;
	stickPress = false;
}

int ImageButton::pixmapNumber()
{
	return index;
}

void ImageButton::changePixmap(int num)
{
	switch(num){
		case 0:
			setIcon( staticPixmap );
			index = 0;
			break;
		case 1:
			setIcon( pressPixmap );
			index = 1;
			break;
		case 2:
			setIcon( blinkPixmap );
			index = 2;
			break;
	}
}

void ImageButton::mousePressEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
	{
		mPressed = true;
		if(pIndex == 0 || pIndex % 2 == 0)
		{
			setIcon( pressPixmap );
			index = 1;
		}
		emit pressed();
	}	
}

void ImageButton::mouseReleaseEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
	{
		mPressed = false;
 		if( !underMouse() ){
			setIcon( staticPixmap );
			index = 0;
 		}
 		else{
 			setIcon( blinkPixmap );
 			index = 2;
 		}
		
		if(stickBlink)
			bIndex++;
		if(stickPress){
			if(pIndex % 2 == 0)
				pIndex++;
		}
		emit released();
 		emit clicked();
		emit playSoundPress();
	}
}

void ImageButton::enterEvent( QEvent *e )
{
	if(pIndex == 0)
	{
		if( index != 2)
		{
			setIcon( blinkPixmap );
			index = 2;
		}
	}
	else
	{
		if(pIndex % 2 == 0)
		{
			setIcon( blinkPixmap );
			index = 2;
		}
	}
	emit statusTextBegin();
	emit playSoundMove();
}

void ImageButton::leaveEvent( QEvent *e )
{
	if(bIndex != 0)
	{
		if(bIndex % 2 == 0)
		{
			setIcon(staticPixmap);
			index = 0;
		}
	}
	if(pIndex != 0)
	{
		if(pIndex % 2 != 0)
		{
			setIcon(pressPixmap);
			index = 1;
		}
		else
		{
			setIcon(staticPixmap);
			index = 0;
		}
	}
	else if(bIndex == 0 && pIndex == 0)
	{
		setIcon(staticPixmap);
		index = 0;
	}
	emit statusTextEnd();
}

void ImageButton::incPIndex()
{
	bIndex++;
}

void ImageButton::incPressIndex()
{
	if( pIndex % 2 != 0)
		pIndex++;
}

void ImageButton::setStickBlink(bool stick)
{
	stickBlink = stick;
}

void ImageButton::setStickPress(bool stick)
{
	stickPress = stick;
}



int ImageButton::x()
{
	return xVal;
}

int ImageButton::y()
{
	return yVal;
}
