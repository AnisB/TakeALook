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


#include "Renderer.h"
#include <iostream>
#include <cstdlib>
using namespace std;
Renderer::Renderer()
{
    mPrimitivesPolyIntsGlobal = NULL;
    mPrimitivesPolyAllocatedGlobal = 0;
	mIsRendering=true;
	mEcran = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	mEcran = SDL_SetVideoMode(640, 650, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("TakeALook", NULL);
}

Renderer::~Renderer()
{
	SDL_Quit();
	delete myMap;
}

void Renderer::loadMap(std::string aFile )
{
	myMap= new Map(aFile);
	myMap->rafiner();
	myMap->rafiner();
}

void Renderer::render()
{
	while (mIsRendering)
	{


	    SDL_WaitEvent(&mEvent);

		switch(mEvent.type)
	    {
	        case SDL_QUIT:
	        	mIsRendering = 0;
	            break;
	        case SDL_MOUSEMOTION:
	            mCamera->motion(mEvent.motion.xrel, mEvent.motion.yrel);
	            break;
	        case SDL_KEYDOWN:
	            switch (mEvent.key.keysym.sym)
	            {
	            case SDLK_i :
	            		mCamera->focalDistance /=3;
	            	break;
	            case SDLK_o:
            		mCamera->focalDistance *=3;
	            break;

	            case SDLK_f :
	            		myMap->scale /=2;
	            	break;
	            case SDLK_g:
	            	myMap->scale *=2;
	            break;
					case SDLK_z :
						mCamera->fd();
					break;
					case SDLK_q:
						mCamera->ld();
					break;
					case SDLK_b:
						mCamera->show();
					break;
					case SDLK_j :
							mCamera->u();
						break;
						case SDLK_k:
							mCamera->d();
						break;
					case SDLK_s:
						mCamera->bd();
					break;
					case SDLK_d:
						mCamera->rd();
					break;
					case SDLK_ESCAPE:
							mIsRendering = false;
					break;
					default:
						break;
	            }
	            break;
	            default:
	            	break;
	    }

	    refresh();
	}
}

void Renderer::setCamera(Vector3 aPosition, Vector3 aDirection)
{
	mCamera = new Camera(aPosition,aDirection);
}
void Renderer::addLight(Vector3 aPosition)
{
}


void Renderer::generateTriangles()
{
	if(myMap!=NULL)
	{

		double RE=myMap->scale;;
		TakeALook::T_Matrix<double>  Y (((myMap->getMap()->dimRows-1)*(myMap->getMap()->dimColumns-1))*2,13);
		int k=0;
		for(int i=1;i<myMap->getMap()->dimRows;i++)
		{
			for(int j=1;j<myMap->getMap()->dimColumns;j++)
			{

					Y.P[k][0]=(i-1)*RE;
					Y.P[k][1]=(j-1)*RE;
					Y.P[k][2]=myMap->getMap()->P[i-1][j-1];
					Y.P[k][3]=(i-1)*RE;
					Y.P[k][4]=(j)*RE;
					Y.P[k][5]=myMap->getMap()->P[i-1][j];
					Y.P[k][6]=(i)*RE;
					Y.P[k][7]=(j)*RE;
					Y.P[k][8]=myMap->getMap()->P[i][j];
					k++;

						Y.P[k][0]=(i-1)*RE;
						Y.P[k][1]=(j-1)*RE;
						Y.P[k][2]=myMap->getMap()->P[i-1][j-1];
						Y.P[k][3]=(i)*RE;
						Y.P[k][4]=(j)*RE;
						Y.P[k][5]=myMap->getMap()->P[i][j];
						Y.P[k][6]=(i)*RE;
						Y.P[k][7]=(j-1)*RE;
						Y.P[k][8]=myMap->getMap()->P[i][j-1];
					k++;
			}
		}
		//cout<<"Y"<<endl<<Y<<endl;
		T_Matrix<double> Z = Y;
		Vector3 W =(mCamera->getPosition()-mCamera->getDirection());
		double norm= W.Norm();
		W=W/norm;
		//cout<<"W"<<endl;
		//W.debugDisplay();

		Vector3 U(0,0,1);
		U=mCamera->getUpVector();

		norm=U.Norm();
		U=U/norm;
		//cout<<"U"<<endl;
		//U.debugDisplay();
		Vector3 V=W;
		V=V.Cross(U);
		//cout<<"V"<<endl;
		//V.debugDisplay();
		T_Matrix<double> aMatrix (3) ;
		aMatrix.setIdentity();
		aMatrix.P[0][0]=U.GetX();
		aMatrix.P[1][0]=U.GetY();
		aMatrix.P[2][0]=U.GetZ();

		aMatrix.P[0][1]=V.GetX();
		aMatrix.P[1][1]=V.GetY();
		aMatrix.P[2][1]=V.GetZ();

		aMatrix.P[0][2]=W.GetX();
		aMatrix.P[1][2]=W.GetY();
		aMatrix.P[2][2]=W.GetZ();
		//cout<<"aMatrix"<<endl<<aMatrix<<endl;

		T_Matrix<double>  Rot (4) ;
		Rot.setIdentity();
		T_Matrix<double> tmp(aMatrix);
		tmp.Reverse();
		for(int i=0; i<3;i++)
		{
			for(int j=0; j<3;j++)
			{
				Rot.P[i][j]=tmp.P[i][j];
			}
		}
		//cout<<"Rot"<<endl<<Rot<<endl;

		T_Matrix<double> Translation(4);
		Translation.setIdentity();
		Translation.P[0][3]=mCamera->getPosition().GetX();
		Translation.P[1][3]=mCamera->getPosition().GetY();
		Translation.P[2][3]=mCamera->getPosition().GetZ();
		Translation.P[3][3]=1;

		T_Matrix<double> tmp2(4);
		tmp2=Translation;

		tmp2.Reverse();
		//cout<<"BeforeTmp"<<endl<<tmp2<<endl;

		//cout<<"Tmp"<<endl<<tmp2<<endl;
		T_Matrix<double> passage(3);
		//cout<<"Pre mul"<<endl;

		passage=(Rot * tmp2);

		//cout<<"passage"<<endl<<passage<<endl;

		Z= baryCentre(Z,mCamera->getPosition());
		//cout<<"Z2"<<endl<<Z<<endl;
		//cout<<"passage"<<endl<<passage<<endl;

		int nombreTri= Z.dimRows;

		for(int i=0; i<nombreTri;i++ )
		{
			Vector4 vect1(Z.P[i][0],Z.P[i][1],Z.P[i][2],1);
			vect1=(passage*vect1);
			vect1.Set(vect1.x/vect1.w, vect1.y/vect1.w, vect1.z/vect1.w, 1);
			Vector4 vect2(Z.P[i][3],Z.P[i][4],Z.P[i][5],1);
			vect2=passage*vect2;
			vect2.Set(vect2.x/vect2.w,vect2.y/vect2.w,vect2.z/vect2.w,1);

			Vector4 vect3(Z.P[i][6],Z.P[i][7],Z.P[i][8],1);
			vect3=passage*vect3;
			vect3.Set(vect3.x/vect3.w,vect3.y/vect3.w,vect3.z/vect3.w,1);

			Z.P[i][0]=vect1.x;
			Z.P[i][1]=vect1.y;
			Z.P[i][2]=vect1.z;

			Z.P[i][3]=vect2.x;
			Z.P[i][4]=vect2.y;
			Z.P[i][5]=vect2.z;

			Z.P[i][6]=vect3.x;
			Z.P[i][7]=vect3.y;
			Z.P[i][8]=vect3.z;

		}

		//cout<<"Z3"<<endl<<Z<<endl;

		Z=perspective(Z,mCamera->focalDistance);
		//cout<<"Z4"<<endl<<Z<<endl;

		for(int i=0;i<nombreTri;i++)
		{
			if(!((Z.P[i][0]<0) &&(Z.P[i][1]<0)&&
					(Z.P[i][3]>700)&&(Z.P[i][4]>700)))
			{

			int r=	rand()%10;
			cout<<"r"<<r<<endl;
			TALColor color = myMap->getColor((int)Y.P[i][2]);
			Triangle tx;
			tx.a=color.a;
			if((color.r+r)<255)
				tx.r=(color.r+r);
			else
				tx.r=(color.r);

			if((color.g+r)<255)
				tx.g=(color.g+r);
			else
				tx.g=(color.g);

			if((color.b+r)<255)
					tx.b=(color.b+r);
				else
					tx.b=(color.b);
			tx.mP1.x=(Z.P[i][0]);
			tx.mP1.y=(Z.P[i][1]);
			tx.mP2.x=(Z.P[i][3]);
			tx.mP2.y=(Z.P[i][4]);
			tx.mP3.x=(Z.P[i][6]);
			tx.mP3.y=(Z.P[i][7]);
			mTriangles.push_back(tx);
			}

		}


	}

}

T_Matrix<double> Renderer::perspective(T_Matrix<double> Z, double focale)
{
	T_Matrix<double> passage(4);
	passage.setIdentity();
	passage.P[3][2]=-1/focale;
	int nombreTri=Z.dimRows;
	for(int i=0; i<nombreTri;i++ )
	{
		Vector4 vect1(Z.P[i][0],Z.P[i][1],Z.P[i][2],1);
		vect1=passage*vect1;
		vect1.Set(vect1.x/vect1.w,vect1.y/vect1.w,vect1.z/vect1.w,1);

		Vector4 vect2(Z.P[i][3],Z.P[i][4],Z.P[i][5],1);
		vect2=passage*vect2;
		vect2.Set(vect2.x/vect2.w,vect2.y/vect2.w,vect2.z/vect2.w,1);

		Vector4 vect3(Z.P[i][6],Z.P[i][7],Z.P[i][8],1);
		vect3=passage*vect3;
		vect3.Set(vect3.x/vect3.w,vect3.y/vect3.w,vect3.z/vect3.w,1);

		Z.P[i][0]=vect1.x;
		Z.P[i][1]=vect1.y;
		Z.P[i][2]=vect1.z;

		Z.P[i][3]=vect2.x;
		Z.P[i][4]=vect2.y;
		Z.P[i][5]=vect2.z;

		Z.P[i][6]=vect3.x;
		Z.P[i][7]=vect3.y;
		Z.P[i][8]=vect3.z;

	}
	return Z;
}
T_Matrix<double> Renderer::baryCentre(T_Matrix<double> machine, Vector3 pos)
{
	T_Matrix<double> BaryCentred =machine;
	int nbTriangle = machine.dimRows;
	Vector3 vectorMachin;
	for(int i=0;i<nbTriangle;i++)
	{
		BaryCentred.P[i][9]=(BaryCentred.P[i][0]+BaryCentred.P[i][3]+BaryCentred.P[i][6])/3;
		BaryCentred.P[i][10]=(BaryCentred.P[i][1]+BaryCentred.P[i][4]+BaryCentred.P[i][7])/3;
		BaryCentred.P[i][11]=(BaryCentred.P[i][2]+BaryCentred.P[i][5]+BaryCentred.P[i][8])/3;
		vectorMachin.Set(BaryCentred.P[i][9],BaryCentred.P[i][10],BaryCentred.P[i][11]);
		Vector3 mach(vectorMachin-pos);
		BaryCentred.P[i][12]=1/mach.Norm();
	}
	return BaryCentred;
}
void Renderer::display()
{
	std::list<Triangle>::iterator it;
	it=mTriangles.begin();
	while(it!=mTriangles.end())
	{

		drawTriangle(mEcran,
	                     ((*it).mP1.x*-1), ((*it).mP1.y*-1),
	                     ((*it).mP2.x*-1), ((*it).mP2.y*-1),
	                     ((*it).mP3.x*-1), ((*it).mP3.y*-1),
	                     (*it).r, (*it).g,(*it).b,(*it).a);
		it++;
	}
	//cout<<"Lignes"<<endl;

	std::list<Line>::iterator itx;
	itx=mLines.begin();
	while(itx!=mLines.end())
	{


		drawLine(mEcran,
	                     ((*itx).mP1.x*-1), ((*itx).mP1.y*-1),
	                     ((*itx).mP2.x*-1), ((*itx).mP2.y*-1),(*itx).r+ (*itx).g+(*itx).b+(*itx).a);
		itx++;
	}

	//cout<<"Fin draw"<<endl;


}
void Renderer::refresh()
{
	SDL_FillRect(mEcran, NULL, SDL_MapRGB(mEcran->format, 0, 0, 0));
	mTriangles.clear();
	mLines.clear();
	generateTriangles();
	display();

	SDL_Flip(mEcran);

}

void Renderer::drawLine(SDL_Surface * ecran,double x1,double y1, double x2,double y2,double color)

{
	double x = x2 - x1;
	double y = y2 - y1;
	double length = sqrt( x*x + y*y );

	double addx = x / length;
	double addy = y / length;

	x = x1;
	y = y1;

	for(double i = 0; i < length; i += 1)
	{
	  drawTriangle(ecran, x, y, x+1, y,x,y+1, 255,0,0,255);
	  x += addx;
	  y += addy;
	}
}

void Renderer::drawTriangle(
					SDL_Surface * aScreen,
					int x1, int y1,
					int x2, int y2,
					int x3, int y3,
					double r, double g,
					double b, double a)
{
	   int x[3];
	   int y[3];
       x[0]=x1;
       x[1]=x2;
       x[2]=x3;
       y[0]=y1;
       y[1]=y2;
       y[2]=y3;
       drawPolygon(aScreen,x,y,3,r,g,b,a);
}


int _gfxPrimitivesCompareInt(const void *a, const void *b)
{
         return (*(const int *) a) - (*(const int *) b);
}


 int Renderer::_filledRectAlpha(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha)
 {
         SDL_PixelFormat *format;
         Uint32 Rmask, Gmask, Bmask, Amask;
         Uint32 Rshift, Gshift, Bshift, Ashift;
         Uint32 sR, sG, sB, sA;
         Uint32 dR, dG, dB, dA;
         Sint16 x, y;

         if (dst == NULL) {
                 return (-1);
         }

         format = dst->format;
         switch (format->BytesPerPixel) {
         case 1:
                 {                       /* Assuming 8-bpp */
                         Uint8 *row, *pixel;
                         Uint8 R, G, B;
                         SDL_Color *colors = format->palette->colors;
                         SDL_Color dColor;
                         SDL_Color sColor = colors[color];
                         sR = sColor.r;
                         sG = sColor.g;
                         sB = sColor.b;

                         for (y = y1; y <= y2; y++) {
                                 row = (Uint8 *) dst->pixels + y * dst->pitch;
                                 for (x = x1; x <= x2; x++) {
                                         if (alpha == 255) {
                                                 *(row + x) = color;
                                         } else {
                                                 pixel = row + x;

                                                 dColor = colors[*pixel];
                                                 dR = dColor.r;
                                                 dG = dColor.g;
                                                 dB = dColor.b;

                                                 R = dR + ((sR - dR) * alpha >> 8);
                                                 G = dG + ((sG - dG) * alpha >> 8);
                                                 B = dB + ((sB - dB) * alpha >> 8);

                                                 *pixel = SDL_MapRGB(format, R, G, B);
                                         }
                                 }
                         }
                 }
                 break;

         case 2:
                 {                       /* Probably 15-bpp or 16-bpp */
                         Uint16 *row, *pixel;
                         Uint16 R, G, B, A;
                         Uint16 dc;
                         Rmask = format->Rmask;
                         Gmask = format->Gmask;
                         Bmask = format->Bmask;
                         Amask = format->Amask;

                         sR = (color & Rmask);
                         sG = (color & Gmask);
                         sB = (color & Bmask);
                         sA = (color & Amask);

                         for (y = y1; y <= y2; y++) {
                                 row = (Uint16 *) dst->pixels + y * dst->pitch / 2;
                                 for (x = x1; x <= x2; x++) {
                                         if (alpha == 255) {
                                                 *(row + x) = color;
                                         } else {
                                                 pixel = row + x;
                                                 dc = *pixel;

                                                 dR = (dc & Rmask);
                                                 dG = (dc & Gmask);
                                                 dB = (dc & Bmask);

                                                 R = (dR + ((sR - dR) * alpha >> 8)) & Rmask;
                                                 G = (dG + ((sG - dG) * alpha >> 8)) & Gmask;
                                                 B = (dB + ((sB - dB) * alpha >> 8)) & Bmask;
                                                 *pixel = R | G | B;
                                                 if (Amask!=0) {
                                                         dA = (dc & Amask);
                                                         A = (dA + ((sA - dA) * alpha >> 8)) & Amask;
                                                         *pixel |= A;
                                                 }
                                         }
                                 }
                         }
                 }
                 break;

         case 3:
                 {                       /* Slow 24-bpp mode, usually not used */
                         Uint8 *row, *pixel;
                         Uint8 R, G, B;
                         Uint8 Rshift8, Gshift8, Bshift8;

                         Rshift = format->Rshift;
                         Gshift = format->Gshift;
                         Bshift = format->Bshift;

                         Rshift8 = Rshift >> 3;
                         Gshift8 = Gshift >> 3;
                         Bshift8 = Bshift >> 3;

                         sR = (color >> Rshift) & 0xff;
                         sG = (color >> Gshift) & 0xff;
                         sB = (color >> Bshift) & 0xff;

                         for (y = y1; y <= y2; y++) {
                                 row = (Uint8 *) dst->pixels + y * dst->pitch;
                                 for (x = x1; x <= x2; x++) {
                                         pixel = row + x * 3;

                                         if (alpha == 255) {
                                                 *(pixel + Rshift8) = sR;
                                                *(pixel + Gshift8) = sG;
                                                 *(pixel + Bshift8) = sB;
                                        } else {
                                                  dR = *((pixel) + Rshift8);
                                                 dG = *((pixel) + Gshift8);
                                                 dB = *((pixel) + Bshift8);

                                                 R = dR + ((sR - dR) * alpha >> 8);
                                                 G = dG + ((sG - dG) * alpha >> 8);
                                                 B = dB + ((sB - dB) * alpha >> 8);

                                                 *((pixel) + Rshift8) = R;
                                                 *((pixel) + Gshift8) = G;
                                                 *((pixel) + Bshift8) = B;
                                         }
                                 }
                         }
                 }
                 break;


         case 4:
                 {
                         Uint32 *row, *pixel;
                         Uint32 R, G, B, A;
                         Uint32 dc;
                         Rmask = format->Rmask;
                         Gmask = format->Gmask;
                         Bmask = format->Bmask;
                         Amask = format->Amask;

                        Rshift = format->Rshift;
                         Gshift = format->Gshift;
                         Bshift = format->Bshift;
                        Ashift = format->Ashift;

                         sR = (color & Rmask) >> Rshift;
                         sG = (color & Gmask) >> Gshift;
                         sB = (color & Bmask) >> Bshift;
                        sA = (color & Amask) >> Ashift;

                        for (y = y1; y <= y2; y++) {
                                 row = (Uint32 *) dst->pixels + y * dst->pitch / 4;
                                 for (x = x1; x <= x2; x++) {
                                         if (alpha == 255) {
                                                 *(row + x) = color;
                                         } else {
                                                 pixel = row + x;
                                                 dc = *pixel;

                                                 dR = (dc & Rmask) >> Rshift;
                                                 dG = (dc & Gmask) >> Gshift;
                                                 dB = (dc & Bmask) >> Bshift;

                                                 R = ((dR + ((sR - dR) * alpha >> 8)) << Rshift) & Rmask;
                                                 G = ((dG + ((sG - dG) * alpha >> 8)) << Gshift) & Gmask;
                                                 B = ((dB + ((sB - dB) * alpha >> 8)) << Bshift) & Bmask;
                                                 *pixel = R | G | B;
                                                 if (Amask!=0) {
                                                         dA = (dc & Amask) >> Ashift;

                                                 }

                                         }
                                 }
                        }
                 }
                 break;
         }
         return (0);
 }

 int Renderer::filledRectAlpha(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
 {
         Uint8 alpha;
         Uint32 mcolor;
         int result = 0;

         /*
         * Lock the surface
         */
         if (SDL_MUSTLOCK(dst)) {
                 if (SDL_LockSurface(dst) < 0) {
                         return (-1);
                 }
         }

         /*
         * Setup color
         */
         alpha = color & 0x000000ff;
         mcolor =
                 SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
                 (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

         result = _filledRectAlpha(dst, x1, y1, x2, y2, mcolor, alpha);

         /*
         * Unlock the surface
         */
         if (SDL_MUSTLOCK(dst)) {
                 SDL_UnlockSurface(dst);
         }

         return (result);
 }

int Renderer::_HLineAlpha(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color)
{
         return (filledRectAlpha(dst, x1, y, x2, y, color));
}
int Renderer::hlineColor(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color)
{
         Sint16 left, right, top, bottom;
         Uint8 *pixel, *pixellast;
         int dx;
         int pixx, pixy;
         Sint16 xtmp;
         int result = -1;
         Uint8 *colorptr;
         Uint8 color3[3];

         /*
         * Check visibility of clipping rectangle
         */
         if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
                 return(0);
         }

         /*
         * Swap x1, x2 if required to ensure x1<=x2
         */
         if (x1 > x2) {
                 xtmp = x1;
                 x1 = x2;
                 x2 = xtmp;
         }

         /*
         * Get clipping boundary and
         * check visibility of hline
         */
         left = dst->clip_rect.x;
         if (x2<left) {
                 return(0);
         }
         right = dst->clip_rect.x + dst->clip_rect.w - 1;
         if (x1>right) {
                 return(0);
         }
         top = dst->clip_rect.y;
         bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
         if ((y<top) || (y>bottom)) {
                 return (0);
         }

         /*
         * Clip x
         */
         if (x1 < left) {
                 x1 = left;
         }
         if (x2 > right) {
                 x2 = right;
         }

         /*
         * Calculate width difference
         */
         dx = x2 - x1;


         if ((color & 255) == 255) {


                 colorptr = (Uint8 *) & color;
                 if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                         color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
                 } else {
                         color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
                 }

                 /*
                 * Lock the surface
                 */
                 if (SDL_MUSTLOCK(dst)) {
                         if (SDL_LockSurface(dst) < 0) {
                                 return (-1);
                         }
                 }

                 /*
                 * More variable setup
                 */
                 pixx = dst->format->BytesPerPixel;
                 pixy = dst->pitch;
                 pixel = ((Uint8 *) dst->pixels) + pixx * (int) x1 + pixy * (int) y;

                 /*
                 * Draw
                 */
                 switch (dst->format->BytesPerPixel) {
                 case 1:
                         memset(pixel, color, dx + 1);
                         break;
                 case 2:
                         pixellast = pixel + dx + dx;
                         for (; pixel <= pixellast; pixel += pixx) {
                                 *(Uint16 *) pixel = color;
                         }
                         break;
                 case 3:
                         pixellast = pixel + dx + dx + dx;
                         if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                                 color3[0] = (color >> 16) & 0xff;
                                 color3[1] = (color >> 8) & 0xff;
                                 color3[2] = color & 0xff;
                         } else {
                                 color3[0] = color & 0xff;
                                 color3[1] = (color >> 8) & 0xff;
                                 color3[2] = (color >> 16) & 0xff;
                         }
                         for (; pixel <= pixellast; pixel += pixx) {
                                 memcpy(pixel, color3, 3);
                         }
                         break;
                 default:                /* case 4 */
                         dx = dx + dx;
                         pixellast = pixel + dx + dx;
                         for (; pixel <= pixellast; pixel += pixx) {
                                 *(Uint32 *) pixel = color;
                         }
                         break;
                 }

                 /*
                 * Unlock surface
                 */
                 if (SDL_MUSTLOCK(dst)) {
                         SDL_UnlockSurface(dst);
                 }

                 /*
                 * Set result code
                 */
                 result = 0;

         } else {

                 /*
                 * Alpha blending blit
                 */
                 result = _HLineAlpha(dst, x1, x1 + dx, y, color);
         }

         return (result);
 }

int Renderer::drawPolygonColorMT(SDL_Surface * dst, const int * vx, const int * vy, int n, Uint32 color, int **polyInts, int *polyAllocated)
 {
         int result;
         int i;
         int y, xa, xb;
         int miny, maxy;
         int x1, y1;
         int x2, y2;
         int ind1, ind2;
         int ints;
         int *gfxPrimitivesPolyInts = NULL;
         int *gfxPrimitivesPolyIntsNew = NULL;
         int gfxPrimitivesPolyAllocated = 0;


         if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
                 return(0);
         }


         if (vx == NULL) {
                 return (-1);
         }
         if (vy == NULL) {
                 return (-1);
         }


         if (n < 3) {
                 return -1;
         }


         if ((polyInts==NULL) || (polyAllocated==NULL)) {
                 /* Use global cache */
                 gfxPrimitivesPolyInts = mPrimitivesPolyIntsGlobal;
                 gfxPrimitivesPolyAllocated = mPrimitivesPolyAllocatedGlobal;
         } else {
                 /* Use local cache */
                 gfxPrimitivesPolyInts = *polyInts;
                 gfxPrimitivesPolyAllocated = *polyAllocated;
         }


         if (!gfxPrimitivesPolyAllocated) {
                 gfxPrimitivesPolyInts = (int *) malloc(sizeof(int) * n);
                 gfxPrimitivesPolyAllocated = n;
         } else {
                if (gfxPrimitivesPolyAllocated < n) {
                         gfxPrimitivesPolyIntsNew = (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
                         if (!gfxPrimitivesPolyIntsNew) {
                                 if (!gfxPrimitivesPolyInts) {
                                         free(gfxPrimitivesPolyInts);
                                         gfxPrimitivesPolyInts = NULL;
                                 }
                                 gfxPrimitivesPolyAllocated = 0;
                         } else {
                                 gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
                                 gfxPrimitivesPolyAllocated = n;
                         }
                 }
         }


         if (gfxPrimitivesPolyInts==NULL) {
                 gfxPrimitivesPolyAllocated = 0;
         }


         if ((polyInts==NULL) || (polyAllocated==NULL)) {
                 mPrimitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
                 mPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
         } else {
                 *polyInts = gfxPrimitivesPolyInts;
                 *polyAllocated = gfxPrimitivesPolyAllocated;
         }


         if (gfxPrimitivesPolyInts==NULL) {
                 return(-1);
         }


         miny = vy[0];
         maxy = vy[0];
         for (i = 1; (i < n); i++) {
                 if (vy[i] < miny) {
                         miny = vy[i];
                 } else if (vy[i] > maxy) {
                         maxy = vy[i];
                 }
         }


         result = 0;
         for (y = miny; (y <= maxy); y++) {
                 ints = 0;
                 for (i = 0; (i < n); i++) {
                         if (!i) {
                                 ind1 = n - 1;
                                 ind2 = 0;
                         } else {
                                 ind1 = i - 1;
                                 ind2 = i;
                         }
                         y1 = vy[ind1];
                         y2 = vy[ind2];
                         if (y1 < y2) {
                                 x1 = vx[ind1];
                                 x2 = vx[ind2];
                         } else if (y1 > y2) {
                                 y2 = vy[ind1];
                                 y1 = vy[ind2];
                                 x2 = vx[ind1];
                                 x1 = vx[ind2];
                         } else {
                                 continue;
                         }
                         if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) ) {
                                 gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
                         }
                 }

                 qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

                 for (i = 0; (i < ints); i += 2) {
                         xa = gfxPrimitivesPolyInts[i] + 1;
                         xa = (xa >> 16) + ((xa & 32768) >> 15);
                         xb = gfxPrimitivesPolyInts[i+1] - 1;
                         xb = (xb >> 16) + ((xb & 32768) >> 15);
                         result |= hlineColor(dst, xa, xb, y, color);
                 }
         }

         return (result);
 }
void Renderer::drawPolygon(SDL_Surface * aScreen,
							const int * x, const int * y,
							int aSize, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	drawPolygonColorMT(aScreen, x, y, aSize, ((Uint32) r << 24) |
			((Uint32) g << 16) | ((Uint32) b << 8) |
			(Uint32) a, NULL, NULL);
}
