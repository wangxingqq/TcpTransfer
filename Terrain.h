#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <windows.h>												// Windows的头文件
#include <stdio.h>													// 标准输入/输出头文件
#include <gl\gl.h>													// OpenGL32库的头文件
#include <gl\glu.h>													// Glu32库的头文件

#define MAP_SIZE		1024										// 定义高度图的大小
#define STEP_SIZE		16											// 每个三角网格的高和宽

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);		// 导入.raw文件

int Height(BYTE *pHeightMap, int X, int Y);							// 根据X和Y返回高度值

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex);			// 转换高度图并将它绘制在场景中

#endif