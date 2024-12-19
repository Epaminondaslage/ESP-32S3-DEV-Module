# Módulo ESP32-S3 DevKitC-1 N8R2 com WiFi e Bluetooth/BLE 5.0 - USB-C

## Escolher a **Placa ESP32S3 DEV Module** na IDE Arduino

O **ESP32-S3 DevKitC-1 N8R2** é um microcontrolador com antena integrada, ideal para projetos de IoT (Internet das Coisas). Ele se destaca pelo seu hardware poderoso, baixo custo e conectividade WiFi e Bluetooth/BLE 5.0. É amplamente aplicado em projetos eletrônicos, como computação de rede neural, IA e IAIoT (Inteligência Artificial das Coisas).

<img src="esp32 s3.jpeg" alt="Diagrama do ESP32" width="400">

## **Características Principais**
- **Microprocessador:** Xtensa 32-Bits LX7 Dual Core com baixo consumo de energia.
- **Memória:** Flash externa de 8 MB (QD) e PSRAM de 2 MB (QD).
- **GPIOs:** 36 pinos programáveis.
- **Alimentação:** 3.3V (via USB-C ou entrada 5V).
- **LED RGB:** Integrado, controlado pela porta GPIO 48.
- **Conectividade:** WiFi 802.11 b/g/n (2.4 GHz) e Bluetooth 5.0.
- **Dimensões:** ~64x27x4,5mm.
  
<img src="fig1.jpg" alt="esp23 pins" width="300">
---

## **Detalhes do Hardware**

### **Processador e Memória**
- **Processador:** Xtensa 32-Bits LX7 Dual Core.
- **Memória SRAM:** 512 KB.
- **Memória Flash:** 8 MB QD (Quad, 4 bits simultâneos para transferência).

### **Alimentação e Conectores**
- **Tensão de Alimentação:** 3,0 a 3,6 VDC.
- **Conector:** USB-C com suporte a OTG e JTAG.
- **Botões:** BOOT e Reset.

### **LEDs Indicativos**
- **Vermelho:** Indica alimentação conectada (3.3V).
- **Verde:** Associado ao TX e botão Reset.
- **Azul:** Pisca ao receber dados (RX).

### **GPIOs**
- 36 GPIOs configuráveis para diversas interfaces:
  - **UART**, **SPI**, **I2C**, **I2S**, **PWM**, **LCD**, **DVP**, etc.

---

## **Como Programar**

1. **Configuração Inicial:**
   - Conecte o módulo via USB-C à porta destacada como "COM".
   - Instale o suporte para ESP32 na **Arduino IDE**:
     - Vá em **Ferramentas > Gerenciador de Placas > ESP32** e instale o pacote.

2. **Selecione a Placa:**
   - Escolha a opção **ESP32S3 Dev Module**.

3. **Carregar o Exemplo:**
   - Vá para **Arquivos > Exemplos > ESP32 > GPIO > BlinkRGB**.
   - Faça o upload do código.

4. **Teste:**
   - O LED RGB embutido alternará entre cores (vermelho, verde, azul, etc.).

---

## **Diagrama de Componentes**

![Diagrama de Componentes ESP32-S3](datasheet%20ESP32-S3-WROOM-1.pdf)

- **Antena Integrada:** Ideal para conectividade WiFi e Bluetooth.
- **Porta USB-C:** Suporte a OTG e debug.
- **Barra de Pinos:** Conexões para jumpers ou soldagem.

---

## **Especificações Técnicas**

| **Especificação**             | **Descrição**                              |
|-------------------------------|--------------------------------------------|
| **Módulo**                    | ESP32-S3-WROOM-1                          |
| **Processador**               | Xtensa 32-Bits LX7 Dual Core              |
| **Memória SRAM**              | 512 KB                                    |
| **Memória Flash Externa**     | 8 MB QD                                   |
| **Tensão de Alimentação**     | 3,0 a 3,6 VDC                             |
| **Tensão de Nível Lógico**    | 3,3 VDC (não tolera 5V)                   |
| **Corrente de Consumo (típica)** | 41 mA                                    |
| **Corrente de Consumo (máxima)** | 56 mA                                    |
| **WiFi**                      | 802.11 b/g/n (2.4 GHz)                    |
| **Segurança WiFi**            | WPA/WPA2/WPA2-Enterprise/WPS              |
| **Bluetooth LE**              | Bluetooth 5.0, Bluetooth Mesh             |
| **Interfaces**                | UART, SPI, SDIO, I2C, I2S, PWM, LCD, DVP  |
| **Temperatura de Trabalho**   | -40° a +85°C                              |
| **GPIOs Programáveis**        | 36                                        |
| **Dimensões**                 | ~64x27x4,5 mm                             |
| **Peso**                      | 8,5 g                                     |

---

# Documentação do Código: BLE Scan com Controle de LED RGB

### Protótipo

<img src="prototipo.jpeg" alt="Prototipo" width="400">

## Resumo
Este código implementa a funcionalidade de varredura de dispositivos BLE (Bluetooth Low Energy) utilizando um ESP32. Além disso, controla um LED RGB para indicar diferentes estados durante a execução.

## Funcionalidades
1. **Varredura de dispositivos BLE:**
   - Detecta dispositivos BLE próximos.
   - Calcula a distância aproximada com base no RSSI.
   - Filtra dispositivos a mais de 5 metros.
   - Ordena dispositivos por distância em ordem crescente.

2. **Indicação de estados por LED RGB:**
   - **Vermelho:** Nenhum dispositivo encontrado.
   - **Azul:** Dispositivos encontrados.
   - **Verde:** Dispositivo próximo (menos de 1 metro).

3. **Saída Serial:**
   - Exibe os dispositivos encontrados em uma tabela, incluindo:
     - Nome do dispositivo.
     - Endereço MAC.
     - RSSI.
     - Distância calculada (em metros).

## Fluxo do código

### Varredura BLE:

    * Realiza a varredura por 5 segundos.
    * Filtra dispositivos além de 5 metros.

### Ordenação e Exibição:

    * Ordena dispositivos por distância em ordem crescente.
    * Exibe os dispositivos em uma tabela na saída serial.

### Controle do LED RGB:

    * Determina a cor com base nos dispositivos detectados:
       *  Verde: Dispositivo próximo 
       *  Azul: Dispositivos encontrados.
       *  Vermelho: Nenhum dispositivo.

### Atraso:

    Aguarda 5 segundos antes da próxima varredura.
---
## Saida serial do ESP32 

Iniciando varredura BLE...

Dispositivos encontrados (ordem por distância):

| Dispositivo | MAC               | RSSI  | Distância (m) |
|-------------|-------------------|-------|---------------|
|             | ef:1d:5a:03:aa:4d | -79   | 8.65          |
|             | 10:3e:9d:bc:a1:b9 | -79   | 8.65          |
|             | d5:8f:86:b1:28:dd | -81   | 10.47         |
|             | 7f:3d:90:af:5a:c4 | -81   | 10.47         |
|             | 72:e7:18:8c:51:94 | -82   | 11.49         |
|             | de:c8:10:dc:12:04 | -82   | 11.49         |
|             | 73:2b:d5:75:23:f5 | -82   | 11.49         |
|             | 1c:08:b8:44:d5:d7 | -82   | 11.49         |
|             | 46:6c:83:08:1c:14 | -85   | 15.13         |
|             | c2:22:77:97:a1:63 | -85   | 15.13         |
|             | 60:7c:9e:28:be:4e | -86   | 16.55         |
|             | d1:0a:47:62:75:89 | -87   | 18.08         |
|             | 28:f5:fb:cf:3f:d5 | -87   | 18.08         |
|             | 4e:47:19:a5:70:38 | -88   | 19.73         |
|             | 3e:87:6a:81:14:91 | -91   | 25.52         |
|             | d0:95:68:a5:01:49 | -91   | 25.52         |
|             | 36:b9:72:9b:25:b1 | -91   | 25.52         |
|             | de:2d:c4:6e:2d:5e | -91   | 25.52         |
|             | 32:64:c2:ff:a1:bd | -92   | 27.75         |
|             | f8:64:df:11:03:56 | -94   | 32.74         |
|             | f0:e8:8d:be:9e:7a | -95   | 35.51         |
|             | 7a:37:8d:36:91:0d | -97   | 41.68         |
----------------------------------------------



