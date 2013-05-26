#include <QDir>

#include <QMouseEvent>

#include "imagelabel.h"


ImageLabel::ImageLabel(QString fileName, int x, int y, QWidget *parent) : QLabel(parent)
{
	xVal = x;
	yVal = y;
	
	QStringList filter;
	filter << "*.png" << "*.PNG" ;
	
	QDir dir(fileName);
	dir.setNameFilters(filter);
	fileList = dir.entryList();

 	vector = new QVector<QPixmap>();
	
    	for(int i = 0; i < fileList.size(); i++)
		vector->append( QPixmap( fileName+fileList[i] ) );
	
	if(fileList.size() == 0)
		return;
	
   	resize( vector->at(0).size() );
 	setPixmap( vector->at(0) );
 	move(x, y);
	
	index = 0;
}

void ImageLabel::clickedSlot()
{
	emit clicked();
}

//  void ImageLabel::mousePressEvent(QMouseEvent *pe)
//  {
//   	if(pe->button() == Qt::LeftButton)
//  	{
//   		emit clicked();
//  		mLeftPressed = true;
//  	}
//  	mPosition = pe->pos();
//  }

QString ImageLabel::pixmap()
{
	QString str = fileList[index];
	str.truncate( str.length()-4 );
	
	return str;
}

int ImageLabel::currentIndex()
{
	return index;
}

int ImageLabel::count()
{
	return fileList.size();
}

void ImageLabel::changePixmap(int i)
{
	if(i >= 0 && i < vector->count()){
		setPixmap( vector->at(i) );
		resize( vector->at(i).size() );
		index = i;
	}
}

bool ImageLabel::changePixmap(QString name)
{
	for(int i = 0; i < fileList.size(); i++)
	{
		if( fileList[i].contains(name) )
		{
			setPixmap( vector->at(i) );
			resize( vector->at(i).size() );
			index = i;
			return true;
		}
	}
	return false;
}

int ImageLabel::X()
{
	return xVal;
}

int ImageLabel::Y()
{
	return yVal;
}


