#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string.h>
#include "bus_common.h"
using namespace std;

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool newOilSensorData = false;

long lastMsg = 0;
String receiveString;
// Eindeutige UUIDs für den UART-Service
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

void BUS_output(uint8_t data[],uint8_t len)
{

      pTxCharacteristic->setValue(data,len);
      pTxCharacteristic->notify(); // Sende Wert an App
}

void BUS_outputStr(String data)
{
      String transData = data + "\r" + "\n";
      //pTxCharacteristic->setValue(data);
      pTxCharacteristic->setValue(transData);
      pTxCharacteristic->notify(); // Sende Wert an App
}

void BUS_outputUint16_t(uint16_t data)
{
      //pTxCharacteristic->setValue(data);
      pTxCharacteristic->setValue(data);
      pTxCharacteristic->notify(); // Sende Wert an App
}

// Callback-Funktionen für Verbindungsstatus
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};


// Callback-Funktionen für empfangene Daten
class MyCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic) {
   // String rxValue = pCharacteristic->getValue();
      receiveString= pCharacteristic->getValue();
      newOilSensorData = true;  
    }
};


void initBTConnection(String Modulename)
{
    // Create the BLE Device
    BLEDevice::init(Modulename);

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    if(!pServer) {
        delay(1000);
        ESP.restart();
    }
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    if(!pTxCharacteristic) {
        //Serial.println("Error creating TX characteristic");
        delay(1000);
        ESP.restart();
    }
                        
    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE
    );
    if(!pRxCharacteristic) {
        //Serial.println("Error creating RX characteristic");
        delay(1000);
        ESP.restart();
    }

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    //Serial.println("Waiting a client connection to notify...");

}


void loopfunction()
{
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        //Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
        //Serial.println("Connecting");
    }
}

String bus_getReceiveString()
{
    newOilSensorData = false;
    return receiveString;
}

bool bus_AreNewDataThere()
{
    return newOilSensorData;
}
