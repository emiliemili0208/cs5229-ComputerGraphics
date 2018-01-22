#import <OpenGL/OpenGL.h>  
  
#ifndef _PARTICLE_SYSTEM_  
#define _PARTICLE_SYSTEM_  
#define MAX_PARTICLE_NUM 1000  
////////////////////////////////////////////////////  
//默认风格集合  
#define PSTYLE_STAR 0  
#define PSTYLE_FIRE 1  
#define PSTYLE_SNOW 2  
////////////////////////////////////////////////////  
typedef struct particle {  
      
    GLboolean active;//是否活跃  
    GLfloat life;//生命  
      
    GLfloat fade; //衰减速度  
      
    //颜色  
    GLfloat r;//红色  
    GLfloat g;//绿色  
    GLfloat b;//蓝色  
      
    //位置  
    GLfloat x;  
    GLfloat y;  
    GLfloat z;  
      
    //速度  
    GLfloat xs;  
    GLfloat ys;  
    GLfloat zs;  
      
    //加速度  
    GLfloat xg;  
    GLfloat yg;  
    GLfloat zg;  
      
}Particle;  
extern void particleInitCallBack(GLvoid (*p)(Particle * q) );   
extern void particleDisplayCallBack(GLvoid (*p)(Particle *q));   
extern void particleUpdateCallBack(GLvoid (*p)(Particle *q));   
extern void particleSysStartUp();   
extern void particleInitAll();   
extern void particleMainLoop();   
extern void particleSetNumber(GLuint num);   
extern void particleSetColorArray(GLint  array[][3],GLuint count);   
extern void particleSetDefaultStyle(GLuint mode);   
#endif  