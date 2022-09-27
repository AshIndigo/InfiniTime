#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>
#include <FreeRTOS.h>
#include <lvgl/src/lv_core/lv_obj.h>
#include <string>
#include "portmacro_cmsis.h"
#include "systemtask/SystemTask.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class NumbCounter : public Screen {
      public:
        NumbCounter(DisplayApp* app);
        ~NumbCounter() override;
        void Refresh() override;
        void OnObjectEvent(lv_obj_t* obj, lv_event_t event);
        
      private:
        bool OnTouchEvent(TouchEvents event) override;
        void addObj(lv_obj_t* obj);
        
        int count1 = 0;
        int count2 = 0;
        int count3 = 0;
        
        int page = 0;
        
        lv_obj_t* count1Text;
        
        lv_obj_t* btnInc1;
        lv_obj_t* btnDec1;
        lv_obj_t* btnInc10;
        lv_obj_t* btnDec10;
        lv_obj_t* btnReset;

        lv_style_t btn_style;
        
        lv_task_t* taskRefresh;
      };
    }
  }
}