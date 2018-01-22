/*
 *  Final Project
 */
#include "CSCIx229.h"
#include "math.h"
unsigned int texture[20];
int zh = 90;
int th = 0;
double lx = 0;
double ly = 0;
double lz = -1.0;
int dim = 1.0;
int light = 1;
double xp = 0;
double yp = 0;
double zp = 1;
double asp=1;           //  Aspect ratio
int at0=50;             //  Constant  attenuation %
int at1=40;             //  Linear    attenuation %
int at2=10;             //  Quadratic attenuation %
float Exp=30;           //  Spot exponent
float sco=10;           //  Spot cutoff angle
double door_Ypos = 0.0;
double door_Angle = 0.0;
int mode = 0;
// Light values
int emission  =   10;   // Emission intensity (%)
int ambient   =  30;    // Ambient intensity (%)
int diffuse   = 100;    // Diffuse intensity (%)
int specular  =   50;   // Specular intensity (%)
int shininess =   0;    // Shininess (power of two)
float shiny   =   1;    // Shininess (value)

static void Vertex(double th,double ph)
{
  double x = Sin(th)*Cos(ph);
  double y = Cos(th)*Cos(ph);
  double z =         Sin(ph);
  glNormal3d(x,y,z);
  glVertex3d(x,y,z);
}

static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double r, double g, double b,
                 double phi, double theta, double psi)
{

  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  //  Offset
  glTranslated(x,y,z);
  glRotated(phi,1,0,0);
  glRotated(theta,0,1,0);
  glRotated(psi,0,0,1);
  glScaled(dx,dy,dz);
  glColor3f(r, g, b);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
  //  Cube
  // Front
  glBegin(GL_QUADS);
  glNormal3f(0, 0, +1);
  glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
  glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
  glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
  glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
  //  Back
  glNormal3f(0, 0, -1);
  glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
  glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
  //  Right
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
  glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
  glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
  //  Left
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
  glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
  glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
  //  Top
  glNormal3f(0, 1, 0);
  glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
  glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
  glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
  glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
  //  Bottom
  glNormal3f(0, -1, 0);
  glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
  glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
  //  End
  glEnd();
}

static void cube2(double x,double y,double z,
                 double dx,double dy,double dz,
                 double r, double g, double b,
                 double phi, double theta, double psi, int rep)
{
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
  //  Offset
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(phi,1,0,0);
  glRotated(theta,0,1,0);
  glRotated(psi,0,0,1);
  glScaled(dx,dy,dz);
  glColor3f(r, g, b);
  //  Cube
  // Front
  glBegin(GL_QUADS);

  glNormal3f(0, 0, +1);
  glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
  glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
  glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
  glTexCoord2f(0,rep); glVertex3f(-1,+1, 1);
  //  Back
  glNormal3f(0, 0, -1);
  glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
  glTexCoord2f(0,rep); glVertex3f(+1,+1,-1);
  //  Right
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
  glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
  glTexCoord2f(0,rep); glVertex3f(+1,+1,+1);
  //  Left
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
  glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
  glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
  //  Top
  glNormal3f(0, 1, 0);
  glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
  glTexCoord2f(rep,0); glVertex3f(+1,+1,+1);
  glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
  glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
  //  Bottom
  glNormal3f(0, -1, 0);
  glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
  glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
  glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
  glTexCoord2f(0,rep); glVertex3f(-1,-1,+1);
  //  End
  glEnd();
  glPopMatrix();
}

static void sphere(double x,double y,double z,double s, double r, double g, double b)
{
  const int d=5;
  int th,ph;
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  //  Save transformation
  glPushMatrix();
  //  Offset and scale
  glTranslated(x,y,z);
  glScaled(s,s,s);
  glColor3f(r, g, b);

  glMaterialf(GL_FRONT,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT,GL_EMISSION,black);
  //  Latitude bands
  for (ph = -90; ph < 90; ph += d)
  {
    glBegin(GL_QUAD_STRIP);
    for (th=0; th<=360; th+=d)
    {
       Vertex(th, ph);
       Vertex(th, ph+d);
    }
    glEnd();
  }
  //  Undo transformations
  glPopMatrix();
}

static void drawCylinder(double x, double y, double z, 
                          double dx,double dy,double dz,
                          double phi, double theta, double psi)
{
  float white[] = {1, 1, 1, 1.0};
  float black[]  = {0.0,0.0,0,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(dx,dy,dz);
  int th_table;
  //  Cap
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0,0,1);
  glTexCoord2f(0.5,0.5);
  glVertex3f(0,0,1);
  for (th_table=0;th_table<=360;th_table+=10){
    glNormal3f(Cos(th_table),Sin(th_table),1);
    glTexCoord2f(1/2*Cos(th_table)+0.5,1/2*Sin(th_table)+0.5);
    glVertex3f(Cos(th_table),Sin(th_table),1);
    glNormal3f(Cos(th_table),Sin(th_table),0);
    glVertex3f(Cos(th_table),Sin(th_table),0);
  }
  glEnd();
  //  Sides
  glBegin(GL_QUAD_STRIP);
  for (th_table=0;th_table<=360;th_table+=15)
  {
    const float tc = th_table/(float)360;
    glNormal3f(Cos(th_table),Sin(th_table),0);
    glTexCoord2f(1*tc, 0); glVertex3f(Cos(th_table),Sin(th_table),1);
    glTexCoord2f(1*tc, 1); glVertex3f(Cos(th_table),Sin(th_table),0);
  }
  glEnd();
}

static void table(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(0, 0, 0, 0.18, 0.01, 0.3, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix(); 
  //feet
  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.17, -0.16, 0.29, 0.01, 0.16, 0.01,0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.17, -0.16, -0.29, 0.01, 0.16, 0.01,  0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.17, -0.16, -0.29, 0.01, 0.16, 0.01, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.17, -0.16, 0.29, 0.01, 0.16, 0.01, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void table2(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(0, 0, 0, 0.1, 0.01, 0.2, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  //feet
  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.09, -0.08, 0.19, 0.01, 0.08, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.09, -0.08, -0.19, 0.01, 0.08, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.09, -0.08, 0.19, 0.01, 0.08, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.09, -0.08, -0.19, 0.01, 0.08, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void bench(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(0, 0, 0, 0.1, 0.01, 0.3, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  //feet
  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.09, -0.06, 0.29, 0.01, 0.06, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.09, -0.06, -0.29, 0.01, 0.06, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.09, -0.06, 0.29, 0.01, 0.06, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[8]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.09, -0.06, -0.29, 0.01, 0.06, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void chair(double x, double y, double z, double ds, double phi, double theta, double psi)
{

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2,1);
 
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(0, 0, 0, 0.07, 0.01, 0.07, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL); 
  //feet
  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.06, -0.09, 0.06, 0.01, 0.09, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.06, -0.09, -0.06, 0.01, 0.09, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.06, -0.0, 0.06, 0.01, 0.17, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.06, -0.0, -0.06, 0.01, 0.17, 0.01,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.06, 0.09, 0.033, 0.005, 0.09, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.06, 0.09, -0.033, 0.005, 0.09, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL); 

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(-0.06, 0.18, 0, 0.01, 0.01, 0.07, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL); 


  glDisable(GL_TEXTURE_2D);
}

static void pic1(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.5,1);
  glPolygonOffset(1,1);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[12]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0, 0, 0.15, 0.1, 0.001, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[13]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.0013, 0, 0, 0.117, 0.08, 0.0011, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL); 
  glDisable(GL_TEXTURE_2D);
}

static void pic2(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.5,1);
  glPolygonOffset(1,1);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[15]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0, 0, 0.05, 0.07, 0.001, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[16]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.0013, 0, 0, 0.04, 0.06, 0.0011, 0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL); 
  glDisable(GL_TEXTURE_2D);
}


static void round_table(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  drawCylinder(0, 0, 0, 0.05, 0.05, 0.015, 90, 0, 0);
  glPopMatrix(); 
  //feet
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, -0.035, -0.04, 0.005, 0.02, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, -0.035, 0.04, 0.005, 0.02, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.04, -0.035, 0, 0.005, 0.02, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.04, -0.035, 0, 0.005, 0.02, 0.005,0.960784, 1, 0.980392,0, 0, 0);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

static void clock(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[7]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);  
  cube(0, 0, 0, 0.04, 0.04, 0.01, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix(); 

  glBindTexture(GL_TEXTURE_2D,texture[18]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);  
  cube(0, 0, 0.01, 0.04, 0.04, 0.001, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix(); 
  glDisable(GL_TEXTURE_2D);
}

static void block(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);  
  cube(0, 0, 0, 0.1, 0.01, 0.03, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix(); 

  glDisable(GL_TEXTURE_2D);
}

static void bottle(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  // Save transformation
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0, 0, 0.015, 0.015, 0.015, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.011, 0, 0.018, 0.018, 0.018, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.03, 0, 0.021, 0.021, 0.021, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.04, 0, 0.02, 0.02, 0.02, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.05, 0, 0.016, 0.016, 0.016, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.06, 0, 0.013, 0.013, 0.013, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.067, 0, 0.01, 0.01, 0.01, 1, 0, 0, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.087, 0, 0.012, 0.009, 0.012, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.0915, 0, 0.011, 0.009, 0.011, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix();
}

void ball(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,texture[5]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);  
  sphere(0, 0, 0, 6,  0.854902, 0.647059, 0.12549);
  glPopMatrix(); 
  glDisable(GL_TEXTURE_2D);
}

static void cup(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  // Save transformation
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0, 0, 0.015, 0.003, 0.015, 1, 0.843137, 0, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.005, 0, 0.013, 0.003, 0.013, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.008, 0, 0.01, 0.003, 0.01, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.01, 0, 0.008, 0.005, 0.008, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.03, 0, 0.015, 0.015, 0.015, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();
  //ears
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.016, 0.02, 0, 0.002, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.016, 0.02, 0, 0.002, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.018, 0.022, 0, 0.002, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.018, 0.022, 0, 0.002, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.02, 0.028, 0, 0.002, 0.006, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.02, 0.028, 0, 0.002, 0.006, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.018, 0.034, 0, 0.004, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.018, 0.034, 0, 0.004, 0.002, 0.002, 1, 0.843137, 0, 0, 0, 0);
  glPopMatrix();
  //word
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.03, 0.0155, 0.002, 0.011, 0.002, 0.545098, 0, 0, 0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.002, 0.039, 0.0155, 0.002, 0.002, 0.002, 0.545098, 0, 0, 0, 0, 0);
  glPopMatrix();

}

static void computer(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  // Save transformation
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0, 0, 0.063, 0.0025, 0.04, 0.662745, 0.662745, 0.662745, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.038, -0.038, 0.063, 0.04, 0.0025, 0.662745, 0.662745, 0.662745, 0, 0, 0); 
  glPopMatrix();

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, 0.041, -0.037, 0.06, 0.032, 0.0025, 0, 0, 0, 0, 0, 0); 
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[9]);
  glPushMatrix();
  // Offset and scale
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  //table surface 
  cube(0.0011, 0.001, -0.01, 0.056, 0.0025, 0.02, 0.960784, 1, 0.980392, 0, 0, 0); 
  glPopMatrix(); 
  glDisable(GL_TEXTURE_2D);
}

static void cabinet(double x, double y, double z, double ds, double phi, double theta, double psi)
{
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2,1);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, -0.1, 0, 0.2, 0.01, 0.06, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL);

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, -0.25, 0, 0.2, 0.01, 0.06, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL);

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0, -0.4, 0, 0.2, 0.01, 0.06, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL);

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(0.15, -0.3, 0, 0.01, 0.2, 0.06, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL);

  glPolygonOffset(2,1);
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.15, -0.3, 0, 0.01, 0.2, 0.06, 0.960784, 1, 0.980392, 0, 0, 0);
  glPopMatrix(); 
  glDisable(GL_POLYGON_OFFSET_FILL);

  glDisable(GL_TEXTURE_2D);
}

static void fireStove(double x, double y, double z, double ds, double phi, double theta, double psi)
{

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube(-0.01, -0.3, 0.01, 0.16, 0.16, 0.001, 0.411765 ,0.411765 ,0.411765, 0, 0, 0); 
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL);

  glPolygonOffset(2,1);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
  // Save transformation
  glBindTexture(GL_TEXTURE_2D,texture[19]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube2(0, -0.1, 0, 0.21, 0.03, 0.08, 0.960784, 1, 0.980392, 0, 0, 0,2);
  glPopMatrix(); 

  glBindTexture(GL_TEXTURE_2D,texture[19]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube2(0.18, -0.26, 0, 0.03, 0.13, 0.08, 0.960784, 1, 0.980392, 0, 0, 0,2);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,texture[19]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube2(-0.18, -0.26, 0, 0.03, 0.13, 0.08, 0.960784, 1, 0.980392, 0, 0, 0,2);
  glPopMatrix(); 

  glBindTexture(GL_TEXTURE_2D,texture[19]);
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  cube2(0, -0.42, 0, 0.21, 0.03, 0.08, 0.960784, 1, 0.980392, 0, 0, 0,2);
  glPopMatrix(); 

  glDisable(GL_TEXTURE_2D);
}

//fire
#define MAX_PARTICLES 500   // Number of particles
typedef struct  // Create A Structure For Particle
{
  float life;  // Particle Life
  float fade;  // Fade Speed
  float x;  // X Position
  float y;  // Y Position
  float z;  // Z Position
  float xi;  // X Direction
  float yi;  // Y Direction
  float zi;  // Z Direction
}
particles;  // Particles Structure

particles particle[MAX_PARTICLES];  // Particle Array 

static void fire(double r, double g, double b){
  for (int loop=0; loop<MAX_PARTICLES; loop++)  // Loop Through All The Particles
  {
    float x=particle[loop].x; // Grab Our Particle X Position
    float y=particle[loop].y; // Grab Our Particle Y Position
    float z=particle[loop].z; // Grab Our Particle Z Position
    // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
    glColor4f(r, g, b,particle[loop].life);
    glBegin(GL_TRIANGLE_STRIP); // Build Quad From A Triangle Strip
    glTexCoord2f(1,1); glVertex3f(x+0.002f,y+0.006f,z); // Top Right
    glTexCoord2f(0,1); glVertex3f(x-0.002f,y+0.006f,z); // Bottom Right
    glTexCoord2f(1,0); glVertex3f(x+0.002f,y-0.006f,z); // Top Left
    glTexCoord2f(0,0); glVertex3f(x-0.002f,y-0.006f,z); // Bottom Left
    glEnd();  // Done Building Triangle Strip

    particle[loop].x+=particle[loop].xi/5000;  // Move On The X Axis By X Speed
    particle[loop].y+=particle[loop].yi/5000;  // Move On The Y Axis By Y Speed
    particle[loop].z+=particle[loop].zi/5000;  // Move On The Z Axis By Z Speed

    // Slow down the particles
    particle[loop].xi*=.97;  
    particle[loop].yi*=.97;
    particle[loop].zi*=.97;

    particle[loop].life-=particle[loop].fade; // Reduce Particles Life By 'Fade'

    if (particle[loop].life<0.05f)  // If Particle Is Burned Out
    {
      particle[loop].life=.5f; // Give It New Life
      particle[loop].fade=(rand()%100)/7500 + 0.0075f; // Random Fade Value
      particle[loop].x= 0;  // Center On X Axis
      particle[loop].y= 0;  // Center On Y Axis
      particle[loop].z= 0;  // Center On Z Axis
      float V = ((rand()%9))+1;
      float Angle = rand()%360;

      particle[loop].xi = sin(Angle) * V;
      particle[loop].yi = cos(Angle) / sin(Angle) * V ;
      particle[loop].zi = ((rand()%10)-5)/5;
    } 
  }
}

static void drawfire(double x, double y, double z, double ds, double phi, double theta, double psi, double r, double g, double b){
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);
  glRotated(psi, 0, 0, 1);
  glScaled(ds, ds, ds);
  fire(r, g, b);
  glPopMatrix();
}

static void Room(double D)
{
  int i,j;
  int num=128;
  double m = 1.0/num;
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  //  Sides
  //  Enable Polygon Offset
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.5,1);
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  //FIRST WALL(x=-D)
  glBindTexture(GL_TEXTURE_2D,texture[3]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1.0);
  //LOWER PART
  for (i=0;i<num;i++) //width
      for (j=0;j<num;j++) //height
      {
      //x direction have 4 texture, z direction have 2 texture, 2*D d is the size of room
      glTexCoord2d(6*m*(i+0),m*(j+0));  glVertex3f(2*D*m*(i+0)-D,D/2.5*m*(j+0)-D/2,-D);
      glTexCoord2d(6*m*(i+1),m*(j+0));  glVertex3f(2*D*m*(i+1)-D,D/2.5*m*(j+0)-D/2,-D);
      glTexCoord2d(6*m*(i+1),m*(j+1));  glVertex3f(2*D*m*(i+1)-D,D/2.5*m*(j+1)-D/2,-D);
      glTexCoord2d(6*m*(i+0),m*(j+1));  glVertex3f(2*D*m*(i+0)-D,D/2.5*m*(j+1)-D/2,-D);
      }
  glEnd();

  //UPPER PART
  glBindTexture(GL_TEXTURE_2D,texture[4]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1.0); 
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   

      glTexCoord2d(m*(i+0),m*(j+0));  glVertex3f(2*D*m*(i+0)-D,1.5*D/2.5*m*(j+0)-0.5*D/5,-D);
      glTexCoord2d(m*(i+1),m*(j+0));  glVertex3f(2*D*m*(i+1)-D,1.5*D/2.5*m*(j+0)-0.5*D/5,-D);
      glTexCoord2d(m*(i+1),m*(j+1));  glVertex3f(2*D*m*(i+1)-D,1.5*D/2.5*m*(j+1)-0.5*D/5,-D);
      glTexCoord2d(m*(i+0),m*(j+1));  glVertex3f(2*D*m*(i+0)-D,1.5*D/2.5*m*(j+1)-0.5*D/5,-D);
      }
  glEnd();
  //SECOND WALL(x=D)
  glBindTexture(GL_TEXTURE_2D,texture[3]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1.0);
  //LOWER PART
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {       
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(2*D*m*(i+0)-D,D/2.5*m*(j+0)-D/2,+D);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(2*D*m*(i+1)-D,D/2.5*m*(j+0)-D/2,+D);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(2*D*m*(i+1)-D,D/2.5*m*(j+1)-D/2,+D);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(2*D*m*(i+0)-D,D/2.5*m*(j+1)-D/2,+D);
      }
  glEnd();
  //UPPER PART
  glBindTexture(GL_TEXTURE_2D,texture[4]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1.0); 
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   

      glTexCoord2d(m*(i+0),m*(j+0));  glVertex3f(2*D*m*(i+0)-D,1.5*D/2.5*m*(j+0)-0.5*D/5,D);
      glTexCoord2d(m*(i+1),m*(j+0));  glVertex3f(2*D*m*(i+1)-D,1.5*D/2.5*m*(j+0)-0.5*D/5,D);
      glTexCoord2d(m*(i+1),m*(j+1));  glVertex3f(2*D*m*(i+1)-D,1.5*D/2.5*m*(j+1)-0.5*D/5,D);
      glTexCoord2d(m*(i+0),m*(j+1));  glVertex3f(2*D*m*(i+0)-D,1.5*D/2.5*m*(j+1)-0.5*D/5,D);
      }
  glEnd();
  //door 
  glPolygonOffset(1,1);
  glBindTexture(GL_TEXTURE_2D,texture[6]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
 
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {
      glTexCoord2d(m*(i+0),m*(j+0));  glVertex3f(0.6*D*m*(i+0)-D*(5.3/6.0),0.93*D*m*(j+0)-D/2,0.999*D);
      glTexCoord2d(m*(i+1),m*(j+0));  glVertex3f(0.6*D*m*(i+1)-D*(5.3/6.0),0.93*D*m*(j+0)-D/2,0.999*D);
      glTexCoord2d(m*(i+1),m*(j+1));  glVertex3f(0.6*D*m*(i+1)-D*(5.3/6.0),0.93*D*m*(j+1)-D/2,0.999*D);
      glTexCoord2d(m*(i+0),m*(j+1));  glVertex3f(0.6*D*m*(i+0)-D*(5.3/6.0),0.93*D*m*(j+1)-D/2,0.999*D);
    }
  glEnd();   
  glDisable(GL_POLYGON_OFFSET_FILL);    

  //FOURTH WALL WITH MIRROR
  glBindTexture(GL_TEXTURE_2D,texture[3]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  //LOWER PART
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {         
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-D,D/2.5*m*(j+0)-D/2,2*D*m*(i+0)-D);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-D,D/2.5*m*(j+0)-D/2,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-D,D/2.5*m*(j+1)-D/2,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-D,D/2.5*m*(j+1)-D/2,2*D*m*(i+0)-D);
      }
  glEnd();

  //UPPER PART
  glBindTexture(GL_TEXTURE_2D,texture[4]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0); 
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-D,0.5*D/5*m*(j+0)-0.5*D/5,2*D*m*(i+0)-D);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-D,0.5*D/5*m*(j+0)-0.5*D/5,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-D,0.5*D/5*m*(j+1)-0.5*D/5,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-D,0.5*D/5*m*(j+1)-0.5*D/5,2*D*m*(i+0)-D);
      }
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-D,D/4*m*(j+0)+D/4,2*D*m*(i+0)-D);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-D,D/4*m*(j+0)+D/4,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-D,D/4*m*(j+1)+D/4,2*D*m*(i+1)-D);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-D,D/4*m*(j+1)+D/4,2*D*m*(i+0)-D);
      }
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-D,D/4*m*(j+0),10*D/9*m*(i+0)-D);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-D,D/4*m*(j+0),10*D/9*m*(i+1)-D);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-D,D/4*m*(j+1),10*D/9*m*(i+1)-D);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-D,D/4*m*(j+1),10*D/9*m*(i+0)-D);
      }
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   
      glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-D,D/4*m*(j+0),4*D/9*m*(i+0)+5*D/9);
      glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-D,D/4*m*(j+0),4*D/9*m*(i+1)+5*D/9);
      glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-D,D/4*m*(j+1),4*D/9*m*(i+1)+5*D/9);
      glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-D,D/4*m*(j+1),4*D/9*m*(i+0)+5*D/9);
      }
  glEnd();

  //mirror frame
  glPolygonOffset(1,1);
  glBindTexture(GL_TEXTURE_2D,texture[10]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0); 

  for (i=0;i<num;i++)
    for (j=0;j<num;j++)
    {      
    glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-0.9999*D,D/4*m*(i+0),0.02*D*m*(j+1)+D/9-0.02*D);
    glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-0.9999*D,D/4*m*(i+0),0.02*D*m*(j+0)+D/9-0.02*D);
    glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-0.9999*D,D/4*m*(i+1),0.02*D*m*(j+0)+D/9-0.02*D);
    glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-0.9999*D,D/4*m*(i+1),0.02*D*m*(j+1)+D/9-0.02*D);
    }
  for (i=0;i<num;i++)
    for (j=0;j<num;j++)
    {      
    glTexCoord2f(6*m*(i+0),m*(j+1)); glVertex3f(-0.9999*D,D/4*m*(i+0),0.02*D*m*(j+1)+5*D/9);
    glTexCoord2f(6*m*(i+0),m*(j+0)); glVertex3f(-0.9999*D,D/4*m*(i+0),0.02*D*m*(j+0)+5*D/9);
    glTexCoord2f(6*m*(i+1),m*(j+0)); glVertex3f(-0.9999*D,D/4*m*(i+1),0.02*D*m*(j+0)+5*D/9);
    glTexCoord2f(6*m*(i+1),m*(j+1)); glVertex3f(-0.9999*D,D/4*m*(i+1),0.02*D*m*(j+1)+5*D/9);
    }
  for (i=0;i<num;i++)
    for (j=0;j<num;j++)
    {      
    glTexCoord2f(m*(i+0),6*m*(j+1)); glVertex3f(-0.9999*D,0.02*D*m*(i+0),4*D/9*m*(j+1)+D/9);
    glTexCoord2f(m*(i+0),6*m*(j+0)); glVertex3f(-0.9999*D,0.02*D*m*(i+0),4*D/9*m*(j+0)+D/9);
    glTexCoord2f(m*(i+1),6*m*(j+0)); glVertex3f(-0.9999*D,0.02*D*m*(i+1),4*D/9*m*(j+0)+D/9);
    glTexCoord2f(m*(i+1),6*m*(j+1)); glVertex3f(-0.9999*D,0.02*D*m*(i+1),4*D/9*m*(j+1)+D/9);
    }
  for (i=0;i<num;i++)
    for (j=0;j<num;j++)
    {      
    glTexCoord2f(m*(i+0),6*m*(j+1)); glVertex3f(-0.9999*D,0.02*D*m*(i+0)+D/4-0.02*D,4*D/9*m*(j+1)+D/9);
    glTexCoord2f(m*(i+0),6*m*(j+0)); glVertex3f(-0.9999*D,0.02*D*m*(i+0)+D/4-0.02*D,4*D/9*m*(j+0)+D/9);
    glTexCoord2f(m*(i+1),6*m*(j+0)); glVertex3f(-0.9999*D,0.02*D*m*(i+1)+D/4-0.02*D,4*D/9*m*(j+0)+D/9);
    glTexCoord2f(m*(i+1),6*m*(j+1)); glVertex3f(-0.9999*D,0.02*D*m*(i+1)+D/4-0.02*D,4*D/9*m*(j+1)+D/9);
    }
  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);    

  //FINAL WALL WITH BRICK
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glNormal3f(-1,0,0);
  glBegin(GL_QUADS);
  for (i=0;i<num;i++) //width
      for (j=0;j<num;j++) //height
      {
      glTexCoord2d(2*m*(i+0),2*m*(j+0));  glVertex3f(D,D*m*(j+0)-D/2,2*D*m*(i+0)-D);
      glTexCoord2d(2*m*(i+1),2*m*(j+0));  glVertex3f(D,D*m*(j+0)-D/2,2*D*m*(i+1)-D);
      glTexCoord2d(2*m*(i+1),2*m*(j+1));  glVertex3f(D,D*m*(j+1)-D/2,2*D*m*(i+1)-D);
      glTexCoord2d(2*m*(i+0),2*m*(j+1));  glVertex3f(D,D*m*(j+1)-D/2,2*D*m*(i+0)-D);
      }

  //wall in the room
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {
      glTexCoord2d(0.68*m*(i+0),1.985*m*(j+0));  glVertex3f(D/2*m*(i+0)+D/2,D*m*(j+0)+0.33*D,-D/3);
      glTexCoord2d(0.68*m*(i+1),1.985*m*(j+0));  glVertex3f(D/2*m*(i+1)+D/2,D*m*(j+0)+0.33*D,-D/3);
      glTexCoord2d(0.68*m*(i+1),1.985*m*(j+1));  glVertex3f(D/2*m*(i+1)+D/2,D*m*(j+1)+0.33*D,-D/3);
      glTexCoord2d(0.68*m*(i+0),1.985*m*(j+1));  glVertex3f(D/2*m*(i+0)+D/2,D*m*(j+1)+0.33*D,-D/3);
      }  
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {
      glTexCoord2d(2*m*(i+0),2*m*(j+0));  glVertex3f(9*D/6*m*(i+0)-D,D*m*(j+0)-D/2,-D/3);
      glTexCoord2d(2*m*(i+1),2*m*(j+0));  glVertex3f(9*D/6*m*(i+1)-D,D*m*(j+0)-D/2,-D/3);
      glTexCoord2d(2*m*(i+1),2*m*(j+1));  glVertex3f(9*D/6*m*(i+1)-D,D*m*(j+1)-D/2,-D/3);
      glTexCoord2d(2*m*(i+0),2*m*(j+1));  glVertex3f(9*D/6*m*(i+0)-D,D*m*(j+1)-D/2,-D/3);
      }  
  glEnd();

  // ceiling
  glBindTexture(GL_TEXTURE_2D,texture[2]);
  glNormal3f(0,-1,0); 
  glBegin(GL_QUADS);
  for (i=0;i<num;i++)
     for (j=0;j<num;j++)
     { 
     glTexCoord2f(2*m*(i+1),m*(j+0)); glVertex3f(2*D*m*(i+1)-D,+D/2,2*D*m*(j+0)-D);
     glTexCoord2f(2*m*(i+1),m*(j+1)); glVertex3f(2*D*m*(i+1)-D,+D/2,2*D*m*(j+1)-D);
     glTexCoord2f(2*m*(i+0),m*(j+1)); glVertex3f(2*D*m*(i+0)-D,+D/2,2*D*m*(j+1)-D);
     glTexCoord2f(2*m*(i+0),m*(j+0)); glVertex3f(2*D*m*(i+0)-D,+D/2,2*D*m*(j+0)-D);
     }
  glEnd();
  // floor
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glNormal3f(0,1,0); 
  glBegin(GL_QUADS);
  for (i=0;i<num;i++)
     for (j=0;j<num;j++)
     { 
     glTexCoord2f(m*(i+0),m*(j+1)); glVertex3f(2*D*m*(i+0)-D,-D/2,2*D*m*(j+1)-D);
     glTexCoord2f(m*(i+1),m*(j+1)); glVertex3f(2*D*m*(i+1)-D,-D/2,2*D*m*(j+1)-D);
     glTexCoord2f(m*(i+1),m*(j+0)); glVertex3f(2*D*m*(i+1)-D,-D/2,2*D*m*(j+0)-D);
     glTexCoord2f(m*(i+0),m*(j+0)); glVertex3f(2*D*m*(i+0)-D,-D/2,2*D*m*(j+0)-D);
     }  
  glEnd();
  //mat
  glPolygonOffset(1,1);
  glBindTexture(GL_TEXTURE_2D,texture[14]);
  glNormal3f(0,1,0); 
  glBegin(GL_QUADS);
  for (i=0;i<num;i++)
     for (j=0;j<num;j++)
     { 
     glTexCoord2f(m*(i+0),m*(j+1)); glVertex3f(D/2*m*(i+0)-D/1.35,-D/2+0.0001,D*5/6*m*(j+1)-D/4);
     glTexCoord2f(m*(i+1),m*(j+1)); glVertex3f(D/2*m*(i+1)-D/1.35,-D/2+0.0001,D*5/6*m*(j+1)-D/4);
     glTexCoord2f(m*(i+1),m*(j+0)); glVertex3f(D/2*m*(i+1)-D/1.35,-D/2+0.0001,D*5/6*m*(j+0)-D/4);
     glTexCoord2f(m*(i+0),m*(j+0)); glVertex3f(D/2*m*(i+0)-D/1.35,-D/2+0.0001,D*5/6*m*(j+0)-D/4);
     }  
  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);    
  glDisable(GL_TEXTURE_2D);
}

static void door(double x, double y, double z, double ds, double rotationAngle, double D)
{
  int i,j;
  int num=128;
  double m = 1.0/num;
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  //  Sides
  //  Enable Polygon Offset
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.5,1);

  glTranslated(D/2, -D/2, -D/3);
  glRotatef(rotationAngle, 0.0, 1.0, 0.0);
  glScaled(ds, ds, ds);
  glTranslated(x, y, z);
  
  glBindTexture(GL_TEXTURE_2D,texture[5]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {
      glTexCoord2d(m*(i+0),m*(j+0));  glVertex3f(0.5*D*m*(i+0)+x,0.83*D*m*(j+0)+y,z);
      glTexCoord2d(m*(i+1),m*(j+0));  glVertex3f(0.5*D*m*(i+1)+x,0.83*D*m*(j+0)+y,z);
      glTexCoord2d(m*(i+1),m*(j+1));  glVertex3f(0.5*D*m*(i+1)+x,0.83*D*m*(j+1)+y,z);
      glTexCoord2d(m*(i+0),m*(j+1));  glVertex3f(0.5*D*m*(i+0)+x,0.83*D*m*(j+1)+y,z);
      }
  glEnd();      
  glDisable(GL_TEXTURE_2D);
}

static void background()
{
  glPushMatrix();
  table(-dim+0.3, dim/2-0.16, -dim+0.35, 1, 0, 0, 0);
  table2(-dim+0.6, -0.35, 0.2, 1, 0, 0, 0);
  bench(-dim+0.4, -0.4, 0.2, 0.5, 0, 0, 0);
  chair(-dim+0.5, -0.3, -dim+0.35, 1.1, 0, 180, 0);
  round_table(-dim+0.6, -0.4, 0.5, 1, 0, 45, 0);
  clock(dim-0.7, -0.05, 0.94, 1, 0, 180, 0);
  block(dim-0.3, 0, -dim+0.03, 1, 0, 0, 0);
  block(dim-0.8, 0.1, -dim+0.03, 1, 0, 0, 0);
  computer(-dim+0.3, dim/2-0.15, -dim+0.35, 1.2, 0, 90, 0);
  pic1(0, 0.1, -0.325, 0.8, 0, 0, 0);
  pic2(-0.2, 0, -0.325, 0.8, 0, 0, 0);
  bottle(0, -0.45, -0.1, 0.8, 0, 0, 0);
  bottle(0.05, -0.45, -0.1, 0.8, 0, 0, 0);
  bottle(-0.05, -0.45, -0.1, 0.8, 0, -20, 90);
  bottle(0.04, -0.45, -0.05, 0.8, 0, 0, 0);
  bottle(-0.04, -0.45, -0.05, 0.8, 0, 0, 90);
  bottle(0, -0.45, 0, 0.8, 0, 0, 0);
  ball(-0.14, -0.478, -0.3, 0.005, 0, 0, 0);
  cup(dim-0.3, 0.01, -dim+0.03, 1.8, 0, 0, 0);
  cabinet(dim-0.7, 0, 0.94, 1, 0, 0, 0);
  fireStove(dim-0.05, 0, 0.5, 1.2, 0, 90, 0);
  drawfire(dim-0.05, -0.435, 0.5, 0.5, 0, 90, 0,0.698039f,0.13333f,0.13333f);
  drawfire(dim-0.05, -0.435, 0.5, 0.2, 0, 90, 0, 0.803922, 0.521569, 0.247059);
  Room(dim);
  door(0, 0, 0, 1,door_Angle, dim);
  glPopMatrix();
}

void mirror(){
  glColor3f(1,1,1);
  //Draw the scene in the mirror as reflection
  glPushMatrix ();
  glScalef (-1., 1., 1.);
  glTranslatef (dim*2, 0., 0.);
  background();
  glPopMatrix ();

  glClear (GL_DEPTH_BUFFER_BIT);
  glPushAttrib (0xffffffff);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f (0., 0., 0., 0.05);

  glPopAttrib();
  /* The real scene in the room*/
  background();

}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(xp,yp,zp,xp+lx ,yp+ly,zp+lz , 0,1,0);
   //  Light switch
   glShadeModel(GL_SMOOTH);
   //flash light
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Spotlight color and direction
      float color[] = {1.0,1.0,0.0,1.0};
      float Position[] = {xp,yp,zp,1};
      float Direction[] = {lx,ly,lz,0}; 
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Set specular colors
      glMaterialfv(GL_FRONT,GL_SPECULAR,color);
      glMaterialf(GL_FRONT,GL_SHININESS,shiny);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
      //  Set attenuation
      glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION ,at0/100.0);
      glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION   ,at1/100.0);
      glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,at2/100.0);
      //  Set spotlight parameters
      glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Direction);
      glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,sco);
      glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,Exp);
   }
   else
      glDisable(GL_LIGHTING);

   mirror();
   
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,position_z=%f position_x=%f",th,zp,xp);
   if (light)
   {
      glWindowPos2i(5,45);  
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}
/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{  
  double angle=0.02*dim; 
  //  Right arrow key - increase angle by 5 degrees
  if (key == GLUT_KEY_RIGHT)
     {th += 2;
        lx = Sin(th);
        lz = -Cos(th);
     }
  //  Left arrow key - decrease angle by 5 degrees
  else if (key == GLUT_KEY_LEFT)
     {th -= 2;
        lx = Sin(th);
        lz = -Cos(th); 
     }
  //  Up arrow key - increase looking y 
  else if (key == GLUT_KEY_UP)
     ly += angle;
  //  Down arrow key - decrease looking y
  else if (key == GLUT_KEY_DOWN)
     ly -= angle;
  //  Keep angles to +/-360 degrees
  th %= 360;
  //  Update projection
  Project(45,asp,dim);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}
/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
  double angle=0.02*dim; 
  //  Exit on ESC
  if (ch == 27)
     exit(0);
  //  Reset view angle
  else if (ch == '0'){
     th = 0;
     xp = 0;
     zp = 1;
     ly = 0;
  }
  else if (ch == 'w' || ch == 'W'){
    if (fabs(xp+lx*angle)<dim && fabs(zp+lz*angle)<dim) {
      xp += lx*angle;
      zp += lz*angle;   
      } 
  }
  else if (ch == 's' || ch == 'S'){
    if (fabs(xp-lx*angle)<dim && fabs(zp-lz*angle)<dim) {
      xp -= lx*angle;
      zp -= lz*angle;   
    }
  }
  else if (ch == 'd' || ch == 'D'){
    if (fabs(xp-lz*angle)<dim && fabs(zp+lx*angle)<dim) {
      xp -= lz*angle;
      zp += lx*angle;
    }  
  }
  else if (ch == 'a' || ch == 'A'){
    if (fabs(xp+lz*angle)<dim && fabs(zp-lx*angle)<dim) {
      xp += lz*angle;
      zp -= lx*angle;
    }  
  }
  //Toggle flash lighting
  else if (ch == 'l' || ch == 'L')
    light = 1-light;
  //open door
  else if (ch == 'o' || ch == 'O')
    door_Angle = -90*Cos(door_Angle);
  //  Translate shininess power to value (-1 => 0)
  shiny = shininess<0 ? 0 : pow(2.0,shininess);
  //  Reproject
  Project(45,asp,dim);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}
/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{

  //  Ratio of the width to the height of the window
  asp = (height>0) ? (double)width/height : 1;
  //  Set the viewport to the entire window
  glViewport(0,0, width,height);
  //  Set projection
  Project(45,asp,dim);
}
/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
  //  Request double buffered, true color window with Z buffering at 800x800
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  glutInitWindowSize(800,800);
  //  Create the window
  glutCreateWindow("Yi Chen Kuo - Final Project");
  //  Tell GLUT to call "display" when the scene should be drawn
  glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
  glutReshapeFunc(reshape);
  //  Tell GLUT to call "special" when an arrow key is pressed
  glutSpecialFunc(special);
  //  Tell GLUT to call "key" when a key is pressed
  glutKeyboardFunc(key);
  //  Tell GLUT to call "idle" when there is nothing else to do
  glutIdleFunc(idle);

  texture[0] = LoadTexBMP("crate.bmp");
  texture[1] = LoadTexBMP("wall.bmp");
  texture[2] = LoadTexBMP("ceiling.bmp");
  texture[3] = LoadTexBMP("white_wall.bmp");
  texture[4] = LoadTexBMP("green.bmp");
  texture[5] = LoadTexBMP("door.bmp");
  texture[6] = LoadTexBMP("door1.bmp");
  texture[7] = LoadTexBMP("desk.bmp");
  texture[8] = LoadTexBMP("woodside.bmp");
  texture[9] = LoadTexBMP("keyboard.bmp");
  texture[10] = LoadTexBMP("frame.bmp");
  texture[11] = LoadTexBMP("chair.bmp");
  texture[12] = LoadTexBMP("frame1.bmp");
  texture[13] = LoadTexBMP("pic1.bmp");
  texture[14] = LoadTexBMP("mat.bmp");
  texture[15] = LoadTexBMP("frame2.bmp");
  texture[16] = LoadTexBMP("pic2.bmp");
  texture[17] = LoadTexBMP("blackwood.bmp");
  texture[18] = LoadTexBMP("clock.bmp");
  texture[19] = LoadTexBMP("stone.bmp");

  ErrCheck("init");
  //  Pass control to GLUT so it can interact with the user
  glutMainLoop();
  return 0;
}
