#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEUtils.h>
#include <vector>
#include <algorithm>

#define DISTANCE_THRESHOLD 1.0  // Limite de distância em metros
#define SCAN_TIME 5  // Tempo de varredura em segundos
#define MAX_DISTANCE 5.0  // Distância máxima para considerar dispositivos

// Definição global do enum Color
enum Color { RED, GREEN, BLUE };

// Estrutura para armazenar informações do dispositivo BLE
struct BLEDeviceInfo {
    String name;
    String address;
    int rssi;
    float distance;
};

// Função para calcular a distância aproximada com base no RSSI
float calculateDistance(int rssi) {
    int txPower = -59; // Valor padrão de Tx Power para dispositivos BLE
    if (rssi == 0) {
        return -1.0; // Sem RSSI
    }
    float ratio = rssi * 1.0 / txPower;
    if (ratio < 1.0) {
        return pow(ratio, 10);
    } else {
        return (0.89976) * pow(ratio, 7.7095) + 0.111;
    }
}

// Função para configurar a cor do LED RGB
void setRGBColor(Color color) {
#ifdef RGB_BUILTIN
    switch (color) {
        case RED:
            rgbLedWrite(RGB_BUILTIN, 255, 0, 0); // Vermelho
            break;
        case GREEN:
            rgbLedWrite(RGB_BUILTIN, 0, 255, 0); // Verde
            break;
        case BLUE:
            rgbLedWrite(RGB_BUILTIN, 0, 0, 255); // Azul
            break;
    }
#endif
}

void setup() {
    Serial.begin(115200);

    // Configurações do BLE
    BLEDevice::init("");
}

void loop() {
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true); // Modo de varredura ativa
    Serial.println("Iniciando varredura BLE...");

    // Inicia a varredura e armazena os resultados
    BLEScanResults* scanResultsPointer = pBLEScan->start(SCAN_TIME);
    BLEScanResults& scanResults = *scanResultsPointer; // Converte o ponteiro para referência

    int deviceCount = scanResults.getCount();
    bool closeDeviceFound = false;

    std::vector<BLEDeviceInfo> devices;

    for (int i = 0; i < deviceCount; i++) {
        BLEAdvertisedDevice device = scanResults.getDevice(i);
        int rssi = device.getRSSI();
        float distance = calculateDistance(rssi);

        if (distance > 0 && distance <= MAX_DISTANCE) {
            BLEDeviceInfo deviceInfo = {
                device.getName().c_str(),
                device.getAddress().toString().c_str(),
                rssi,
                distance
            };
            devices.push_back(deviceInfo);

            if (distance <= DISTANCE_THRESHOLD) {
                closeDeviceFound = true;
            }
        }
    }

    // Ordenar dispositivos por distância em ordem crescente
    std::sort(devices.begin(), devices.end(), [](const BLEDeviceInfo& a, const BLEDeviceInfo& b) {
        return a.distance < b.distance;
    });

    Serial.println("\nDispositivos encontrados (ordem por distância):");
    Serial.println("----------------------------------------------");
    Serial.println("| Dispositivo | MAC               | RSSI  | Distância (m) |");
    Serial.println("----------------------------------------------");

    for (const auto& device : devices) {
        Serial.printf("| %-11s | %-17s | %-5d | %-12.2f |\n",
                      device.name.c_str(),
                      device.address.c_str(),
                      device.rssi,
                      device.distance);
    }

    Serial.println("----------------------------------------------\n");

    // Define a cor do LED com base na proximidade de dispositivos
    if (closeDeviceFound) {
        setRGBColor(GREEN); // Verde: Dispositivo próximo
    } else if (!devices.empty()) {
        setRGBColor(BLUE); // Azul: Dispositivos encontrados
    } else {
        setRGBColor(RED); // Vermelho: Nenhum dispositivo
    }

    delay(5000); // Intervalo entre varreduras
}
