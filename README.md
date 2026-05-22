# 📺 Control de TV con Alexa + ESP32

Sistema que permite controlar un televisor mediante comandos de voz a través de Alexa, usando un ESP32 como emisor infrarrojo (IR) y SinricPro como puente de comunicación.

---

## ¿Cómo funciona?

1. Le dices un comando a Alexa ("Alexa, enciende la tele")
2. Alexa lo envía a SinricPro por internet
3. SinricPro se comunica con el ESP32 por WiFi
4. El ESP32 emite la señal infrarroja al televisor

---

## 🛠️ Hardware necesario

- Placa ESP32
- LED emisor IR (ej. IR333)
- Resistencia de 100Ω
- Cable USB para programar

---

## 🔌 Conexión del hardware

| ESP32 | Componente |
|-------|------------|
| Pin 19 | LED IR (+) |
| GND | LED IR (-) con resistencia 100Ω |

---

## 🗣️ Comandos de voz disponibles

| Comando Alexa | Acción |
|---------------|--------|
| "Alexa, enciende la tele" | Enciende el TV |
| "Alexa, apaga la tele" | Apaga el TV |
| "Alexa, enciende sube volumen" | Sube el volumen continuamente |
| "Alexa, apaga sube volumen" | Detiene subir volumen |
| "Alexa, enciende baja volumen" | Baja el volumen continuamente |
| "Alexa, apaga baja volumen" | Detiene bajar volumen |

---

## 📁 Estructura del repositorio

```
proyecto-esp32-alexa-tv/
├── README.md
└── esp32/
    └── main.ino        # Código principal del ESP32
```

---

## ⚙️ Configuración

### 1. Librerías necesarias en Arduino IDE

| Librería | Cómo instalarla |
|----------|----------------|
| SinricPro | Gestor de librerías → busca `SinricPro` |
| IRremoteESP8266 | Gestor de librerías → busca `IRremoteESP8266` |
| WiFi | Ya incluida con ESP32 |

### 2. Credenciales

Abre `esp32/main.ino` y edita esta sección con tus datos:

```cpp
#define WIFI_SSID     "TU_WIFI"
#define WIFI_PASSWORD "TU_CONTRASEÑA"

#define APP_KEY    "TU_APP_KEY_DE_SINRICPRO"
#define APP_SECRET "TU_APP_SECRET_DE_SINRICPRO"
```

> ⚠️ Nunca subas tus claves reales a GitHub.

### 3. Cuenta en SinricPro

1. Regístrate en [sinric.pro](https://sinric.pro)
2. Crea 3 dispositivos de tipo **Switch**:
   - `Tele` → copia el Device ID en `DEVICE_TV`
   - `Sube Volumen` → copia el ID en `DEVICE_VOL_UP`
   - `Baja Volumen` → copia el ID en `DEVICE_VOL_DOWN`
3. Copia tu **App Key** y **App Secret** del dashboard

### 4. Vincular con Alexa

1. Abre la app de Alexa
2. Ve a **Skills** → busca **SinricPro**
3. Activa el skill e inicia sesión con tu cuenta SinricPro
4. Alexa detectará los 3 dispositivos automáticamente

---

## 📚 Tecnologías utilizadas

- [SinricPro](https://sinric.pro) — puente Alexa ↔ ESP32
- [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) — emisión de señales IR
- Arduino IDE con soporte ESP32
## 📊 Tabla de códigos IR capturados

| Dispositivo | Función | Protocolo | Código HEX | Bits |
|-------------|---------|-----------|------------|------|
| TV | Power | NEC | 0x20250AF | 32 |
| TV | Vol + | NEC | 0x202A857 | 32 |
| TV | Vol - | NEC | 0x20238C7 | 32 |

---

## ⚙️ Funcionamiento del sistema

1. Alexa recibe el comando de voz del usuario
2. Sinric Pro envía la instrucción al ESP32 por internet
3. El ESP32 procesa la orden recibida
4. El LED IR transmite el código correspondiente al televisor
5. El TV responde como si fuera el control remoto original
