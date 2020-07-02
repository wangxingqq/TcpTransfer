#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <windows.h>												// Windows��ͷ�ļ�
#include <stdio.h>													// ��׼����/���ͷ�ļ�
#include <gl\gl.h>													// OpenGL32���ͷ�ļ�
#include <gl\glu.h>													// Glu32���ͷ�ļ�

#define MAP_SIZE		1024										// ����߶�ͼ�Ĵ�С
#define STEP_SIZE		16											// ÿ����������ĸߺͿ�

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);		// ����.raw�ļ�

int Height(BYTE *pHeightMap, int X, int Y);							// ����X��Y���ظ߶�ֵ

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex);			// ת���߶�ͼ�����������ڳ�����

#endif