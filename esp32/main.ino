#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

// ─── WiFi ─────────────────────────────────────────────────────────
#define WIFI_SSID     "RAZZERNET"
#define WIFI_PASSWORD "75058917"

// ─── SinricPro ────────────────────────────────────────────────────
#define APP_KEY    "31d77da7-55a6-4d26-959f-81081b884abc"
#define APP_SECRET "8c2147f7-48e7-405a-ae85-c52d8e5bf7c3-39e7a431-4a14-4b42-80fd-0977f1811a78"

// ─── IDs dispositivos ─────────────────────────────────────────────
#define DEVICE_TV       "6a0e2c4c977a0619a74477f7"
#define DEVICE_VOL_UP   "6a0fd93bc93c9fd0e0f94ba9"
#define DEVICE_VOL_DOWN "6a0fda74977a0619a7457bb0"

// ─── Pin emisor IR ────────────────────────────────────────────────
#define IR_SEND_PIN 19
IRsend irsend(IR_SEND_PIN);

// ─── Códigos IR ───────────────────────────────────────────────────
#define IR_TV_POWER   0x020250AFUL
#define IR_VOL_UP     0x202A857UL
#define IR_VOL_DOWN   0x20238C7UL

// ─── Estado volumen continuo ──────────────────────────────────────
bool subiendo  = false;
bool bajando   = false;
unsigned long ultimoEnvio = 0;
#define INTERVALO_VOL 300

// ─── Callback TV ──────────────────────────────────────────────────
bool onTV(const String &deviceId, bool &state) {
  if (state) {
    Serial.println("Alexa → TV: ENCENDER");
  } else {
    Serial.println("Alexa → TV: APAGAR");
  }
  // VARIANTE 1
  irsend.sendNEC(IR_TV_POWER, 32);
  delay(40);
  // VARIANTE 2 — descomenta si V1 no funciona
  // irsend.sendNEC(IR_TV_POWER, 32);
  // delay(40);
  // irsend.sendNEC(IR_TV_POWER, 32);
  // delay(40);
  return true;
}

// ─── Callback Subir Volumen ───────────────────────────────────────
bool onVolUp(const String &deviceId, bool &state) {
  subiendo = state;
  if (state) {
    bajando = false;
    Serial.println("Alexa → VOL+: INICIANDO");
  } else {
    Serial.println("Alexa → VOL+: DETENIDO");
  }
  return true;
}

// ─── Callback Bajar Volumen ───────────────────────────────────────
bool onVolDown(const String &deviceId, bool &state) {
  bajando = state;
  if (state) {
    subiendo = false;
    Serial.println("Alexa → VOL-: INICIANDO");
  } else {
    Serial.println("Alexa → VOL-: DETENIDO");
  }
  return true;
}

// ─── WiFi ─────────────────────────────────────────────────────────
void conectarWiFi() {
  Serial.print("Conectando WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi OK — IP: " + WiFi.localIP().toString());
}

// ─── Setup ────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  irsend.begin();
  conectarWiFi();

  // TV
  SinricProSwitch &sw_tv = SinricPro[DEVICE_TV];
  sw_tv.onPowerState(onTV);

  // Subir Volumen
  SinricProSwitch &sw_vup = SinricPro[DEVICE_VOL_UP];
  sw_vup.onPowerState(onVolUp);

  // Bajar Volumen
  SinricProSwitch &sw_vdown = SinricPro[DEVICE_VOL_DOWN];
  sw_vdown.onPowerState(onVolDown);

  SinricPro.onConnected([]()    { Serial.println("SinricPro conectado ✓"); });
  SinricPro.onDisconnected([]() { Serial.println("SinricPro desconectado"); });
  SinricPro.begin(APP_KEY, APP_SECRET);

  Serial.println("Listo → comandos disponibles:");
  Serial.println("  'Alexa, enciende la tele'");
  Serial.println("  'Alexa, apaga la tele'");
  Serial.println("  'Alexa, sube el volumen'");
  Serial.println("  'Alexa, ya no subas el volumen'");
  Serial.println("  'Alexa, baja el volumen'");
  Serial.println("  'Alexa, ya no bajes el volumen'");
}

// ─── Loop ─────────────────────────────────────────────────────────
void loop() {
  SinricPro.handle();

  unsigned long ahora = millis();

  if ((subiendo || bajando) && (ahora - ultimoEnvio >= INTERVALO_VOL)) {
    if (subiendo) {
      irsend.sendNEC(IR_VOL_UP, 32);
      Serial.println("IR → VOL+");
    } else if (bajando) {
      irsend.sendNEC(IR_VOL_DOWN, 32);
      Serial.println("IR → VOL-");
    }
    ultimoEnvio = ahora;
  }
}
