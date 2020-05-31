// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

// Define sensors
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED pins
int HumidifierPin = D2;
int HeaterPin = D3;
int CoolerPin = D4;
int Buzzer = D5;

// variables
double temp = 0.0;
double hum = 0.0;
double Temperature = 0.0;
double Humidity = 0.0;
double MaxTemp = 30.0;
double MinTemp = 10.0;
int Humidifier_status = 0;
int AirConditioner_status = 0;

// Setup
void setup() 
{
    pinMode(HumidifierPin, OUTPUT);
    pinMode(HeaterPin, OUTPUT);
    pinMode(CoolerPin, OUTPUT);
    pinMode(Buzzer, OUTPUT);
    digitalWrite(HumidifierPin, LOW);
    digitalWrite(HeaterPin, LOW);
    digitalWrite(CoolerPin, LOW);
    digitalWrite(Buzzer, LOW);
    
    dht.begin();
    
    Particle.variable("Temperature", &Temperature, DOUBLE);
    Particle.variable("Humidity", &Humidity, DOUBLE);
    Particle.variable("Humidifier", &Humidifier_status, INT);
    Particle.variable("AirConditioner", &AirConditioner_status, INT);
    
    Particle.subscribe("Humidifier_Controller", humidifierController, MY_DEVICES);
    Particle.subscribe("AirConditioner_Controller", airConditionerController, MY_DEVICES);
    Particle.subscribe("Guess_Notifications", NotifyUser, MY_DEVICES);
    Particle.subscribe("Max_Temperature_Changed", roomMaxTemperatureController, MY_DEVICES);
    Particle.subscribe("Min_Temperature_Changed", roomMinTemperatureController, MY_DEVICES);
    
}

//Main loop for collecting data from DHT22 sensor
void loop()
{
    temp = dht.getTempCelcius();
    hum = dht.getHumidity();
    if (isnan(temp) || isnan(hum) || temp<= -10 || temp >= 50 || hum >= 100 || hum <= 0) return;
    Temperature = temp;
    Particle.publish("Room_Temperature", String(temp));
    Humidity = hum;
    Particle.publish("Room_Humidity", String(hum));
    //TemperatureController(temp, MaxTemp, MinTemp);
    delay(5000);
}

// Automatic Air Conditioner controller
void TemperatureController(double Temp, double Max, double Min){
    if (Temp >= Max){
        airConditioner(-1);
    }
    else if (Temp <= Min){
        airConditioner(1);
    }
    else{
        airConditioner(0);
    }
}
// Simulated Humidifier using Green LED
void humidifierController(const char *event, const char *data)
{
    if(strcmp(data, "ON") == 0)
    {
        Humidifier_status = 1;
        digitalWrite(HumidifierPin, HIGH);
    }
    else if(strcmp(data, "OFF") == 0)
    {
        Humidifier_status = 0;
        digitalWrite(HumidifierPin, LOW);
    }
}

// AirConditioner function
void airConditioner(int cmd){
    AirConditioner_status = cmd;
    if (cmd == 1){
        
        digitalWrite(HeaterPin, HIGH);
        digitalWrite(CoolerPin, LOW);
    }
    else if (cmd == -1){
        digitalWrite(CoolerPin, HIGH);
        digitalWrite(HeaterPin, LOW);
    }
    else if (cmd == 0){
        digitalWrite(HeaterPin, LOW);
        digitalWrite(CoolerPin, LOW);
    }
}
// Simulated Air Conditioner using Red & Blue LED
void airConditionerController(const char *event, const char *data)
{
    if(strcmp(data, "HEAT") == 0)
    {
        airConditioner(1);
    }
    else if(strcmp(data, "COOL") == 0)
    {
        airConditioner(-1);
    }
    else if(strcmp(data, "OFF") == 0)
    {
        airConditioner(0);
    }
}

// Send to IFTTT trigger
void NotifyUser(const char *event, const char *data)
{
    if(strcmp(data, "visitor") == 0)
    {
        Particle.publish("User_Notifications", "Visitor");
        digitalWrite(Buzzer, HIGH);
        delay(1000);
        digitalWrite(Buzzer, LOW);
        delay(1000);
        digitalWrite(Buzzer, HIGH);
        delay(1000);
        digitalWrite(Buzzer, LOW);
        
    }
    else if(strcmp(data, "delivery") == 0)
    {
        Particle.publish("User_Notifications", "Delivery");
        digitalWrite(Buzzer, HIGH);
        delay(3000);
        digitalWrite(Buzzer, LOW);
    }
}

// get Min, Max Temperature for controlling
void roomMaxTemperatureController(const char *event, const char *data)
{
    double value;
    if ((value = atof(data)) == 1){
        MaxTemp = temp;
    }
}

void roomMinTemperatureController(const char *event, const char *data)
{
    double value;
    if ((value = atof(data)) == 1){
        MinTemp = temp;
    }
}
