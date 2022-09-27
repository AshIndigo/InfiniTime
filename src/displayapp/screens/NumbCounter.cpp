
#include "displayapp/screens/NumbCounter.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

static void event_handler(lv_obj_t* obj, lv_event_t event) {
  NumbCounter* screen = static_cast<NumbCounter*>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}

NumbCounter::NumbCounter(DisplayApp* app) : Screen(app) {
  lv_obj_t* label;

  lv_style_init(&btn_style);
  lv_style_set_radius(&btn_style, LV_STATE_DEFAULT, 20);
  lv_style_set_bg_color(&btn_style, LV_STATE_DEFAULT, LV_COLOR_AQUA);
  lv_style_set_bg_opa(&btn_style, LV_STATE_DEFAULT, LV_OPA_50);

  // Inc 1 Button
  addObj(btnInc1);
  lv_obj_align(btnInc1, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, -50, 0);
  label = lv_label_create(btnInc1, nullptr);
  lv_label_set_text_static(label, "+1");

  // Inc 10 Button
  addObj(btnInc10);
  lv_obj_align(btnInc10, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
  label = lv_label_create(btnInc10, nullptr);
  lv_label_set_text_static(label, "+10");

  // Dec 1 Button
  addObj(btnDec1);
  lv_obj_align(btnDec1, nullptr, LV_ALIGN_IN_BOTTOM_LEFT, 50, 0);
  label = lv_label_create(btnDec1, nullptr);
  lv_label_set_text_static(label, "-1");

  // Dec 10 Button
  addObj(btnDec10);
  lv_obj_align(btnDec10, nullptr, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
  label = lv_label_create(btnDec10, nullptr);
  lv_label_set_text_static(label, "-10");

  // Reset Button
  addObj(btnReset);
  lv_obj_align(btnReset, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  label = lv_label_create(btnReset, nullptr);
  lv_label_set_text_static(label, "X");

  // Count 1
  count1Text = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(count1Text, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_76);
  lv_obj_set_style_local_text_color(count1Text, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xb0, 0xb0, 0xb0));
  lv_label_set_text_static(count1Text, std::to_string(count1).c_str());
  lv_obj_align(count1Text, lv_scr_act(), LV_ALIGN_CENTER, 0, -45);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

void NumbCounter::addObj(lv_obj_t* obj) {
  obj = lv_btn_create(lv_scr_act(), nullptr);
  obj->user_data = this;
  lv_obj_set_event_cb(obj, event_handler);
  lv_obj_set_size(obj, 45, 45);
  lv_obj_add_style(obj, LV_STATE_DEFAULT, &btn_style);
}

NumbCounter::~NumbCounter() {
  lv_obj_clean(lv_scr_act());
  lv_task_del(taskRefresh);
}

void NumbCounter::OnObjectEvent(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (obj == btnInc1) {
      switch (page) {
        case 0:
          count1++;
          break;
        case 1:
          count2++;
          break;
        case 2:
          count3++;
          break;
      }
    } else if (obj == btnInc10) {
      switch (page) {
        case 0:
          count1 += 10;
          break;
        case 1:
          count2 += 10;
          break;
        case 2:
          count3 += 10;
          break;
      }
    } else if (obj == btnDec1) {
      switch (page) {
        case 0:
          count1--;
          break;
        case 1:
          count2--;
          break;
        case 2:
          count3--;
          break;
      }
    } else if (obj == btnDec10) {
      switch (page) {
        case 0:
          count1 -= 10;
          break;
        case 1:
          count2 -= 10;
          break;
        case 2:
          count3 -= 10;
          break;
      }
    } else if (obj == btnReset) {
      switch (page) {
        case 0:
          count1 = 0;
          break;
        case 1:
          count2 = 0;
          break;
        case 2:
          count3 = 0;
          break;
      }
    }
  }
}

void NumbCounter::Refresh() {
  switch (page) {
    case 0:
      lv_label_set_text_fmt(count1Text, std::to_string(count1).c_str());
      break;
    case 1:
      lv_label_set_text_fmt(count1Text, std::to_string(count2).c_str());
      break;
    case 2:
      lv_label_set_text_fmt(count1Text, std::to_string(count3).c_str());
      break;
  }
  lv_obj_align(count1Text, lv_scr_act(), LV_ALIGN_CENTER, 0, -45);
}

bool NumbCounter::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  switch (event) {
    case TouchEvents::SwipeRight: {
      page = std::max(0, page - 1);
      return true;
    }
    case TouchEvents::SwipeLeft: {
      page = std::min(2, page + 1);
      return true;
    }
    default: {
      return false;
    }
  }
}