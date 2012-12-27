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


#include "Map.h"
#include <vector>
Map::Map(std::string aFile)
{
	mFile=aFile;
	parseMyFile();

}

Map::~Map()
{
	delete mInitialMap;
}
std::vector<string> split ( string &chaine, char c )
{
    int size = chaine.size();
    int r = 0;
    std::vector<string> v;
    for (int i = 0; i < size; i++)
    {
	if (chaine[i] == c)
	{
	    v.push_back(chaine.substr(r, i - r));
	    r = i + 1;
	}
    }
    v.push_back(chaine.substr(r, size - r));
    return v;
}

void Map::parseMyFile()
{
	  string aStringLineNumber,aStringColumnNumber;
	  ifstream aFile;
	  aFile.open (mFile.c_str(), ifstream::in);
	  if (aFile.is_open())
	  {
	      getline(aFile,aStringLineNumber);
	      stringstream aSLN(aStringLineNumber);
	      int aLineNumber;
	      aSLN >> aLineNumber;

	      getline(aFile,aStringColumnNumber);
	      stringstream aScale(aStringColumnNumber);
	      int aColumnNumber;
	      aScale >> aColumnNumber;

	      getline(aFile,aStringColumnNumber);
	      stringstream aSCN(aStringColumnNumber);
	      aSCN >> scale;
	      mInitialMap = new TakeALook::T_Matrix<double>(aLineNumber,aColumnNumber);
	      for(int i = 0; i<aLineNumber;i++)
	      {
	    	  string temp;
    		  getline(aFile,temp);
    		  std::vector<string> content=split(temp, ' ');
	    	  for(int j = 0;j<aColumnNumber;j++)
	    	  {
				  stringstream aSCN(content[j]);
				  int high;
				  aSCN >> high;
				  mInitialMap->P[i][j]=high;
	    	  }
	      }
	      getline(aFile,aStringColumnNumber);
	      stringstream mp(aStringColumnNumber);
	      int nbMaps;
	      mp >> nbMaps;
	      for(int i = 0; i<nbMaps;i++)
	      {
	    	  string temp;
    		  getline(aFile,temp);
    		  std::vector<string> content=split(temp, ' ');
    	      stringstream b1(content[0]);
    	      int borne1;
    	      b1 >> borne1;

    	      stringstream b2(content[1]);
    	      int borne2;
    	      b2 >> borne2;

    	      stringstream r(content[2]);
    	      int rc;
    	      r >> rc;

    	      stringstream g(content[3]);
    	      int gc;
    	      g >> gc;

    	      stringstream b(content[4]);
    	      int bc;
    	      b >> bc;

    	      stringstream a(content[5]);
    	      int ac;
    	      a >> ac;

    	      TALColor newColor;
    	      newColor.r=rc;
    	      newColor.b=bc;
    	      newColor.g=gc;
    	      newColor.a=ac;
    	      HRange range(borne1,borne2);
    	      colorMap[range]=newColor;
	      }
	      aFile.close();
	  }
	  else
	  {
		  cout << "Unable to open file";
	  }

}
TALColor Map::getColor(int h)
{
	std::map<HRange ,TALColor>::iterator it;
	for(it=colorMap.begin();it!=colorMap.end();it++)
	{
		if((it->first.l<=h)&&(it->first.h>=h))
		{
			return it->second;

		}
	}
	TALColor a;
	return a;
}

void Map::rafiner()
{
	scale*=2;
	T_Matrix<double> * tempMap = new TakeALook::T_Matrix<double>(mInitialMap->dimRows*2-1,
															mInitialMap->dimColumns*2 -1);
	int nbL=mInitialMap->dimRows*2-2;
	int nbC=mInitialMap->dimColumns*2-2;
	for(int i=0;i<mInitialMap->dimRows;i++)
	{
		for(int j=0;j<mInitialMap->dimColumns;j++)
		{
			tempMap->P[i*2][j*2]=mInitialMap->P[i][j];
		}
	}

	for(int i=1;i<(mInitialMap->dimRows*2-2);i+=2)
	{
		for(int j=1;j<(mInitialMap->dimColumns*2-2);j+=2)
		{
			tempMap->P[i][j]=(tempMap->P[i-1][j-1]+tempMap->P[i+1][j-1]+tempMap->P[i-1][j+1]+tempMap->P[i+1][j+1])/4;
		}
	}
	for(int i=2;i<(mInitialMap->dimRows*2-2);i+=2)
	{
		for(int j=1;j<(mInitialMap->dimColumns*2-2);j+=2)
		{
			tempMap->P[i][j]=(tempMap->P[i-1][j]+tempMap->P[i][j-1]+tempMap->P[i][j+1]+tempMap->P[i][j+1])/4;
		}
	}
	for(int i=1;i<(mInitialMap->dimRows*2-2);i+=2)
	{
		for(int j=2;j<(mInitialMap->dimColumns*2-2);j+=2)
		{
			tempMap->P[i][j]=(tempMap->P[i-1][j]+tempMap->P[i][j-1]+tempMap->P[i][j+1]+tempMap->P[i][j+1])/4;
		}
	}
	for(int j=1;j<(mInitialMap->dimColumns*2-2);j+=2)
	{
		tempMap->P[0][j]=(tempMap->P[1][j]+tempMap->P[0][j-1]+tempMap->P[0][j+1])/3;
	}
	for(int j=1;j<(mInitialMap->dimColumns*2-2);j+=2)
	{
		tempMap->P[nbL][j]=(tempMap->P[nbL-1][j]+tempMap->P[nbL][j-1]+tempMap->P[nbL][j+1])/3;
	}

	for(int i=1;i<(mInitialMap->dimRows*2-2);i+=2)
	{
		tempMap->P[i][0]=(tempMap->P[i][1]+tempMap->P[i-1][0]+tempMap->P[i+1][0])/3;
	}
	for(int i=1;i<(mInitialMap->dimRows*2-2);i+=2)
	{
		tempMap->P[i][nbC]=(tempMap->P[i][nbC-1]+tempMap->P[i-1][nbC]+tempMap->P[i+1][nbC])/3;
	}
	delete mInitialMap;
	mInitialMap=tempMap;
}


