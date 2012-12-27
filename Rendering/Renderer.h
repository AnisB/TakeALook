/**
  * This file belongs to the TakeALook project
  *
  * @see https://github.com/AnisB/Inertia
  * @author 2012-2013 Anis Benyoub <benyoub.anis@gmail.com>
  * @see The GNU Public License (GPL)
  */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


#ifndef RENDERER_H_
#define RENDERER_H_


#include <list>
#include "../Objects/MovableObjects/Light.h"
#include "../Objects/MovableObjects/Camera.h"
#include "../Objects/StaticObjects/Tree.h"
#include "../Objects/StaticObjects/Map.h"
#include "../Types.h"
#include <string>
#include "SDL/SDL.h"
#include "../MathTools/Vector3.h"
#include "../MathTools/Vector4.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();
	void loadMap(std::string aFile );
	void setCamera(Vector3 aPosition, Vector3 aDirection);
	void addLight(Vector3 aPosition);
	void render();

protected:
	T_Matrix<double> baryCentre(T_Matrix<double> machin, Vector3 pos);
	T_Matrix<double> perspective(T_Matrix<double> machin, double focale);
	void generateTriangles();
	void display();
	void refresh();
	void drawLine(SDL_Surface * ecran,double x1,double y1, double x2, double y2,double color);
	void drawTriangle(SDL_Surface * aScreen,
						int x1, int y1,
						int x2, int y2,
						int x3, int y3,
						double r, double g,
						double b, double a);

	void drawPolygon(SDL_Surface * aScreen,
			const int * x, const int * y,
			int aSize, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int _filledRectAlpha(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha);
	int filledRectAlpha(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
	int _HLineAlpha(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color);
	int hlineColor(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color);
	int drawPolygonColorMT(SDL_Surface * dst, const int * vx, const int * vy, int n, Uint32 color, int **polyInts, int *polyAllocated);




protected :
	std::list<Light *> mLights;
	Map * myMap ;
	Camera * mCamera;
	std::list<Tree *> mTrees;
	bool mIsRendering;
	SDL_Event mEvent;
	SDL_Surface *mEcran ;
	std::list<Triangle> mTriangles;
	std::list<Line> mLines;
	int *mPrimitivesPolyIntsGlobal;
	int mPrimitivesPolyAllocatedGlobal;
};

#endif /* RENDERER_H_ */
