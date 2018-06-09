#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "externs.h"
#include "game.h"
#include <stdio.h>
#include <math.h>
int NumberPlayers=2;
//int Currentplayer=0;
int View_Menu=5;
 //int View_Menu=0;
struct point Points[MAX_PATHS][MAX_POINT], *pPoints=&Points[0][0];
struct player Players[MAX_PLAYER], *pPlayers=&Players[0];
struct fileinfo1 Fileinfo={"SBM",-1,-1," CorelDraw picture"}, *pFileInfo=&Fileinfo;
static HWND hMainWnd;
char* ver={"0.07"};
char* pFilePoints={"points.dat"};//
extern CurPl,flag;
void InitGame()
{
flag=0;
//int path=0;
int path=0;
CurPl=0;//NumberPlayers-1;
//NumberPlayers=1;
Players[0].color=0;
Players[0].path=path;
Players[0].point=1;
Players[0].winner=0;

Players[1].color=1;
Players[1].path=path;
Players[1].point=1;
Players[1].winner=0;

Players[2].color=2;
Players[2].path=path;
Players[2].point=1;
Players[2].winner=0;
//Players[0].LocX=Players[0].X=1456;
//Players[0].LocY=Players[0].Y=174;


//Points[0][1].X=1456;
//Points[0][1].Y=174;

//Points[0][2].X=1334;
//Points[0][2].Y=718;



LoadPoints();
//Points[7][17].X=266;
//Points[7][17].Y=510;

Players[0].LocX=Players[0].X=Points[path][Players[0].point].X;
Players[0].LocY=Players[0].Y=Points[path][Players[0].point].Y;

Players[1].LocX=Players[1].X=Points[path][Players[1].point].X;
Players[1].LocY=Players[1].Y=Points[path][Players[1].point].Y;
Players[2].LocX=Players[2].X=Points[path][Players[2].point].X;
Players[2].LocY=Players[2].Y=Points[path][Players[2].point].Y;

//Players[0].LocX=Players[0].X=1456;
//Players[0].LocY=Players[0].Y=174;
//for(int k=0;k< 30;k++)
//{Points[7][k].X=0;
//Points[7][k].Y=0;}
}

void Move(int path ,int point)
//void Move(int point)
{

int i=CurPl;

	int		x1=Players[i].x1=Players[i].X=Points[Players[i].path][Players[i].point].X;;
	int		y1=Players[i].y1=Players[i].Y=Points[Players[i].path][Players[i].point].Y;

	Players[i].path=path;
	Players[i].point=point;
	//Players[i].count=2;

	int		x2=Players[i].x2=Players[i].LocX=Points[path][point].X;
	int		y2=Players[i].y2=Players[i].LocY=Points[path][point].Y;

		Players[i].r=0;			
		
		//Players[i].x2=Points[path][point].X;
					//Players[i].y2=Points[path][point].Y;

					//Players[i].x1=Players[i].X;
					//Players[i].y1=Players[i].Y;
			//int		x2=Players[i].x2=Points[path][point].X;
			//int		y2=Players[i].y2=Points[path][point].Y;
					
						
					//int		x1=Players[i].x1;
					//int		x2=Players[i].x2;
					//int		y1=Players[i].y1;
					//int		y2=Players[i].y2;
					float	locX=(float)(x2-x1);
					float	locY=(float)(y2-y1);

					if(x2>x1&&y2>y1)Players[i].alfa=(float)(atanf((float)(locY/locX)));
					if(x2<x1&&y2>y1)Players[i].alfa=(float)(PI/2+atanf((float)(-locX/locY)));
					if(x2<x1&&y2<y1)Players[i].alfa=(float)(PI+atanf((float)(locY/locX)));
					if(x2>x1&&y2<y1)Players[i].alfa=(float)(PI+PI/2+atanf((float)(-locX/locY)));
				
					/*
					int		r=Players[i].r;
					float	alfa=Players[i].alfa;
					float	locX2=(float)(r*cosf(alfa));
					float	locY2=(float)(r*sinf(alfa));
			
					Players[i].X=(int)(x1+locX2); 
					Players[i].Y=(int)(y1+locY2); 
				*/

					//Players[i].Xq=Players[i].X/Q_WIDTH;
					//Players[i].Yq=Players[i].Y/Q_WIDTH;
				
					//LocalPersX=PersX;
					//LocalPersY=PersY;
					//PersXNew=PersX;
					//PersYNew=PersY;
					//XqNew=LocalXq=Xp;
					//YqNew=LocalYq=Yp;




if(Map_scrolled)
{
	CameraX=Players[CurPl].X;	
	CameraY=Players[CurPl].Y;
	Map_scrolled=0;
}
#ifndef ZOOM
	if(CameraX<MAX_WIDTH/2)CameraX=MAX_WIDTH/2;
	if(CameraX>MAP_WIDTH-MAX_WIDTH/2)CameraX=MAP_WIDTH-MAX_WIDTH/2;
	if(CameraY<MAX_HEIGHT/2)CameraY=MAX_HEIGHT/2;
	if(CameraY>MAP_HEIGHT-MAX_HEIGHT/2)CameraY=MAP_HEIGHT-MAX_HEIGHT/2;
#endif
#ifdef ZOOM
	if(CameraX<MAX_WIDTH)CameraX=MAX_WIDTH;
	if(CameraX>MAP_WIDTH-MAX_WIDTH)CameraX=MAP_WIDTH-MAX_WIDTH;
	if(CameraY<MAX_HEIGHT)CameraY=MAX_HEIGHT;
	if(CameraY>MAP_HEIGHT-MAX_HEIGHT)CameraY=MAP_HEIGHT-MAX_HEIGHT;
#endif
}

void SavePoints()
{
	FILE *fp;
if((fp=fopen(pFilePoints,"wb"))==NULL)
	ErrorHandle(hMainWnd, "error OPENFILE");

//if(fwrite(&MaxQ,4,1,fp)!=1)
//ErrorHandle(hMainWnd, "writeMapSizeFILE");


if(fwrite(pPoints,sizeof(Points[MAX_PATHS][MAX_POINT]),MAX_PATHS*MAX_POINT,fp)!=unsigned int(MAX_PATHS*MAX_POINT))
	ErrorHandle(hMainWnd, "error writeFILE");
if((fclose(fp))!=NULL)
	ErrorHandle(hMainWnd, "error closeFILE");

}
void LoadPoints()
{

	
	FILE *fp;
if((fp=fopen(pFilePoints,"rb"))==NULL)
	ErrorHandle(hMainWnd, "error OPENFILE");

//if(fwrite(&MaxQ,4,1,fp)!=1)
//ErrorHandle(hMainWnd, "writeMapSizeFILE");


if(fread(pPoints,sizeof(Points[MAX_PATHS][MAX_POINT]),MAX_PATHS*MAX_POINT,fp)!=unsigned int((MAX_PATHS)*MAX_POINT))
	ErrorHandle(hMainWnd, "error readFILE");
if((fclose(fp))!=NULL)
	ErrorHandle(hMainWnd, "error closeFILE");



}