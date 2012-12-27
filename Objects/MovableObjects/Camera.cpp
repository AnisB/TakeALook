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

#include <iostream>
#include "Camera.h"
using namespace std;
Camera::Camera(Vector3 aPosition, Vector3 aDirection)
{
	mPosition=aPosition;
	mDirection=aDirection;
	Vector3 tmp =aDirection-aPosition;
	//mUpVector =tmp.Cross(Vector3(0,0,1));
	mUpVector=Vector3(2000,2000,0);
	focalDistance=1000;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::fd()
{
	Vector3 tmp=(mDirection -mPosition);
	tmp=tmp.Cross(mUpVector);
	tmp.Normalize();
	mPosition+=tmp*100;
}

void Camera::bd()
{
	Vector3 tmp=(mDirection -mPosition);
	tmp=tmp.Cross(mUpVector);
	tmp.Normalize();
	mPosition-=tmp*100;

}

void Camera::rd()
{
	Vector3 tmp=(mDirection -mPosition);
	tmp.Normalize();
	mPosition-=tmp*100;

}

void Camera::ld()
{
	Vector3 tmp=(mDirection -mPosition);
	tmp.Normalize();
	mPosition+=tmp*100;
}
void Camera::u()
{

	mDirection-=(Vector3(0,100,0));

}

void Camera::d()
{
	mDirection-=(Vector3(0,-100,00));

}

void Camera::show()
{
	cout<<"Position"<<endl;
	mPosition.debugDisplay();

	cout<<"Direction"<<endl;
	mDirection.debugDisplay();

	cout<<"mUpVector"<<endl;
	mUpVector.debugDisplay();
}
void Camera::motion(int ax, int ay)
{
	double x= (double)0.05f*ax;
	double y= (double)0.005f*ay;
	cout<<x<<y<<endl;
	Vector3 tmp=(mDirection -mPosition);
	tmp.Normalize();
	mPosition+=tmp*20*x;
	//mDirection=Vector3(mDirection.GetX()+10,mDirection.GetY()+10,mDirection.GetZ());


	if((y>0 && (mUpVector*Vector3(1,0,0)-mUpVector.Norm())<0.1)
			||(y<0 && (mUpVector*Vector3(1,0,0)+mUpVector.Norm())>0.1))
	{
		mDirection+=mUpVector*-y;
	}
}

