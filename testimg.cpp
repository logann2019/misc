
#include <iostream>
#include <algorithm>
#include "bmpmini.hpp"

using namespace image;


void DrawPixel(ImageView & img,int x, int y, u_int32_t c1)
{
    if (img.channels==1)
    {
        img.data[x+y*img.width] = c1;
    }
    else
    {
        img.data[x*3+y*img.width*3+0] = c1&0xFF;
        img.data[x*3+y*img.width*3+1] = (c1>>2) &0xFF;
        img.data[x*3+y*img.width*3+2] = (c1>>4) &0xFF;

    }
}

void drawLine(ImageView & img, int x0, int y0, int x1, int y1, u_int32_t c=250)
{
    
		int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
		int err = dx + dy, e2; 

		int size = img.width*img.height;


		for (;;){  /* loop */
			auto index = (x0+y0*img.width);	
			if(index<0 || index>=size)		 
				break;
            DrawPixel(img,x0,y0,c);

			if (x0 == x1 && y0 == y1) break;
			e2 = 2 * err;
			if (e2 >= dy) { err += dy; x0 += sx; }
			if (e2 <= dx) { err += dx; y0 += sy; }
		}
	
}
void drawCross(ImageView & img, int fx, int fy,int w)
{
    for(int x=fx-w;x<=fx+w;x++)
    {
        DrawPixel(img,x,fy,255);
    }
     for(int y=fy-w;y<=fy+w;y++)
    {

        DrawPixel(img,fx,y,255);
    }
}

void drawRectangle(ImageView & img, int fx, int fy, int tx, int ty)
{
    for(int x=fx;x<tx;x++)
    {
        DrawPixel(img,x,fy,255);
        DrawPixel(img,x,ty,255);

    }

    for(int y=fy;y<ty;y++)
    {
        DrawPixel(img,fx,y,255);
        DrawPixel(img,tx,y,255);
    }
}
void drawRectangleFull(ImageView & img, int fx, int fy, int tx, int ty, u_int32_t c=128)
{

	for(int x=fx;x<tx;x++)
    for(int y=fy;y<ty;y++)
    {
         DrawPixel(img,x,y,c);
    }
   drawRectangle(img,fx,fy,tx,ty);
}

void fillTriangle2(ImageView & img, int x0, int y0, int x1, int y1, int x2, int y2, u_int32_t c)
{

	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
		int err = dx + dy, e2; 

		int size = img.width*img.height;


		for (;;){  /* loop */
			auto index = (x0+y0*img.width);	
			if(index<0 || index>=size)		 
				break;

            drawLine(img,x0,y0,x2,y2,c);	

			if (x0 == x1 && y0 == y1) break;
			e2 = 2 * err;
			if (e2 >= dy) { err += dy; x0 += sx; }
			if (e2 <= dx) { err += dx; y0 += sy; }
		}
	
}
void fillTriangle(ImageView & img, int x0, int y0, int x1, int y1, int x2, int y2,u_int32_t c)
{
    fillTriangle2(img,x0,y0,x1,y1,x2,y2,c);
    fillTriangle2(img,x1,y1,x2,y2,x0,y0,c);
    fillTriangle2(img,x2,y2,x0,y0,x1,y1,c);

}

void drawPoint(ImageView & img , int x, int y)
{
	if(x>0 && y>0 && x<img.width && y <img.height)
	{
	   DrawPixel(img,x,y,255);

	}

}


void drawCicrle(ImageView & img , int x, int y, int xc, int yc)
{		

	drawPoint(img,x+xc , (y+yc)) ;
	drawPoint(img,-x+xc , (y+yc));
	drawPoint(img,x+xc , (-y+yc));
	drawPoint(img,-x+xc , (-y+yc));					
	drawPoint(img,y+xc , (x+yc)) ;
	drawPoint(img,-y+xc , (x+yc));
    drawPoint(img,y+xc , (-x+yc));
	drawPoint(img,-y+xc , (-x+yc));

	
}
//-------------------------------------------------------------------------
/// @brief DrawFullCircleRGB
void drawCicrle(ImageView & img,  int xc, int yc, int r)
{
	int pk = 3 - 2*r;
	int x = 0; 
	int y = r;
	drawCicrle(img, x,y,xc,yc);
	while(x < y)
	{
		if(pk <= 0)
		{
			pk = pk + (4*x) + 6;
			drawCicrle(img,++x,y,xc,yc);
		}
		else
		{
			pk = pk + (4*(x-y)) + 10;
			drawCicrle(img,++x,--y,xc,yc);
		}
	}

}
u_int32_t color(u_int32_t r, u_int32_t g, u_int32_t b)
{
    return r+ g<<2 + b<<4;
}

void drawCube(ImageView & img,  int x, int y, int w)
{


    int px1 = x + w/2;
    int py1 = y - w/2;

    int px2 =px1+w;
    int py2 =py1;

    int px3 = px2;
    int py3 = py2+w;

    auto c1 = color(40,100,0);
    auto c2 = color(100,0,0);
    auto c3 = color(50,0,100);

   fillTriangle(img,x,y,px1,py1,x+w,y,c1);
   fillTriangle(img,px2,py2,px1,py1,x+w,y,c1);

	drawLine(img,x,y,px1,py1);
    drawLine(img,px1,py1,px2,py2);
    drawLine(img,px2,py2,x,y+w);


    fillTriangle(img, x+w,y,px2,py2,px3,py3,c2);
    fillTriangle(img, x+w,y+w,x+w,y,px3,py3,c2);

    drawLine(img,px2,py2,x+w,y);
    drawLine(img,px2,py2,px3,py3);
    drawLine(img,px3,py3,x+w,y+w);

	drawRectangleFull(img,x,y,x+w,y+w,c3);


 //  fillTriangle(img,px2,py2,px1,py1,px1,y);

    /*
	drawLine(img,x,y,x+w/2,y-w/2);
	drawLine(img,w+x,y,w+x+w/2,y-w/2);
	drawLine(img,w+x,w+y,w+x+w/2,w+y-w/2);
	drawLine(img,x+w/2,y-w/2,w+x+w/2,y-w/2);
	drawLine(img,w+x+w/2,y-w/2,w+x+w/2,w+y-w/2);
    */

}

int main(int argc, char* argv[])
{
    BMPMini bmp;
    try {
        std::vector<uint8_t> data(512*512*10,0);

        ImageView img(512,512,3,data.data());    
        /*drawRectangle(img,10,10,310,230);
        drawLine(img,30,30,200,200);
        drawCross(img,60,60,2);
        drawCross(img,110,70,2);
        drawCross(img,150,30,2);
        drawCicrle(img,50,50,10);*/
        //drawCube(img,200,200,40);
        //drawCube(img,300,200,40);

   
   
       

    
		for(int x=0;x<3;x++)
		for(int y=2;y>=0;y--)
		for(int z=2;z>=0;z--)

			drawCube(img,200+x*40+z*20,200+y*40-z*20,40);
  
	    bmp.write(img, "test.bmp");
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
   
    return 0;
}