#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <driver/gpio.h>
#include "button_control.h"  // Bao gồm header của button_control

// Hàm callback khi nút được nhấn
bool ledState =0;
void on_button_event(btn_event_e event) {
    if (event == PRESSED) {
        ESP_LOGI("BUTTON", "Button pressed");
        ledState = !ledState ;
        // Thực hiện hành động khi nút được nhấn, ví dụ: bật relay
        gpio_set_level(RELAY1, ledState);  // Bật relay
    }
    
}

void app_main(void) {
    // Khởi tạo nút bấm với callback xử lý sự kiện
    button_init(on_button_event);
}
