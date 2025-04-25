 // Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class RELAY {
  public:
    byte pin;       //GPIO
    boolean state;  //state of relay
  private:
    boolean sw_mode; // Relay as Normally Open (NO)=0, Normally Close (NC)=1
  public:
    RELAY(byte pin) {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->pin = pin;
      init();
    }
    void init() {
      pinMode(pin, OUTPUT);
      // Always try to avoid duplicate code.
      // Instead of writing digitalWrite(pin, LOW) here,
      // call the function off() which already does that
      sw_mode=LOW;
      off();
    }

    void on() {
      digitalWrite(pin, HIGH);
      state=HIGH;
    }

    void off() {
      digitalWrite(pin, LOW);
      state=LOW;
    }

    void toggle() {
      if (state==HIGH) {
        digitalWrite(pin, LOW);
        state=LOW;
      }
      else if (state==LOW) {
        digitalWrite(pin, HIGH);
        state=HIGH;
      }
    }

//mode=0 OFF, mode=1 ON, mode=2 toggle
    void rlswitch(byte swmode) {
            if (swmode==0) {
              off();
            }
            if (swmode==1) {
              on();
            }
            if (swmode==2) {
              toggle();
            }
    }
}; // don't forget the semicolon at the end of the class

RELAY Relay1(25);
RELAY Relay2(26);
RELAY Relay3(33);
RELAY Relay4(32);

class BUTTON {
  public:
    byte pin;
    byte state;
  private:  
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 100;
  public:
    BUTTON(byte pin) {
      this->pin = pin;
      lastReading = LOW;
      init();
    }
    void init() {
      pinMode(pin, INPUT);
      update();
    }
    void update() {
      // You can handle the debounce of the button directly
      // in the class, so you don't have to think about it
      // elsewhere in your code
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        // Update the 'state' attribute only if debounce is checked
        state = newReading;
      }
      lastReading = newReading;
    }
    
    byte getState() {
      update();
      return state;
    }
    bool isPressed() {
      return (getState() == HIGH);
    }
}; // don't forget the semicolon at the end of the class

BUTTON button1(34);
BUTTON button2(35);
BUTTON button3(36);
BUTTON button4(39);

// Replace with your network credentials
const char* ssid = "[SSID NETWORK]";
const char* password = "[PASSWORD NETWORK]";

const char* PARAM_INPUT_1 = "relay";  
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
  xhr.send();
}</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
      String relayStateValue = relayState(Relay1.pin);
      buttons+= "<h4>Relay 1</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=1"+ relayStateValue +"><span class=\"slider\"></span></label>";
      relayStateValue = relayState(Relay2.pin);
      buttons+= "<h4>Relay 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=2"+ relayStateValue +"><span class=\"slider\"></span></label>";
      relayStateValue = relayState(Relay3.pin);
      buttons+= "<h4>Relay 3</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=3"+ relayStateValue +"><span class=\"slider\"></span></label>";
      relayStateValue = relayState(Relay4.pin);
      buttons+= "<h4>Relay 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=4"+ relayStateValue +"><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

String relayState(int pin_N){
    if(digitalRead(pin_N)){
      return "";
    }
    else {
      return "checked";
    }
 
  return "";
}

void action1() {
  if (digitalRead(button1.pin)==0){
  volatile byte buttonstate=digitalRead(button1.pin);
  delay(100); 
    if(digitalRead(button1.pin)==0){
      Relay1.toggle();
    }
  }
}

void action2() {
  if (digitalRead(button2.pin)==0){
  volatile byte buttonstate=digitalRead(button2.pin);
  delay(100); 
    if(digitalRead(button2.pin)==0){
      Relay2.toggle();
    }
  }
}

void action3() {
  if (digitalRead(button3.pin)==0){
  volatile byte buttonstate=digitalRead(button3.pin);
  delay(100); 
    if(digitalRead(button3.pin)==0){
      Relay3.toggle();
    }
  }
}

void action4() {
  if (digitalRead(button4.pin)==0){
  volatile byte buttonstate=digitalRead(button4.pin);
  delay(100); 
    if(digitalRead(button4.pin)==0){
      Relay4.toggle();
    }
  }
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  attachInterrupt(digitalPinToInterrupt(button1.pin),action1,FALLING);
  attachInterrupt(digitalPinToInterrupt(button2.pin),action2,FALLING);
  attachInterrupt(digitalPinToInterrupt(button3.pin),action3,FALLING);
  attachInterrupt(digitalPinToInterrupt(button4.pin),action4,FALLING);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}
  
void loop() {

}