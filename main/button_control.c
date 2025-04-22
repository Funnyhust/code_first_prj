#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "button_control.h"  // Bao gồm header của button_control

// Biến toàn cục để lưu callback
buttonEventCallback btn_event = NULL;

// Hàm khởi tạo nút bấm
void button_init(buttonEventCallback cb) {
    // Cấu hình chân relay
    gpio_reset_pin(RELAY1);
    gpio_set_direction(RELAY1, GPIO_MODE_OUTPUT);

    // Cấu hình chân nút
    gpio_reset_pin(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY); // Nút kéo lên, nhấn xuống nối GND

    // Lưu callback để xử lý sự kiện
    btn_event = cb;

    // Tạo task để theo dõi trạng thái nút
    xTaskCreate(button_task, "Button Task", 2048, NULL, 5, NULL);
}

// Hàm xử lý trạng thái nút bấm
void button_task(void *pvParam) {
    bool last_state = 1;

    while (1) {
        bool current_state = gpio_get_level(BUTTON_GPIO);
        if (last_state == 1 && current_state == 0) { // Phát hiện nhấn (falling edge)
            if (btn_event != NULL) {
                btn_event(PRESSED); // Gọi callback khi nút được nhấn
            }
            vTaskDelay(pdMS_TO_TICKS(50)); // Chống dội nút
        }
        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(10)); // Đọc nút mỗi 10ms
    }
}
