#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// Eindeutige UUIDs für den UART-Dienst (Nordic UART Service Standard)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define RX_UUID                "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define TX_UUID                "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// Status-Überwachung für die Verbindung
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

// Callback für empfangene Daten vom Smartphone/PC
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String rxValue =  pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        for (int i = 0; i < rxValue.length(); i++) {
        }
      }
    }
};

void setup() {

  // BLE-Gerät initialisieren
  BLEDevice::init("ESP32-S3-UART");

  // BLE-Server erstellen
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // BLE-Dienst erstellen
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // TX-Charakteristik erstellen (Senden zum Smartphone)
  pTxCharacteristic = pService->createCharacteristic(
                        TX_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  // RX-Charakteristik erstellen (Empfangen vom Smartphone)
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                                           RX_UUID,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Dienst starten
  pService->start();

  // Sichtbarkeit (Advertising) starten
  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  Serial.println("Warte auf Bluetooth-Verbindung...");
}

void loop() {
    // Wenn ein Gerät verbunden ist, senden wir alle 2 Sekunden eine Nachricht
    if (deviceConnected) {
        String message = "Hallo von ESP32-S3! Zeit: " + String(millis() / 1000) + "s\n";
        
        pTxCharacteristic->setValue(message.c_str());
        pTxCharacteristic->notify(); // Nachricht pushen
        
        Serial.print("Gesendet: " + message);
        delay(2000); 
    }

    // Verbindung verloren: Sichtbarkeit neu starten
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // Dem BLE-Stack Zeit geben
        pServer->startAdvertising(); 
        Serial.println("Verbindung verloren. Suche erneut...");
        oldDeviceConnected = deviceConnected;
    }
    
    // Neue Verbindung aufgebaut
    if (deviceConnected && !oldDeviceConnected) {
        Serial.println("Gerät erfolgreich verbunden!");
        oldDeviceConnected = deviceConnected;
    }
}