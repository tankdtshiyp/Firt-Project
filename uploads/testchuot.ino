#include <Usb.h>
#include <hidboot.h>
#include <usbhub.h>

USB     Usb;
USBHub  Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    Mouse(&Usb);

// --- Parser TUYỆT ĐỐI KHÔNG TRÙNG TÊN ---
class MyMouseParser : public MouseReportParser {
  void OnMouseMove(MOUSEINFO *mi) {
    Serial.print("Di chuyen: X=");
    Serial.print(mi->dX);
    Serial.print("  Y=");
    Serial.println(mi->dY);
  }

  void OnLeftButtonDown(MOUSEINFO *mi) {
    Serial.println("Nut trai: DOWN");
  }
  void OnLeftButtonUp(MOUSEINFO *mi) {
    Serial.println("Nut trai: UP");
  }

  void OnRightButtonDown(MOUSEINFO *mi) {
    Serial.println("Nut phai: DOWN");
  }
  void OnRightButtonUp(MOUSEINFO *mi) {
    Serial.println("Nut phai: UP");
  }

  void OnMiddleButtonDown(MOUSEINFO *mi) {
    Serial.println("Nut giua: DOWN");
  }
  void OnMiddleButtonUp(MOUSEINFO *mi) {
    Serial.println("Nut giua: UP");
  }
};

MyMouseParser parser;   // dùng class mới, không trùng với thư viện

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }

  Serial.println("Khoi dong USB Host test chuot...");
  if (Usb.Init() == -1) {
    Serial.println("Loi Init USB Host Shield!");
    while (1);   // dừng luôn
  }

  Mouse.SetReportParser(0, &parser);
  Serial.println("San sang. Hay cam chuot USB vao Host Shield.");
}

void loop() {
  Usb.Task();   // xử lý USB
}
