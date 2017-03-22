/*  LabelEditor.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LabelEditor_h
#define LabelEditor_h


#include <QPainter>
#include <QScrollArea>
#include <QWidget>

#include "Region.h"


namespace glabels
{

	// Forward References
	class LabelModel;
	class LabelModelObject;
	class UndoRedoModel;
	class Handle;


	///
	/// LabelEditor Widget
	///
	class LabelEditor : public QWidget
	{
		Q_OBJECT

		/////////////////////////////////////
		// Lifecycle
		/////////////////////////////////////
	public:
		LabelEditor( QScrollArea* scrollArea, QWidget* parent = nullptr );


		/////////////////////////////////////
		// Signals
		/////////////////////////////////////
	signals:
		void contextMenuActivate();
		void zoomChanged();
		void pointerMoved( const Distance& x, const Distance& y );
		void pointerExited();
		void modeChanged();


		/////////////////////////////////////
		// Parameters
		/////////////////////////////////////
	public:
		double zoom() const;
		bool markupVisible() const;
		bool qridVisible() const;


		/////////////////////////////////////
		// Model
		/////////////////////////////////////
	public:
		void setModel( LabelModel* model, UndoRedoModel* undoRedoModel );


		/////////////////////////////////////
		// Visibility operations
		/////////////////////////////////////
	public:
		void setGridVisible( bool visibleFlag );
		void setMarkupVisible( bool visibleFlag );


		/////////////////////////////////////
		// Zoom operations
		/////////////////////////////////////
	public:
		void zoomIn();
		void zoomOut();
		void zoom1To1();
		void zoomToFit();
		bool isZoomMax() const;
		bool isZoomMin() const;
	private:
		void setZoomReal( double zoom, bool zoomToFitFlag );


		/////////////////////////////////////
		// Mode operations
		/////////////////////////////////////
	public:
		void arrowMode();
		void createBoxMode();
		void createEllipseMode();
		void createLineMode();
		void createImageMode();
		void createTextMode();
		void createBarcodeMode();


		/////////////////////////////////////
		// Event handlers
		/////////////////////////////////////
	protected:
		void resizeEvent( QResizeEvent* event ) override;
		void mousePressEvent( QMouseEvent* event ) override;
		void mouseMoveEvent( QMouseEvent* event ) override;
		void mouseReleaseEvent( QMouseEvent* event ) override;
		void leaveEvent( QEvent* event ) override;
		void keyPressEvent( QKeyEvent* event ) override;
		void paintEvent( QPaintEvent* event ) override;


		/////////////////////////////////////
		// Private methods
		/////////////////////////////////////
	private:
		void handleResizeMotion( const Distance& xWorld,
		                         const Distance& yWorld );

		void drawBgLayer( QPainter* painter );
		void drawGridLayer( QPainter* painter );
		void drawMarkupLayer( QPainter* painter );
		void drawObjectsLayer( QPainter* painter );
		void drawFgLayer( QPainter* painter );
		void drawHighlightLayer( QPainter* painter );
		void drawSelectRegionLayer( QPainter* painter );


		/////////////////////////////////////
		// Private slots
		/////////////////////////////////////
	private slots:
		void onSettingsChanged();
		void onModelSizeChanged();


		/////////////////////////////////////
		// Private data
		/////////////////////////////////////
	private:
		enum State {
			IdleState,
			ArrowSelectRegion,
			ArrowMove,
			ArrowResize,
			CreateIdle,
			CreateDrag
		};

		enum CreateType {
			Box,
			Ellipse,
			Line,
			Image,
			Text,
			Barcode
		};

		QScrollArea*         mScrollArea;

		double               mZoom;
		bool                 mZoomToFitFlag;
		double               mScale;
		Distance             mX0;
		Distance             mY0;

		bool                 mMarkupVisible;
		bool                 mGridVisible;

		double               mGridSpacing;
		Distance             mStepSize;

		LabelModel*          mModel;
		UndoRedoModel*       mUndoRedoModel;

		State                mState;

		/* ArrowSelectRegion state */
		bool                 mSelectRegionVisible;
		Region               mSelectRegion;

		/* ArrowMove state */
		Distance             mMoveLastX;
		Distance             mMoveLastY;

		/* ArrowResize state */
		LabelModelObject*    mResizeObject;
		Handle*              mResizeHandle;
		bool                 mResizeHonorAspect;

		/* CreateDrag state */
		CreateType           mCreateObjectType;
		LabelModelObject*    mCreateObject;
		Distance             mCreateX0;
		Distance             mCreateY0;


	};

}


#endif // LabelEditor_h
