
#include <SPI.h>

#include <Client.h>
#include <SdFat.h>
#include <Ethernet.h>
#include <Server.h>
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#include <stdio.h>
#include <Wire.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <Log_Message.h>
#include <Fan.h>
#include <LogDisplay.h>


#include <IPersistable.h>
#include <SimpleDevice.h>
#include <Global_MessageId.h>
#include <MCP_Message.h>
#include <Connector.h>
#include <MCP_Interpreter.h>
#include <MCP_Methods.h>
#include <Call_Message.h>
#include <Result_Message.h>
#include <WorkQueue.h>
#include <ITemperaturSensor.h>

#include <Log.h>
#include <Loggable.h>
#include <IO.h>
#include <Led.h>
#include <Device.h>
#include <DeviceManager.h>
#include <iterator> 
#include <list> 
#include <map>
#include <SolidStateRelay.h>
#include <pnew.cpp>
#include <Sensor.h>
#include <Actor.h>
#include <avr/io.h>
#include <UnifiedFactory.h>
#include <StringUtility.h>
#include <AlarmSystem.h>
#include <MovementSensor.h>
#include <Connection.h>
#include <ConnectionType.h>
#include <MemoryFree.h>
#include <Ultrasonic.h>
#include <MCP_MessageObserver.h>
#include <C_ControlTemperatureSensor.h>
#include <MCP_MessageListener.h>
#include <PrecisionLightSensorPhidget.h>
#include <ILightSensor.h>
#include <TemperatureSensorPhidget.h>
#include <MotionSensorPhidget.h>
#include <Device_Message.h>
#include <ILightSensor.h>
#include <Rolladen.h>
#include <Light.h>
#include <PowerOutlet.h>
#include <Heater.h>
#include <SystemLogPreferences.h>
#include <str_cmp.h>
#include <SmartPointer.h>
#include <memory>
#include <glcd.h>
#include <fonts/allFonts.h>
#include <bitmaps/allBitmaps.h>

MCP_MessageObserver *messageObserver;

/*void InitAlarmSystem()
{
  MovementSensor* sensor = new MovementSensor();
  sensor->setIOPins(11,12);
  sensor->setId(3);
  Log::serial("sensor init");
  SolidStateRelay *ssr = new SolidStateRelay(11,false);
  ssr->setIOPin(2);
  ssr->setId(2);
  Log::serial("ssr init");
  DeviceManager *deviceManager = DeviceManager::getInstance();
  Log::serial("get Instance");
  deviceManager->addActor(ssr);
  deviceManager->addSensor(sensor);
  Log::serial("devicemanager add");
  AlarmSystem* alarmSystem = new AlarmSystem();
  alarmSystem->setName("AlarmSystem");
  alarmSystem->setId(1);
  alarmSystem->setSirene(ssr);
  alarmSystem->setRangeSensor(sensor);
  deviceManager->addDevice(alarmSystem);
  Log::serial("alarmsystem init");
}

void InitSimpleDevice()
{
  PrecisionLightSensorPhidget* sensor = new PrecisionLightSensorPhidget();
  sensor->setPin(A4);
  sensor->setId(4);
  
  TemperatureSensorPhidget* tempSensor = new TemperatureSensorPhidget();
  tempSensor->setPin(A3);
  tempSensor->setId(10);
  
  MotionSensorPhidget* motionSensor = new MotionSensorPhidget();
  motionSensor->setPin(A4);
  motionSensor->setId(11);
  
  Log::serial("sensor init");
  DeviceManager *deviceManager = DeviceManager::getInstance();
  Log::serial("get Instance");
  deviceManager->addSensor(sensor);
  deviceManager->addSensor(tempSensor);
  deviceManager->addSensor(motionSensor);
  Log::serial("devicemanager add");
  SimpleDevice* simpleDevice = new SimpleDevice();
  simpleDevice->setName("simpleDevice");
  simpleDevice->setId(5);
  simpleDevice->setSensor(sensor);
  simpleDevice->setTemperatureSensor(tempSensor);
  simpleDevice->setMovementSensor(motionSensor);
  deviceManager->addDevice(simpleDevice);
  Log::serial("simpleDevice init");
}

void initRolladen()
{
  Rolladen* rolladen = new Rolladen();
  rolladen->setId(11);
  rolladen->setName("Rolladen");
  
  PrecisionLightSensorPhidget* sensor = new PrecisionLightSensorPhidget();
  sensor->setPin(A4);
  sensor->setId(13);
  
  SolidStateRelay* ssr = new SolidStateRelay();
  ssr->setIOPin(13);
  ssr->setId(14);
  
  rolladen->setSSRUp(ssr);
  rolladen->setSSRDown(ssr);
  rolladen->setLightSensor(sensor);
  DeviceManager::getInstance()->addSensor(sensor);
  DeviceManager::getInstance()->addActor(ssr);
  DeviceManager::getInstance()->addDevice(rolladen);
}

void initLight()
{
  PrecisionLightSensorPhidget* sensor = new PrecisionLightSensorPhidget();
  sensor->setPin(A4);
  sensor->setId(15);
  
  SolidStateRelay* ssr = new SolidStateRelay();
  ssr->setIOPin(13);
  ssr->setId(16);
  
  Light* light = new Light();
  light->setName("Lampe");
  light->setId(17);
  light->setSSR(ssr);
  light->setLightSensor(sensor);
  
  
  DeviceManager::getInstance()->addSensor(sensor);
  DeviceManager::getInstance()->addActor(ssr);
  DeviceManager::getInstance()->addDevice(light);
}

void initPowerOutlet()
{
  
  SolidStateRelay* ssr = new SolidStateRelay();
  ssr->setIOPin(2);
  ssr->setId(18);
  
  PowerOutlet* po = new PowerOutlet();
  po->setSSR(ssr);
  po->setName("PowerSource");
  po->setId(20);
  
  DeviceManager::getInstance()->addActor(ssr);
  DeviceManager::getInstance()->addDevice(po);
}
void initHeater()
{
  SolidStateRelay* ssr = new SolidStateRelay();
  ssr->setIOPin(2);
  ssr->setId(12);
  ssr->setName("SSR");
  
  Heater* heater = new Heater();
  heater->setId(25);
  heater->setName("Heizkessel");
  heater->setSSR(ssr);
  
  TemperatureSensorPhidget* tempSensor = new TemperatureSensorPhidget();
  tempSensor->setPin(A3);
  tempSensor->setId(10);
  heater->setTemperaturSensor(tempSensor);
  
   DeviceManager::getInstance()->addSensor(tempSensor);
  DeviceManager::getInstance()->addActor(ssr);
  DeviceManager::getInstance()->addDevice(heater);
  
}

void initFan()
{
  SolidStateRelay* ssr = new SolidStateRelay();
  ssr->setIOPin(2);
  ssr->setId(50);
  ssr->setName("SSR");
  
  Fan* f = new Fan();
  f->setId(26);
  f->setName("Fan");
  f->setSSR(ssr);
  
  TemperatureSensorPhidget* tempSensor = new TemperatureSensorPhidget();
  tempSensor->setPin(A3);
  tempSensor->setId(99);
  f->setTemperaturSensor(tempSensor);
  
   DeviceManager::getInstance()->addSensor(tempSensor);
  DeviceManager::getInstance()->addActor(ssr);
  DeviceManager::getInstance()->addDevice(f);
  
}*/

void setup()
{
  wdt_enable(WDTO_8S);
  Serial.begin(115200);
  Log::serial("init");
  messageObserver = MCP_MessageObserver::getInstance();
  //InitAlarmSystem();
  //InitSimpleDevice(); 
  //initRolladen();
  //initLight();
  //initPowerOutlet();
  //initHeater();
  //initFan();
  messageObserver->observeSerialMessages(true);
  messageObserver->observeEthernetMessages(true);
  messageObserver->observeADKMessages(true);
  messageObserver->subscribeListener();
  
  //delay(200);
  DeviceManager::getInstance()->readFromSdCard();
  
}

void loop()
{
  //Log::serial("loop");
  messageObserver->checkForMessages();
  //delay(200);
  
  //Serial.print("freeMemory()=");
  //Serial.println(freeMemory());
  //AlarmSystem* alarmSystem = (AlarmSystem*) DeviceManager::getInstance()->getDeviceById(1);
  //alarmSystem->doWork();
  WorkQueue::getInstance()->doWork();
  wdt_reset();
}



