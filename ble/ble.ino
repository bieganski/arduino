
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "d9229e80-e0ef-49c5-822b-0dfc5b61ce6d"
#define CHARACTERISTIC_UUID "f805b93f-a1cd-416d-85ce-f84dc1399737"

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    BLEDevice::init("Long name works now");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

    pCharacteristic->setValue("Hello World says Neil");

    pService->start();
// BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}


void loop() {
    delay(2222);
}
