/*
 *  Fianl Project
 */

#include "CSCIx229.h"
int texture_mode = 1; //  Texture mode
int mode=1;    //  mode
int ntex=0;    //  Texture
int axes=1;       //  Display axes
int th=-45;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
double rep=1;  //  Repetition
double asp=1;     //  Aspect ratio
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
int toggleCup = 1;
int fov=55;       //  Field of view (for perspective)
int move=1;       //  Move light
double dim=3.0;   //  Size of world
int light=0;      //  Lighting
// Light values
int one       =   1;  // Unit value
double distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int room[3]; 


/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube_texture(double x,double y,double z,
                 double dx,double dy,double dz,
                 double r, double g, double b,
                 double phi, double theta, double psi,
     unsigned int texture)
{
   //  Set specular color to white
  float white[] = {1,1,1,1};
  //float black[] = {0,0,0,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

  //  Save transformation
  glPushMatrix();
  //  Offset
  glTranslated(x,y,z);
  glRotated(phi,1,0,0);
  glRotated(theta,0,1,0);
  glRotated(psi,0,0,1);
  glScaled(dx,dy,dz);
  
    //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,texture_mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture);
  //scale color into 255 color space
  double sr = r / 255, sg = g / 255, sb = b / 255;
  //  Front
  glColor3f(sr,sg,sb);
  if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
  glBegin(GL_QUADS);
  glNormal3f( 0, 0, 1);
  glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
  glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
  glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
  glTexCoord2f(0,rep); glVertex3f(-1,+1, 1);
  glEnd();
   //  Back
   glColor3d(sr, sg, sb);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glColor3d(sr, sg, sb);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,rep); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glColor3d(sr, sg, sb);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glColor3d(sr, sg, sb);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(rep,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glColor3d(sr, sg, sb);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, -1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,rep); glVertex3f(-1,-1,+1);
  //  End
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double r, double g, double b,
                 double phi, double theta, double psi)
{
   //  Set specular color to white
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  //  Save transformation
  glPushMatrix();
  //  Offset
  glTranslated(x,y,z);
  glRotated(phi,1,0,0);
  glRotated(theta,0,1,0);
  glRotated(psi,0,0,1);
  glScaled(dx,dy,dz);
  //  Cube
  glBegin(GL_QUADS);
  //scale color into 255 color space
  double sr = r / 255, sg = g / 255, sb = b / 255;
  //  Front
  glColor3f(sr,sg,sb);
  glNormal3f( 0, 0, 1);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);
  //  Back
  glColor3f(sr,sg,sb);
  glNormal3f( 0, 0, -1);
  glVertex3f(+1,-1,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,+1,-1);
  glVertex3f(+1,+1,-1);
  //  Right
  glColor3f(sr,sg,sb);
  glNormal3f(+1, 0, 0);
  glVertex3f(+1,-1,+1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,+1,-1);
  glVertex3f(+1,+1,+1);
  //  Left
  glColor3f(sr,sg,sb);
  glNormal3f(-1, 0, 0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1,+1);
  glVertex3f(-1,+1,+1);
  glVertex3f(-1,+1,-1);
  //  Top
  glColor3f(sr,sg,sb);
  glNormal3f( 0,+1, 0);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);
  //  Bottom
  glColor3f(sr,sg,sb);
  glNormal3f( 0,-one, 0);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);
  //  End
  glEnd();
  //  Undo transformations
  glPopMatrix();
}


/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}


static void background()
{
    unsigned int t_ground = LoadTexBMP("crate.bmp"), t_wall = LoadTexBMP("wall.bmp")
    , t_floor = LoadTexBMP("floor1.bmp");
    
    // Save transformation
    glPushMatrix();

    // Draw a ground
    cube_texture(0, -0.2, 0, 4, 0.2, 4, // x, y, z & dx, dy, dz
      50, 100, 140, 0, 0, 0, t_ground); // r, g, b & phi, theta, psi

    // Draw walls
    cube_texture(4, 4, 0, 0.2, 4, 4, // x, y, z & dx, dy, dz
      50, 100, 140, 0, 0, 0, t_wall); // r, g, b & phi, theta, psi
    
    //with door
    cube_texture(-0.5, 4, -4, 3, 4, -0.2, // x, y, z & dx, dy, dz
      50, 100, 140, 0, 0, 0, t_floor); // r, g, b & phi, theta, psi

    glPopMatrix();
}

static void bottle(double x, double y, double z, double ds, double phi, double theta, double psi)
{
    // Save transformation
    glPushMatrix();

    // Offset and scale
    glTranslated(x, y, z);
    glRotated(phi, 1, 0, 0);
    glRotated(theta, 0, 1, 0);
    glRotated(psi, 0, 0, 1);
    glScaled(ds, ds, ds);
   
   cube(0, 0, 0, 0.35, 0.35, 0.35, 256, 256, 256, 0, 0, 0); 
   cube(0, 0.7, 0, 0.5, 0.5, 0.5, 256, 256, 256, 0, 0, 0);
   cube(0, 1.4, 0, 0.6, 0.6, 0.6, 256, 256, 256, 0, 0, 0);
   cube(0, 2, 0, 0.5, 0.5, 0.5, 256, 256, 256, 0, 0, 0);
   cube(0, 2.4, 0, 0.4, 0.4, 0.4, 256, 256, 256, 0, 0, 0);
   cube(0, 2.8, 0, 0.2, 0.2, 0.2, 256, 0, 0, 0, 0, 0);
   cube(0, 2.9, 0, 0.2, 0.2, 0.2, 256, 256, 256, 0, 0, 0);
   cube(0, 3.4, 0, 0.3, 0.3, 0.3, 256, 256, 256, 0, 0, 0);
   cube(0, 3.6, 0, 0.2, 0.2, 0.2, 256, 256, 256, 0, 0, 0);
   
   glPopMatrix();
}

static void cup(double x, double y, double z, double ds, double phi, double theta, double psi)
{
    // Save transformation
    glPushMatrix();

    // Offset and scale
    glTranslated(x, y, z);
    glRotated(phi, 1, 0, 0);
    glRotated(theta, 0, 1, 0);
    glRotated(psi, 0, 0, 1);
    glScaled(ds, ds, ds);

   
   cube(0, 0, 0, 0.5, 0.5, 0.5, 210,105,30, 0, 0, 0); 

   cube(0, 0.4, 0, 0.3, 0.3, 0.3, 255,215,0, 0, 0, 0); 
   cube(0, 1.3, 0, 0.6, 0.6, 0.6, 255,215,0, 0, 0, 0); 
   cube(0, 1.6, 0, 0.6, 0.6, 0.6, 255,215,0, 0, 0, 0);

   //word
   cube(0, 1.4, 0.65, 0.1, 0.5, 0.1, 255,0,0, 0, 0, 0); 
   cube(-0.1, 1.7, 0.65, 0.1, 0.1, 0.1, 255,0,0, 0, 0, 0);


   //right ear
   cube(0.7, 1, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0); 
   cube(0.8, 1.1, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(0.9, 1.2, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(1, 1.3, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(1, 1.4, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(1, 1.5, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(0.9, 1.6, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(0.8, 1.7, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(0.7, 1.8, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);

   //left ear
   cube(-0.7, 1, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0); 
   cube(-0.8, 1.1, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-0.9, 1.2, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-1, 1.3, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-1, 1.4, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-1, 1.5, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-0.9, 1.6, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-0.8, 1.7, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   cube(-0.7, 1.8, 0, 0.1, 0.1, 0.1, 255,215,0, 0, 0, 0);
   
   glPopMatrix();
}


/*static void cutter(double x, double y, double z, double ds, double phi, double theta, double psi)
{
    // Save transformation
    glPushMatrix();

    // Offset and scale
    glTranslated(x, y, z);
    glRotated(phi, 1, 0, 0);
    glRotated(theta, 0, 1, 0);
    glRotated(psi, 0, 0, 1);
    glScaled(ds, ds, ds);

    // Right Blade
    cube(0.3, -0.5, 0, 0.1, 0.8, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, -20); // r, g, b & phi, theta, psi
    cube(0.47, -0.55, 0, 0.1, 0.6, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, -20); // r, g, b & phi, theta, psi
    cube(0.6, -0.6, 0, 0.1, 0.4, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, -20); // r, g, b & phi, theta, psi
    cube(0.72, -0.61, 0, 0.1, 0.2, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, -20); // r, g, b & phi, theta, psi

    // Left Blade
    cube(-0.3, -0.5, 0, 0.1, 0.8, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, 20); // r, g, b & phi, theta, psi
    cube(-0.47, -0.55, 0, 0.1, 0.6, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, 20); // r, g, b & phi, theta, psi
    cube(-0.6, -0.6, 0, 0.1, 0.4, 0.02, // x, y, z & dx, dy, dz
      255,20,147, 0, 0, 20); // r, g, b & phi, theta, psi
    cube(-0.72, -0.61, 0, 0.1, 0.2, 0.02, // x, y, z & dx, dy, dz
     255,20,147, 0, 0, 20); // r, g, b & phi, theta, psi
    glPopMatrix();
}*/
/*  Draw sky box
 */
static void Room(double D)
{  
   int i,j;
   int num=128;
   double mul = 1.0/num;
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);

   //  Sides
   //  Enable Polygon Offset
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1.5,1);

   glBindTexture(GL_TEXTURE_2D,room[0]);
   glNormal3f(0,0,1.0);
   glBegin(GL_QUADS);
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {
      glTexCoord2d(mul*(i+0),mul*(j+0));  glVertex3f(2*D*mul*(i+0)-D,D*mul*(j+0)-D/2,-D);
      glTexCoord2d(mul*(i+1),mul*(j+0));  glVertex3f(2*D*mul*(i+1)-D,D*mul*(j+0)-D/2,-D);
      glTexCoord2d(mul*(i+1),mul*(j+1));  glVertex3f(2*D*mul*(i+1)-D,D*mul*(j+1)-D/2,-D);
      glTexCoord2d(mul*(i+0),mul*(j+1));  glVertex3f(2*D*mul*(i+0)-D,D*mul*(j+1)-D/2,-D);
      }
   glNormal3f(-1,0,0);    
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {   
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(+D,D*mul*(i+0)-D/2,2*D*mul*(j+0)-D);
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(+D,D*mul*(i+0)-D/2,2*D*mul*(j+1)-D);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(+D,+D*mul*(i+1)-D/2,2*D*mul*(j+1)-D);
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(+D,+D*mul*(i+1)-D/2,2*D*mul*(j+0)-D);
      }
   glNormal3f(0,0,-1.0);
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {         
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(+2*D*mul*(i+1)-D,D*mul*(j+0)-D/2,+D);
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(2*D*mul*(i+0)-D,D*mul*(j+0)-D/2,+D);
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(2*D*mul*(i+0)-D,+D*mul*(j+1)-D/2,+D);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(+2*D*mul*(i+1)-D,+D*mul*(j+1)-D/2,+D);
      }
   
   glNormal3f(1,0,0); 
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {      
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(-D,D*mul*(i+0)-D/2,+D/2*mul*(j+1)-D);
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(-D,D*mul*(i+0)-D/2,D/2*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(-D,+D*mul*(i+1)-D/2,D/2*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(-D,+D*mul*(i+1)-D/2,D/2*mul*(j+1)-D);
      }
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {      
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(-D,D*mul*(i+0)-D/2,+D/2*mul*(j+1)+D/2);
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(-D,D*mul*(i+0)-D/2,D/2*mul*(j+0)+D/2);
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(-D,+D*mul*(i+1)-D/2,D/2*mul*(j+0)+D/2);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(-D,+D*mul*(i+1)-D/2,D/2*mul*(j+1)+D/2);
      }   
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {      
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(-D,(D/4)*mul*(i+0)-D/2,+2*D*mul*(j+1)-D);
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(-D,(D/4)*mul*(i+0)-D/2,2*D*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(-D,(D/4)*mul*(i+1)-D/2,2*D*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(-D,(D/4)*mul*(i+1)-D/2,2*D*mul*(j+1)-D);
      }       
   for (i=0;i<num;i++)
      for (j=0;j<num;j++)
      {      
      glTexCoord2f(mul*(i+0),mul*(j+1)); glVertex3f(-D,(D/4)*mul*(i+0)+D/4,+2*D*mul*(j+1)-D);
      glTexCoord2f(mul*(i+0),mul*(j+0)); glVertex3f(-D,(D/4)*mul*(i+0)+D/4,2*D*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+0)); glVertex3f(-D,(D/4)*mul*(i+1)+D/4,2*D*mul*(j+0)-D);
      glTexCoord2f(mul*(i+1),mul*(j+1)); glVertex3f(-D,(D/4)*mul*(i+1)+D/4,2*D*mul*(j+1)-D);
      }   
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
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes

   
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   //  Orthogonal - set world orientation
   /*if (mode == 0) {
       glRotatef(ph,1,0,0);
       glRotatef(th,0,1,0);
   } else if (mode == 1) {
      Ex = -2*worldSize*Sin(th)*Cos(ph);
      Ey = +2*worldSize        *Sin(ph);
      Ez = +2*worldSize*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  
   } else {
      //gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
      gluLookAt(eye_x, eye_y, eye_z, 
  reference_x * Cos(eye_th),reference_y,reference_z * Sin(eye_th),  
  0,1,0);
   }
   */
   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

   
   


   //  Draw a background
   background();

   // Draw bottle
   bottle(-1, 0.1, -0.1, 0.2, 80, 0, 20);
   bottle(-1.5, 0, 0.5, 0.3, 0, 0, 0);
   bottle(-1.5, 0, -0.5, 0.3, 0, 0, 0);
  
   //ball(1, 0.2, 0, 0.2);

   if (toggleCup) {
      cup(1.4, 0, -1, 0.3, 0, 0, 0);
      cutter(1.4 , 1+ Cos(zh*2)/12, -1, 0.2, 0, 90 *zh/18, 0);
   }
   
   //bowling ball
   //sphere(1.4-zh/50, 0.2, 0.9, 0.2);
   //sphere(1.6-zh/60, 0.2, 0-zh*zh/28000, 0.2);
   
   

/* + Sin(zh * 2) 3 * zh*/

   //  White
   //glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   /*Print("Angle=%d,%d  worldSize=%.1f FOV=%d Projection=%s",
     th,ph,worldSize,fov,mode?"Perpective":"Orthogonal");*/
   //  Display parameters
   
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s Repeat=%.1f Texture=%s",
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off",rep,texture_mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%.1f Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();
   
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   /*else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;*/
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
     //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();

}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'z' || ch == 'Z')
      toggleCup = 1-toggleCup;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle texture mode
   else if (ch == 'T')
      texture_mode = 1-texture_mode;
     //  Toggle textures mode
   else if (ch == 't')
      ntex = 1-ntex;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1-mode;
   //  Toggle light movement
   else if (ch == 'i' || ch == 'I')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Change light distance
   else if (ch == ',' && distance >0.1)
      distance -= 0.1;
   else if (ch == '.')
      distance += 0.1;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
  //  Repetition
   else if (ch=='1')
      rep += 0.1;
   else if (ch=='2')
      rep -= 0.1;
   //  Keep values in range
   if (rep<1) rep = 1;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
    const double dim=2.5;
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   //  Set projection
   Project(mode?fov:0,asp,dim);
   glLoadIdentity();
   
}



/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 800x800
   glutInitWindowSize(800,800);
   
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Yi Chen Kuo - Final Project");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);

   room[0] = LoadTexBMP("crate.bmp");
   

   ErrCheck("init");
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
