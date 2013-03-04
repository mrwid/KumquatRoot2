#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/gdicmn.h"

//////////////////////////////////////////////////////////////////////////


// 屏幕分辨率
const wxInt32 MAIN_SIZE_X = static_cast<wxInt32> (wxGetDisplaySize().x*0.8);		//当前显示器分辨率_X * 0.8
const wxInt32 MAIN_SIZE_Y = static_cast<wxInt32> (wxGetDisplaySize().y*0.8);		//当前显示器分辨率_Y * 0.8
