# 📡 Capturador IR con ESP32 + AWS Lambda

Sistema que captura códigos de controles remotos infrarrojos con un ESP32 y los almacena automáticamente en la nube usando AWS Lambda y DynamoDB.

---

## ¿Cómo funciona?

1. El ESP32 detecta una señal infrarroja (IR) de cualquier control remoto
2. Extrae el protocolo, código HEX y cantidad de bits
3. Envía los datos por WiFi a una función AWS Lambda
4. Lambda guarda el registro en una base de datos DynamoDB

---

## 🛠️ Hardware necesario

- Placa ESP32
- Receptor IR (ej. VS1838B)
- Cable USB para programar

---

## 📁 Estructura del repositorio

```
proyecto-esp32-lambda/
├── README.md
├── esp32/
│   └── main.ino        # Código para el ESP32
└── lambda/
    └── index.py        # Función AWS Lambda
```

---

## ⚙️ Configuración

### ESP32
1. Abre `esp32/main.ino` en Arduino IDE
2. Cambia estas líneas con tus datos:
```cpp
const char* ssid     = "TU_WIFI";
const char* password = "TU_CONTRASEÑA";
const char* serverURL = "TU_URL_API_GATEWAY";
```
3. Instala la librería **IRremoteESP8266** desde el gestor de librerías
4. Carga el código en tu ESP32

### AWS
1. Crea una tabla en **DynamoDB** llamada `codigos-ir` con clave `id`
2. Crea una función **Lambda** con el código de `lambda/index.py`
3. Asigna el permiso **AmazonDynamoDBFullAccess** al rol de Lambda
4. Crea una **API Gateway** HTTP con método POST en `/guardar`

---

## 🗄️ Datos guardados en DynamoDB

| Campo | Descripción |
|-------|-------------|
| `id` | Identificador único |
| `protocolo` | Protocolo IR (NEC, SONY, etc.) |
| `hex` | Código en hexadecimal |
| `bits` | Cantidad de bits de la señal |
| `timestamp` | Fecha y hora de captura |

---

## 📚 Librerías utilizadas

- [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)
- AWS SDK (boto3) — incluido en Lambda por defecto
