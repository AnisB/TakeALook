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


#ifndef CAMERA_H_
#define CAMERA_H_

#include "MovableObject.h"

class Camera : public MovableObject {
public:
	Camera(Vector3 aPosition, Vector3 aDirection);
	virtual ~Camera();
	void fd();
	void bd();
	void ld();
	void rd();
	void u();
	void d();
	void show();
	Vector3 & getPosition() { return mPosition;}
	Vector3 & getDirection() {return mDirection;}
	Vector3 & getUpVector() {return mUpVector;}
	double focalDistance ;
	void motion(int x, int y);
protected:
	Vector3 mPosition;
	Vector3 mDirection;
	Vector3 mUpVector;

};

#endif /* CAMERA_H_ */
