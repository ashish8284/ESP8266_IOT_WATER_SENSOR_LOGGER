//TX & RX Pin assignment
int Rx = 13; 
int Tx = 12;
int DE_RE = 4; // For MAX485 chip

//Wifi router Credentials
const char* ssid             = "JioFiber-pPmqQ_4g"; // SSID
const char* passuint16_t     = "987654321"; //Password

//MQTT Server Setting
bool MQTT_Enable = 0;
int Re_Connect_Interval = 60000;
const char* mqtt_server      = "";
const char* mqttUser         = "";
const char* mqttPassuint16_t = "";
const char* mqttClientid     = "ABCD";
unsigned long  Window_Time = 5000;

//Settings for AP Mode
const char* AP_ssid             = "Tech_Sensor";
const char* AP_passuint16_t     = "12345678";
IPAddress AP_IP(192, 168, 11, 4);
IPAddress AP_gateway(192, 168, 11, 1);
IPAddress AP_subnet(255, 255, 255, 0);

//Adaftruit.io credential
#define AIO_USERNAME    ""
#define AIO_KEY         ""

//Adafruit Setting
bool Ada_MQTT_Enable = 0;
unsigned long AdaMqttDly_Window = (1000 *60)* 1;

//Modbus Slave address
byte Start_ID = 1;
byte End_Id = 1;
