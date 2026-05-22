#include <IRrecv.h>
#include <IRutils.h>

#define IR_RECV_PIN 18
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.setUnknownThreshold(12);
  Serial.println("Listo — Apunta el control y presiona POWER");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Ignorar señales de repetición
    if (results.value == 0xFFFFFFFFFFFFFFFF || results.bits == 0) {
      irrecv.resume();
      return;
    }
    Serial.println("====== CÓDIGO CAPTURADO ======");
    Serial.print("Protocolo : ");
    Serial.println(typeToString(results.decode_type));
    Serial.print("HEX       : 0x");
    Serial.println(results.value, HEX);
    Serial.print("Bits      : ");
    Serial.println(results.bits);
    Serial.println("==============================\n");
    irrecv.resume();
  }
}#include <IRrecv.h>
#include <IRutils.h>

#define IR_RECV_PIN 18
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.setUnknownThreshold(12);
  Serial.println("Listo — Apunta el control y presiona POWER");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Ignorar señales de repetición
    if (results.value == 0xFFFFFFFFFFFFFFFF || results.bits == 0) {
      irrecv.resume();
      return;
    }
    Serial.println("====== CÓDIGO CAPTURADO ======");
    Serial.print("Protocolo : ");
    Serial.println(typeToString(results.decode_type));
    Serial.print("HEX       : 0x");
    Serial.println(results.value, HEX);
    Serial.print("Bits      : ");
    Serial.println(results.bits);
    Serial.println("==============================\n");
    irrecv.resume();
  }
}
