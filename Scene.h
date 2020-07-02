#pragma once

int SceneInit(HWND scene_wnd,IplImage **image);
LONG WINAPI SceneProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*F22
          全长 18.92m
          全宽 13.56m
          全高 5m
          空重 13636Kg
          最大起飞重量 27273Kg
          超音速巡航时飞行速度 1590km / h
		  高空最大飞行速率 2335km / h
		  海平面最大飞行速率 1482km / h
		  升限 15240m
*/

//#define TRACKTRANSFORM        //跟踪模式自动切换宏命令