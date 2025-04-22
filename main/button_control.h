#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

// Khai báo các chân GPIO
#define BUTTON_GPIO 15
#define RELAY1 47

// Khai báo kiểu enum cho sự kiện nút
typedef enum {
    PRESSED,
    RELEASE,
} btn_event_e;

// Khai báo kiểu callback function cho sự kiện nút
typedef void (*buttonEventCallback)(btn_event_e);

// Hàm khởi tạo và cấu hình nút bấm
void button_init(buttonEventCallback cb);

// Hàm xử lý sự kiện của nút bấm
void button_task(void *pvParam);

#endif // BUTTON_CONTROL_H
