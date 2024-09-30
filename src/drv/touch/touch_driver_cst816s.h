#if defined(ARDUINO) && (TOUCH_DRIVER == 0x816) && !defined(HASP_USE_LGFX_TOUCH)
#include <Arduino.h>
#include "ArduinoLog.h"
#include "hasp_conf.h"

#include "touch_driver.h" // base class

#include "../../hasp/hasp.h" // for hasp_sleep_state
extern uint8_t hasp_sleep_state;

#include <CST816S.h>

namespace dev {

class Cst816sTouch : public BaseTouch {

  public:
    CST816S* touch;

    void init(int w, int h)
    {
        touch = new CST816S(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_IRQ);
        touch->begin();
    }

    IRAM_ATTR bool read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
    {
        if(touch->available()) {
            if(touch->data.points != 0) {
                data->point.x = touch->data.x;
                data->point.y = touch->data.y;
                data->state   = LV_INDEV_STATE_PR;
            } else {
                data->state = LV_INDEV_STATE_REL;
            }
        }

        return false;
    }
};

} // namespace dev

#warning Using CST816S
using dev::Cst816sTouch;
dev::Cst816sTouch haspTouch;

#endif // ARDUINO
