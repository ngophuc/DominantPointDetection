/////////////////////////////////////////////////////////////////////////////
// Display the Noise level obtained after multi scales analysis 
//////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ImaGene/base/Proxy.h"
#include "ImaGene/dgeometry2d/C4CGeometry.h"
#include "ImaGene/dgeometry2d/C4CSegmentPencil.h"
#include "ImaGene/base/Vector2i.h"
#include "ImaGene/base/Arguments.h"
#include "ImaGene/base/StandardArguments.h"
#include "ImaGene/mathutils/Mathutils.h"
#include "ImaGene/mathutils/Statistics.h"
#include "ImaGene/timetools/Clock.h"
#include "ImaGene/dgeometry2d/C4CTangentialCover.h"
#include "ImaGene/helper/C4CTangentialCoverGeometry.h"
#include "ImaGene/dgeometry2d/FreemanChain.h"
#include "ImaGene/dgeometry2d/FreemanChainTransform.h"
#include "ImaGene/dgeometry2d/C4CIteratorOnFreemanChain.h"
#include "ImaGene/digitalnD/C4CIteratorOnFreemanChainSurface.h"
#include "ImaGene/digitalnD/KnSpace.h"
#include "ImaGene/digitalnD/C4CIteratorOnSurface.h"
#include "ImaGene/helper/ShapeHelper.h"
#include "ImaGene/helper/MultiscaleProfile.h"
#include "ImaGene/helper/DrawingXFIG.h"
#include "ImaGene/helper/CurveVariationsHelper.h"
#include "ImaGene/mathutils/SimpleLinearRegression.h"



using namespace std;
using namespace ImaGene;


static Arguments args;



struct ImagePGM{
  uint width;
  uint height;
  uint maxValue;
  uint *tabImage;
};


struct ImagePPM{
  uint width;
  uint height;
  uint maxValue;
  uint * tabImageR;
  uint * tabImageG;
  uint * tabImageB;
};



void exportPGM(const char* name, ImagePGM image);
ImagePGM importPGM(const char * name);


void exportPPM(const char* name, ImagePPM image);
ImagePPM importPPM( const  char* name);



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// M A I N
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int
main( int argc, char** argv ) 
{
  // -------------------------------------------------------------------------
  // Prepare arguments.
  StandardArguments::addIOArgs( args, true, false );
 
  
  

  args.addOption("-srcA", "-srcA <sourceImage>" , " ");
  args.addOption("-srcB", "-srcB <sourceImage>" , " ");

  
  
  if ( ( argc <= 1 )|| ! args.readArguments( argc, argv ))
    {
      cerr << args.usage( "composeImage", 
			  "composeImage <image1.ppm> <image2.ppm>."
			  ,"" ) << endl;
      return 1;
    }

  
  string str1 = args.getOption("-srcA")->getValue(0);
  string str2 = args.getOption("-srcB")->getValue(0);
  const char * ch1 =str1.c_str();
  const char * ch2 =str2.c_str();
  
  
  ImagePPM image1 =  importPPM(ch1);
  ImagePPM image2 =  importPPM(ch2);
  ImagePPM imageComposed;
  imageComposed.width=image1.width;
  imageComposed.height=image1.height;
  imageComposed.tabImageR = new uint [image1.width*image1.height];
  imageComposed.tabImageG = new uint [image1.width*image1.height];
  imageComposed.tabImageB = new uint [image1.width*image1.height];
  uint max =0;
  
  
  for(int i=0; i<image2.height; i++){
    for(int j=0; j<image2.width; j++){
      uint indice = i*image2.width+j;
      if(image2.tabImageR[indice]!=0){
	imageComposed.tabImageR[indice] = image1.tabImageR[indice]/(image2.tabImageR[indice]); 
	imageComposed.tabImageG[indice] =0;
	imageComposed.tabImageB[indice] =0;
	
      }
      
      if(max < imageComposed.tabImageR[indice]){
	max = imageComposed.tabImageR[indice];
      } 
    }
  }
  
  
  
  imageComposed.maxValue = max;


  exportPPM("composed.ppm", imageComposed);
  
}
  
  

  

	        








//---------------------------
// Sauvegarde format PGM/PPM 




ImagePGM importPGM(const  char * name){

    
  ifstream in;
  in.open(name, ifstream::in);
    
  
  ImagePGM imageImported;
  string str;
  getline( in, str );
  if ( ! in.good() ) return imageImported;
  if ( str != "P5" ) return imageImported;
  do
    {
      getline( in, str );
      if ( ! in.good() ) return imageImported;
    }
  while ( str[ 0 ] == '#' );
  istringstream str_in( str );
  str_in >> imageImported.width >> imageImported.height;
  in >> noskipws;
  getline( in, str );
  istringstream str2_in( str );
  int max_value;
  
  str2_in >> max_value;
  imageImported.maxValue=max_value;
  imageImported.tabImage = new uint[imageImported.width*imageImported.height];  
  
  for(int i=0; i<imageImported.width*imageImported.height; i++){
    unsigned char c; 
    in >> c;
    imageImported.tabImage[i] = (uint)c;    
  }  
  return imageImported;
}







ImagePPM importPPM(const  char* name){

  ifstream in;
  in.open(name, ifstream::in);

  ImagePPM imageImported;
  string str;
  getline( in, str );
  if ( ! in.good() ) return imageImported;
  if ( str != "P6" ) return imageImported;
  do
    {
      getline( in, str );
      if ( ! in.good() ) return imageImported;
    }
  while ( str[ 0 ] == '#' );
  istringstream str_in( str );
  str_in >> imageImported.width >> imageImported.height;
  in >> noskipws;
  getline( in, str );
  istringstream str2_in( str );
  int max_value;
  
  str2_in >> max_value;
  imageImported.maxValue=max_value;
  imageImported.tabImageR = new uint[imageImported.width*imageImported.height];  
  imageImported.tabImageG = new uint[imageImported.width*imageImported.height];  
  imageImported.tabImageB = new uint[imageImported.width*imageImported.height];  
  
  for(int i=0; i<imageImported.width*imageImported.height; i++){
    unsigned char c; 
    in >> c;
    imageImported.tabImageR[i] = (uint)c;    
    in >> c;
    imageImported.tabImageG[i] = (uint)c;    
    in >> c;
    imageImported.tabImageB[i] = (uint)c;    
  }  
  return imageImported;
}




void exportPGM(const char* name, ImagePGM image){
  ofstream out;
  out.open(name, ios_base::out);

  out << "P5" << endl
      << "# CREATOR: addGaussianNoisePGM " 
      << "(kerautret@loria.fr)" << endl;
  out << image.width << " " << image.height << endl
      << image.maxValue << endl;
  
  
  for(int i=0; i<image.width*image.height; i++){
    out << (unsigned char)(image.tabImage[i]) ;    
  }
  
  out << endl;
}





void exportPPM(const char* name, ImagePPM image){

  ofstream out;
  out.open(name, ios_base::out);
    
  out << "P6" << endl
      << "# CREATOR: displayNoise " 
      << "(kerautret@loria.fr)" << endl;
  out << image.width << " " << image.height << endl
      << image.maxValue << endl;
  
  
  for(int i=0; i<image.width*image.height; i++){
    out << (unsigned char)(image.tabImageR[i])<< (unsigned char)(image.tabImageG[i])
	<< (unsigned char)(image.tabImageB[i]);    
  }
  out << endl;
}

