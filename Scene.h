#pragma once

int SceneInit(HWND scene_wnd,IplImage **image);
LONG WINAPI SceneProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*F22
          ȫ�� 18.92m
          ȫ�� 13.56m
          ȫ�� 5m
          ���� 13636Kg
          ���������� 27273Kg
          ������Ѳ��ʱ�����ٶ� 1590km / h
		  �߿����������� 2335km / h
		  ��ƽ������������ 1482km / h
		  ���� 15240m
*/

//#define TRACKTRANSFORM        //����ģʽ�Զ��л�������