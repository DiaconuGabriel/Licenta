#include <lvgl.h>
#include <TFT_eSPI.h>
#include <CST816S.h>
#include <ui.h>
#include <ArduinoBLE.h>
#include <WiFi.h>
#include "mpu.h"
#include "uUnixDate.h"
#include "MAX30105.h"
#include "heartRate.h"
#include <DS1307.h>
#include <LittleFS.h>
#include <Firebase_ESP_Client.h> 
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//------------------------------------------------//
//                  Task handle                   //
//------------------------------------------------//

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;
TaskHandle_t Task5;
TaskHandle_t Task6;
TaskHandle_t Task7;

//------------------------------------------------//
//                       Ble                      //
//------------------------------------------------//

BLEService Service("19B10000-E8F2-537E-4F6C-D104768A1214"); // UUID serviciu
BLEStringCharacteristic sendCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify,50); // UUID caracteristica raspuns
BLEStringCharacteristic receivenameCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify,50); // UUID caracteristica nume
BLEStringCharacteristic receivecredentialsCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify,50); // UUID caracterisstica credentiale 

bool isBleOn = false;
bool recievedcred = false;
bool esprejected = false;

//------------------------------------------------//
//                 Time variables                 //
//------------------------------------------------//

String zile[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
String luni_an[12] = {"IAN", "FEB", "MAR", "APR", "MAI", "IUN", "IUL", "AUG", "SEP", "OCT", "NOV", "DEC"}; 

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7200;
const int daylightOffset_sec = 3600;

uint8_t sec, minute, hour, day, month;
uint16_t year;

//------------------------------------------------//
//                 MPU variables                  //
//------------------------------------------------//

float magcaldata[12]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
bool was_calibrated = true;
float now,deltat,last;
uint16_t kcal;
float steps,distance;
bool wasrestarted;
bool itwastosoon;

bool possiblesteph = false;
bool possiblestepl = false;
int timerlast = 0;

double x1 = 0 ,x2 = 0 ,x3 = 0;
double y = 0 ,y2 = 0 ,y3 = 0;

float x1_hp = 0, x2_hp = 0, x3_hp = 0;
float y1_hp = 0, y2_hp = 0, y3_hp = 0;

float accel_tresh_high = 0.82;
float accel_tresh_low = -0.82;

//------------------------------------------------//
//                 Variablie lvgl                 //
//------------------------------------------------//

static const uint8_t screenWidth  = 240;
static const uint8_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;

static lv_color_t buf[ screenWidth * screenHeight / 10 ];
static lv_color_t buf1[ screenWidth * screenHeight / 10 ];

//------------------------------------------------//
//               Instantieri clase                //
//------------------------------------------------//

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

TwoWire senzorii2c = TwoWire(1);
MPU9250 mpu(senzorii2c);
CST816S mytouch(1, 0, 41, 42);
MAX30105 particleSensor;
DS1307 ceas(senzorii2c);

//------------------------------------------------//
//          Variabile pentru senzor puls          //
//------------------------------------------------//

int i = 0;
const uint8_t WINDOW_SIZE=10;
int32_t window[WINDOW_SIZE];  // Array to hold recent samples
int windowIndex = 0;  // Index of the current sample
int32_t sum = 0;  // Sum of the samples in the window

int heartbeatCount = 0;
unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long duration = 0;
// long lastBeat = 0;
uint8_t heartRate;

int32_t redDC = 0;
int32_t irDC = 0;

bool errorwithpulse = false;
// bool masoara_puls = false;
uint8_t numar_masuratori_puls = 0;

uint8_t spo2;

//------------------------------------------------//
//          Variabile pentru fisiere              //
//------------------------------------------------//

File salvarifile;
File wififile;
File magnetometerfile;
File magnetometerfiletest; // test mag
String lista_wifi[200]={};

//------------------------------------------------//
//             Variabile pentru wifi              //
//------------------------------------------------//

int lista_wifi_var = -2;
String cred_name, cred_pass;
bool este_in_fisier;
bool conex_show = false;
bool numar_deconectari = false;

//------------------------------------------------//
//                    Firebase                    //
//------------------------------------------------//

const char* DATABASE_URL = "********";  // aici trebuie setate variabilele pentru baza de date
const char* API_KEY =  "********";
const char* USER_EMAIL =  "********";
const char* USER_PASSWORD =  "********";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String uid;

//------------------------------------------------//
//                  Functii lvgl                  //
//------------------------------------------------//

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint8_t w = ( area->x2 - area->x1 + 1 );
    uint8_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, (w * h), true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{     
    // Serial.println(mytouch.available());
    if (mytouch.available()) {
      data->point.x = map(mytouch.data.x,0,240,240,0);
      data->point.y = mytouch.data.y;
      data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

//------------------------------------------------//
//                     Setup                      //
//------------------------------------------------//

void setup()
{ 
  Serial.begin( 115200 );
  wasrestarted = true;

  if (!LittleFS.begin()) {
    // Serial.println("Failed to initialize LittleFS, formatting...");
    LittleFS.format();
  }

  analogWrite(TFT_BL,255);

  senzorii2c.begin(SDA1, SCL1);
  Wire.begin();

  mytouch.begin();
  setpulsesensor();
  ceas.start();
  delay(100);
  particleSensor.shutDown();

  lv_init();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin("fjdslajfdasv", "vasdvasdvlsF");

  tft.begin();  

  lv_disp_draw_buf_init(&draw_buf,buf,buf1,screenWidth*screenHeight / 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  lv_disp_drv_register( &disp_drv );
  disp_drv.draw_buf = &draw_buf;
  disp_drv.flush_cb = my_disp_flush;

  ui_init();
  lv_port_indev_init();

  lv_obj_add_event_cb(ui_butonwifi, deconecteaza, LV_EVENT_SHORT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_Slider1, schimbareluminozitate, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(ui_accepta, trimiteraspunspositiv, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_refuza, trimiteraspunsnegativ, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_butonmasurare, masoarapuls, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_butoncal, calibreazamag, LV_EVENT_SHORT_CLICKED, NULL);

  mpu.setmpu(); // partea de mpu
  mpu.calibrateGyro();

  magnetometerfile = LittleFS.open("/magnetometru.txt", FILE_READ);

  if (!magnetometerfile) {
    Serial.println("Failed to open file for reading");
  }

  for (i=0; i<12; i++){
    String line = magnetometerfile.readStringUntil('\n');
    float calibdate = line.toFloat();
    magcaldata[i] = calibdate;
  }

  magnetometerfile.close();

  mpu.set_cal_mag_data(magcaldata[0],magcaldata[1],magcaldata[2],magcaldata[3],magcaldata[4],magcaldata[5],magcaldata[6],magcaldata[7],magcaldata[8],magcaldata[9],magcaldata[10],magcaldata[11]);

  // Serial.println(magcaldata[0]);
  // Serial.println(magcaldata[1]);
  // Serial.println(magcaldata[2]);
  // Serial.println(magcaldata[3]);
  // Serial.println(magcaldata[4]);
  // Serial.println(magcaldata[5]);
  // Serial.println(magcaldata[6]);
  // Serial.println(magcaldata[7]);
  // Serial.println(magcaldata[8]);
  // Serial.println(magcaldata[9]);
  // Serial.println(magcaldata[10]);
  // Serial.println(magcaldata[11]);

  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  lv_obj_clear_flag(ui_butonbluetooth, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_flag(ui_textecalibrare, LV_OBJ_FLAG_HIDDEN);

  delay(100);
  
  xTaskCreatePinnedToCore(
      UiTask,
      "Task1",
      7000,
      NULL,
      4,
      &Task1,
      1);
  
  xTaskCreatePinnedToCore(
      ClockTask,
      "Task2",
      5000,
      NULL,
      3,
      &Task2,
      1);

  xTaskCreatePinnedToCore(
      IMUTask,
      "Task4",
      8000,
      NULL,
      4,
      &Task4,
      1);

   xTaskCreatePinnedToCore(
      SaveVariablesTask,
      "Task7",
      8000,
      NULL,
      4,
      &Task7,
      1);
}

//------------------------------------------------//
//                    Loop()                      //
//------------------------------------------------//

void loop(){  
  if (isBleOn == true){
    BLE.poll();
  }
  delay(50);
}

//------------------------------------------------//
//                    Tasks                       //
//------------------------------------------------//

int s_a_conectat_fire=0;
void FirebaseTask(void * parameter) {
  for(;;) {
    if (s_a_conectat_fire==0){
      // Serial.println("Am intrat aici");
      config.api_key = API_KEY;

      auth.user.email = USER_EMAIL;
      auth.user.password = USER_PASSWORD;

      config.database_url = DATABASE_URL;
      Firebase.reconnectWiFi(true);

      config.token_status_callback = tokenStatusCallback; 
      
      Firebase.begin(&config, &auth);
      Serial.println("Getting User UID");
      while ((auth.token.uid) == "") {
        Serial.print('.');
        delay(1000);
      }
      uid = auth.token.uid.c_str();
      Serial.print("User UID: ");
      Serial.println(uid);

      s_a_conectat_fire=1;
    }
    if (Firebase.ready()){
      String data_to_send = String(heartRate)+","+String(spo2)+","+String(steps)+","+String(distance)+","+String(kcal);
      String today_date = String(day)+"_"+String(month)+"_"+String(year);
      String ora = String(hour)+"_"+String(minute); 
      if(Firebase.isTokenExpired()){
        Firebase.refreshToken(&config);
      }
    
      if (Firebase.RTDB.push(&fbdo, "/userdata/" + today_date + "/" + ora, data_to_send)) {
        Serial.println("Am trimis datele");
      } else {
        if(Firebase.isTokenExpired()){
          Firebase.refreshToken(&config);
        }
        Serial.println(fbdo.errorReason().c_str());
      }
    }

    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
}

void UiTask( void* pvParameters){
  for(;;){
    lv_task_handler();
    // UBaseType_t stackRemaining1 = uxTaskGetStackHighWaterMark(Task1);

    // Serial.print("  Task1 stack remaining: ");
    // Serial.print(stackRemaining1);
    vTaskDelay(25 / portTICK_PERIOD_MS);
  }
}

void IMUTask( void* pvParameters){
  char text2[6];
  for(;;){
    mpu.getAccelData();

    float accelvector = sqrt(mpu.accx * mpu.accx + mpu.accy *mpu.accy + mpu.accz * mpu.accz);

    // Low-pass filter
    x3 = x2;
    x2 = x1;
    x1 = accelvector;
    y = ((x1 + 2 * x2 + x3) + 94.748 * y2 + (-39.538) * y3) / 59.210; //3 hz 90 hz
    y3 = y2;
    y2 = y;

    // High-pass filter
    x3_hp = x2_hp;
    x2_hp = x1_hp;
    x1_hp = y; 
    y1_hp = ((x1_hp - 2 * x2_hp + x3_hp) + 1.999 * y2_hp + (-0.967) * y3_hp) / 1.034; // 0.5 hz 90hz
    y3_hp = y2_hp;
    y2_hp = y1_hp;

    if(y1_hp * 10 >=accel_tresh_high){
      possiblesteph = true;
    }

    if(y1_hp * 10 <=accel_tresh_low){
      if(possiblesteph == true){
        possiblestepl = true;
      }
    }

    if(possiblesteph == true && possiblestepl == true){
      int timerval1 = millis();
      if (timerval1 - timerlast < 250){
        // Serial.println("Aici");
        itwastosoon = true;
        possiblesteph = false;
        possiblestepl = false;
      }
      if(itwastosoon == false){
        steps++; 
        possiblesteph = false;
        possiblestepl = false;
      }
      itwastosoon = false;
      timerlast = millis();
    }

    if (was_calibrated == false){
      mpu.calibrateMag();
      was_calibrated = true;
      lv_obj_add_flag(ui_textecalibrare, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_butoncal, LV_OBJ_FLAG_CLICKABLE);
      lv_obj_add_event_cb(ui_calibraremagscreen ,ui_event_calibraremagscreen,LV_EVENT_GESTURE,NULL);

      magnetometerfile = LittleFS.open("/magnetometru.txt", FILE_WRITE);             ////// CU ASTA SALVEZI NOUA CONFIGURATIE PENTRU MAGNETOMETRU

      if (!magnetometerfile) {
        Serial.println("Failed to create file");
      }

      magnetometerfile.printf("%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n", mpu.mxh, mpu.myh, mpu.mzh, mpu.mxs, mpu.mys, mpu.mzs, mpu.mxh1, mpu.myh1, mpu.mzh1, mpu.mxh2, mpu.myh2, mpu.mzh2);

      magnetometerfile.close();

      // magnetometerfiletest = LittleFS.open("/magnetometrutest.txt", FILE_WRITE);             ////// CU ASTA SALVEZI NOUA CONFIGURATIE PENTRU MAGNETOMETRU test

      // if (!magnetometerfiletest) {
      //   Serial.println("Failed to create file");
      // }
      // // Write a message to the file
      // magnetometerfiletest.printf("%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n", mpu.mxh, mpu.myh, mpu.mzh, mpu.mxs, mpu.mys, mpu.mzs, mpu.mxh1, mpu.myh1, mpu.mzh1, mpu.mxh2, mpu.myh2, mpu.mzh2, mpu.mxs1, mpu.mys1, mpu.mzs1, mpu.mxs2, mpu.mys2, mpu.mzs2);
    
      // magnetometerfiletest.close();

    }
    if (was_calibrated == true){
      if( lv_scr_act() == ui_busola){
        mpu.getGyroDataCalibrated();
        mpu.getMagDataCalibrated();

        now = micros();
        deltat = (now - last) * 1.0e-6;
        last = now;
        
        mpu.updatempumadgwick(mpu.accx, -mpu.accy, mpu.accz, mpu.gyrox*PI/180, -mpu.gyroy*PI/180, mpu.gyroz*PI/180, mpu.my*10, -mpu.mx*10, -mpu.mz*10, deltat);
        float yaw  = atan2f(2.0f * (mpu.q[1] * mpu.q[2] + mpu.q[0] * mpu.q[3]), mpu.q[0] * mpu.q[0] + mpu.q[1] * mpu.q[1] - mpu.q[2] * mpu.q[2] - mpu.q[3] * mpu.q[3]);
        yaw = (yaw*180/PI)+180+270+25;
        if (yaw>360){
          yaw-=360;
        }
        int yaw1=map(yaw,0,360,360,0);
        // Serial.print(int(yaw)); Serial.print("   ");
        // Serial.println(mpu.mx);
        sprintf(text2, "%d°", int(yaw));

        lv_label_set_text(ui_unghi, text2);
        lv_img_set_angle(ui_imunghi, yaw1*10);
        // Serial.println(deltat);
        if ((yaw >= 337 && yaw < 360) || (yaw >= 0 && yaw < 23)) {
          lv_label_set_text(ui_directie, "N");
        } else if (yaw >= 23 && yaw < 68) {
          lv_label_set_text(ui_directie, "NE");
        } else if (yaw >= 68 && yaw < 113) {
          lv_label_set_text(ui_directie, "E");
        } else if (yaw >= 113 && yaw < 158) {
          lv_label_set_text(ui_directie, "SE");
        } else if (yaw >= 158 && yaw < 203) {
          lv_label_set_text(ui_directie, "S");
        } else if (yaw >= 203 && yaw < 248) {
          lv_label_set_text(ui_directie, "SW");
        } else if (yaw >= 248 && yaw < 293) {
          lv_label_set_text(ui_directie, "W");
        } else if (yaw >= 293 && yaw < 337) {
          lv_label_set_text(ui_directie, "NW");
        }
      }
    }

    distance = steps * 0.65;
    kcal = steps * 0.042;

    if(steps<1000){
      lv_label_set_text(ui_nrpasi, String((int)(steps)).c_str());
      lv_label_set_text(ui_Label9, " ");
    }
    if(steps>1000){
      float text_steps = steps/1000;
      // Serial.println(text_steps);
      lv_label_set_text(ui_nrpasi, String(text_steps).c_str());
      lv_label_set_text(ui_Label9, "k");
    }
    if(distance<1000){
      lv_label_set_text(ui_nrdistanta, String((int)(distance)).c_str());
      lv_label_set_text(ui_kmdisanta, "m");
    }
    if(distance>1000){
      lv_label_set_text(ui_nrdistanta, String((float)(distance/1000)).c_str());
      lv_label_set_text(ui_kmdisanta, "km");
    }
    lv_label_set_text(ui_nrcal, String(kcal).c_str());
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void ClockTask( void* pvParameters){
  for(;;){
    int timerceas = millis();
    if (millis()-timerceas > 60000){
      if (WiFi.status() == WL_CONNECTED){
        set_time();
      }
    }
    ceas.get(&sec, &minute, &hour, &day, &month, &year);
    if(sec == 0 && minute == 0 && hour == 0){
      steps = 0;
    }
    if( lv_scr_act() == ui_ecranceas2){
      if (hour>=10){
        String oradis = String(hour);
        lv_label_set_text(ui_ora1, String(oradis[0]).c_str());
        lv_label_set_text(ui_ora2, String(oradis[1]).c_str());
      }
      if (hour<10){
        lv_label_set_text(ui_ora1, String(0).c_str());
        lv_label_set_text(ui_ora2, String(hour).c_str());
      }
      if (minute<10){
        lv_label_set_text(ui_min1, String(0).c_str());
        lv_label_set_text(ui_min2, String(minute).c_str());
      }
      if (minute>=10){
        String mindis = String(minute);
        lv_label_set_text(ui_min1, String(mindis[0]).c_str());
        lv_label_set_text(ui_min2, String(mindis[1]).c_str());
      }
      if (sec<10){
        lv_label_set_text(ui_sec0, String(0).c_str());
        lv_label_set_text(ui_sec1, String(sec).c_str());
      }
      if (sec>=10){
        String secdis = String(sec);
        lv_label_set_text(ui_sec0, String(secdis[0]).c_str());
        lv_label_set_text(ui_sec1, String(secdis[1]).c_str());
      }
      // Serial.print(hour); Serial.print("  ");Serial.print(minute); Serial.print("  ");Serial.print(sec); Serial.println("  ");
      lv_label_set_text(ui_zisapt, String(zile[ISO_day_of_week(day, month, year)-1]).c_str());
      lv_label_set_text(ui_zi, String(day).c_str());
      lv_label_set_text(ui_luna, String(luni_an[month-1]).c_str());
      lv_label_set_text(ui_an, String(year).c_str());

    }
  vTaskDelay(200 / portTICK_PERIOD_MS); //delay 0.2 sec
  }
}

void PulseTask( void* pvParameters){ 
  for(;;){
      int32_t irValuev = particleSensor.getIR();
      int32_t redValuev = particleSensor.getRed();

      // Serial.println(redValuev);

      if (checkForBeat(movingAverage(redValuev)) == true) {

        heartbeatCount++;

        if (heartbeatCount == 1)
        {
          startTime = millis(); // Start bataie
        }

        if (heartbeatCount == 4)
        {
          endTime = millis();
          duration = endTime - startTime;

          heartRate = (60000.0/duration)*3;
            
          heartbeatCount = 0; //reset

          numar_masuratori_puls++;

          irDC = averageDCEstimator(&irDC, irValuev);  
          // Serial.print(irDC); Serial.print("  ");

          redDC = averageDCEstimator(&redDC, redValuev); 
          // Serial.print(redDC); Serial.print("  ");

          // // Calculate the AC component
          int32_t irAC = irValuev - irDC;
          int32_t redAC = redValuev - redDC;

          // Serial.print(irAC); Serial.print("  ");
          // Serial.println(redAC); //Serial.print("  ");

          float ratio = ((float)redAC / (float)redDC) / ((float)irAC / (float)irDC);
          
          spo2 = 104 - 17 * ratio;

          lv_label_set_text(ui_numarpuls, String(int(heartRate)).c_str());
          lv_arc_set_value(ui_Arc1, int(heartRate));
          lv_label_set_text(ui_puls, String(int(heartRate)).c_str());

          String spo2txt = String(int(spo2))+" "+"%";
          
          lv_label_set_text(ui_Spo2value, spo2txt.c_str());
          lv_arc_set_value(ui_Arc2, int(spo2));
          lv_label_set_text(ui_nrox, String(int(spo2)).c_str());
        }
      }

      if(numar_masuratori_puls == 4){
        lv_obj_add_flag(ui_butonmasurare, LV_OBJ_FLAG_CLICKABLE);
        particleSensor.shutDown();
        numar_masuratori_puls = 0;
        heartbeatCount = 0;
        vTaskDelete(NULL);
      }
    
      if (irValuev < 50000){
        // Serial.print(" deget?");
        heartbeatCount = 0;
      }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void ScanAndReconnTask( void* pvParameters){ 
  for(;;){
    int n  = WiFi.scanNetworks();
    // Serial.println(n);
    if (n == 0) {
      if (isBleOn == false){
        // Serial.println("Nimic nimic");
        esprejected = false;
        startble();
        lv_obj_set_y(ui_Textalerta, 18);
        lv_label_set_text(ui_Textalerta,"Nu ai retea la care sa te conectezi in zona! Bluetooth activat!");
        lv_disp_load_scr(ui_ecranalerte);
        delay(2000);
        lv_disp_load_scr(ui_ecranceas2);
        vTaskDelete(NULL);
      }
    }else {
      for (int fm = 0; fm < n; fm++) {
        // Serial.print(fm + 1);
        // Serial.print(": ");
        for (int ck = 0; ck <= get_number_of_list_elements()-2; ck++){
          if (lista_wifi[ck] == WiFi.SSID(fm)){
            // Serial.println(WiFi.SSID(fm));
            int flj = da_indexul_la_care_se_afla_ssid(WiFi.SSID(fm));
            if (flj == -1){
              Serial.println("Ceva nu e ok!");
            }
            else{
              WiFi.begin(lista_wifi[flj],lista_wifi[flj+1]);
              WiFi.setAutoReconnect(false);
              vTaskDelete(NULL);
            }
          }
        }
        // Serial.print(WiFi.SSID(fm));
        // Serial.print(" (");
        // Serial.print(WiFi.RSSI(fm));
        // Serial.println(")");
        // Serial.println("Nu s-a gasit nici o retea");
      }
    }
    if (isBleOn){
      vTaskDelete(NULL);
    }
    if (isBleOn == false){
      Serial.println("Nici o retea gasita printe celelalte");
      esprejected = false;
      startble();
      lv_obj_set_y(ui_Textalerta, 18);
      lv_label_set_text(ui_Textalerta,"Nu ai retea la care sa te conectezi in zona! Bluetooth activat!");
      lv_disp_load_scr(ui_ecranalerte);
      delay(2000);
      lv_disp_load_scr(ui_ecranceas2);
      vTaskDelete(NULL);
    }
  }
}

void SaveVariablesTask( void* pvParameters){
  for(;;){
    if(wasrestarted == true){
      salvarifile = LittleFS.open("/salvari.txt", FILE_READ);
      
      String linesavefile = salvarifile.readStringUntil('\n');
      steps = linesavefile.toFloat();
      linesavefile = salvarifile.readStringUntil('\n');
      distance = linesavefile.toFloat();
      linesavefile = salvarifile.readStringUntil('\n');
      kcal = linesavefile.toInt();
      linesavefile = salvarifile.readStringUntil('\n');
      uint16_t file_year = linesavefile.toInt();
      linesavefile = salvarifile.readStringUntil('\n');
      uint16_t file_month = linesavefile.toInt();
      linesavefile = salvarifile.readStringUntil('\n');
      uint16_t file_day = linesavefile.toInt();

      Serial.println(steps); Serial.println(distance); Serial.println(kcal); Serial.println(file_year); Serial.println(file_month); Serial.println(file_day);

      ceas.get(&sec, &minute, &hour, &day, &month, &year);

      Serial.println(year); Serial.println(month); Serial.println(day);
      if (file_year != year | file_month != month | file_day != day){
        steps = 0;
        distance = 0;
        kcal = 0;
        // Serial.println("Am schimbat");
      }
      salvarifile.close();
      wasrestarted = false;
    }
    if(wasrestarted == false){
      salvarifile = LittleFS.open("/salvari.txt", FILE_WRITE);
      salvarifile.printf("%f\n%f\n%d\n%d\n%d\n%d\n",steps,distance,kcal,year,month,day);
      salvarifile.close();
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

//------------------------------------------------//
//                  Lvgl events                   //
//------------------------------------------------//

void deconecteaza(lv_event_t *event){
  if(numar_deconectari == false){
    WiFi.disconnect();
    lv_obj_clear_flag(ui_butonwifi, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_state(ui_switchwifi, LV_STATE_CHECKED);
    numar_deconectari = true;
  }
}

void schimbareluminozitate(lv_event_t *event){
    lv_obj_t *ui_Slider1 = lv_event_get_target(event);
    analogWrite(TFT_BL,lv_slider_get_value(ui_Slider1));
}

void trimiteraspunspositiv(lv_event_t *event){
  sendCharacteristic.writeValue(String('1'));
  if(was_calibrated == false){
    lv_disp_load_scr(ui_calibraremagscreen);
  }
  else{
  lv_disp_load_scr(ui_ecranceas2);
  }
}

void trimiteraspunsnegativ(lv_event_t *event){
  sendCharacteristic.writeValue(String('2'));
  esprejected = true;
  if(was_calibrated == false){
    lv_disp_load_scr(ui_calibraremagscreen);  
  }
  else{
  lv_disp_load_scr(ui_ecranceas2);
  }
}

void calibreazamag(lv_event_t *event){
  lv_obj_clear_flag(ui_textecalibrare, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_flag(ui_butoncal, LV_OBJ_FLAG_CLICKABLE);
  was_calibrated = false;
  lv_disp_load_scr(ui_calibraremagscreen);
  lv_obj_remove_event_cb(ui_calibraremagscreen ,ui_event_calibraremagscreen);
}

void masoarapuls(lv_event_t *event){
  lv_obj_clear_flag(ui_butonmasurare, LV_OBJ_FLAG_CLICKABLE);
  particleSensor.wakeUp();
  xTaskCreatePinnedToCore(
      PulseTask,
      "Task3",
      8000,
      NULL,
      4,
      &Task3,
      1);
}

//------------------------------------------------//
//                  Wifi events                   //
//------------------------------------------------//

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){  ////luat din exemple : https://reference.arduino.cc/reference/en/libraries/arduinoble/blecharacteristic.seteventhandler/
  if(wififile){
    wififile.close();
  }
  if (recievedcred == true){
    verifica_daca_exista_in_fisier();
  }
  numar_deconectari = false; 
  conex_show = false;
  recievedcred = false; 
  lista_wifi_var = -2;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  lv_obj_set_y(ui_Textalerta, 45);
  lv_label_set_text(ui_Textalerta,"S-a realizat conexiunea la internet");
  lv_disp_load_scr(ui_ecranalerte);
  if (isBleOn) {
    endble();
  }
  delay(2000);
  lv_disp_load_scr(ui_ecranceas2);
  Serial.println("Connected to AP successfully!");
  lv_obj_add_state(ui_switchwifi, LV_STATE_CHECKED);
  lv_obj_clear_state(ui_switchble, LV_STATE_CHECKED);
  lv_obj_add_flag(ui_butonwifi, LV_OBJ_FLAG_CLICKABLE);
  set_time();
  xTaskCreatePinnedToCore(
      FirebaseTask,
      "Task6",
      10000,
      NULL,
      5,
      &Task6,
      1);
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  WiFi.disconnect();
  numar_deconectari == true;
  s_a_conectat_fire=0;
  read_wifi_list_elements();
  if (Task6 != NULL) {
    vTaskDelete(Task6);
    Task6 = NULL;
  }
  if (conex_show==false){
    if(recievedcred == true){
      lv_obj_clear_state(ui_switchwifi, LV_STATE_CHECKED);
      lv_obj_set_y(ui_Textalerta, 27);
      lv_label_set_text(ui_Textalerta,"Nu s-a putut conecta la internet cu credentialele primite!");
      lv_disp_load_scr(ui_ecranalerte);
      delay(2000);
      lv_disp_load_scr(ui_ecranceas2);
    }
    if(recievedcred == false){
      lv_obj_clear_state(ui_switchwifi, LV_STATE_CHECKED);
      lv_obj_set_y(ui_Textalerta, 45);
      lv_label_set_text(ui_Textalerta,"S-a pierdut conexiunea la internet!");
      lv_disp_load_scr(ui_ecranalerte);
      delay(2000);
      lv_disp_load_scr(ui_ecranceas2);
    }
    conex_show = true;
  }
  xTaskCreatePinnedToCore(
    ScanAndReconnTask,
    "Task5",
    10000,
    NULL,
    5,
    &Task5,
    1);

  if(recievedcred == true){
    recievedcred = false;
  }
}

//------------------------------------------------//
//                  Ble events                    //
//------------------------------------------------//

void receivenameCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic){
  if (receivenameCharacteristic.value()) {
    String devicename = String(receivenameCharacteristic.value());
    // Serial.println(devicename);
    lv_label_set_text(ui_numedispozitiv, devicename.c_str());
    lv_disp_load_scr(ui_ecranbluetooth);
    esprejected = false;
  }
}

void receivecredentialsCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic){
  if (central){
    conex_show = false;
    if (receivecredentialsCharacteristic.value()) {
      String credentiale = String(receivecredentialsCharacteristic.value());
      recievedcred = true;

      int commaIndex = credentiale.indexOf(',');
      cred_name = credentiale.substring(0, commaIndex);
      cred_pass = credentiale.substring(commaIndex + 1);

      // Serial.println(cred_name.length());
      // Serial.println(cred_pass.length());

      WiFi.begin(cred_name,cred_pass);
      WiFi.setAutoReconnect(false);
    }
  }
}

void blePeripheralConnectHandler(BLEDevice central) {  ///luat din exemple : https://reference.arduino.cc/reference/en/libraries/arduinoble/ble.seteventhandler/
  // Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // Serial.print("Disconnected event, central: ");
  if (recievedcred == false && esprejected == false){
    lv_obj_set_y(ui_Textalerta, 45);
    lv_label_set_text(ui_Textalerta,"Dispozitivul s-a deconectat");
    lv_disp_load_scr(ui_ecranalerte);
    delay(2000);
    lv_disp_load_scr(ui_ecranceas2);
  }
}

//------------------------------------------------//
//                   Functii Ble                  //
//------------------------------------------------//

void startble(){
  lv_obj_clear_flag(ui_butonwifi, LV_OBJ_FLAG_CLICKABLE);
  if (!BLE.begin()){
    // Serial.print("Failed to initialize ble");
    while(1);
  }

  isBleOn = true;

  lv_obj_add_state(ui_switchble, LV_STATE_CHECKED);

  BLE.setLocalName("ESP32S3_ceas"); 
  BLE.setAdvertisedService(Service);
  Service.addCharacteristic(sendCharacteristic); 
  Service.addCharacteristic(receivenameCharacteristic); 
  Service.addCharacteristic(receivecredentialsCharacteristic);
  
  receivenameCharacteristic.setEventHandler(BLEWritten,receivenameCharacteristicWritten);
  receivecredentialsCharacteristic.setEventHandler(BLEWritten,receivecredentialsCharacteristicWritten);

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  BLE.addService(Service); 
  
  BLE.advertise(); 

  recievedcred=false;
}

void endble(){
  isBleOn = false;
  delay(20);
  BLE.stopAdvertise();
  BLE.end();
  lv_obj_clear_state(ui_switchble, LV_STATE_CHECKED);
}

//------------------------------------------------//
//                  Functii Fisere                //
//------------------------------------------------//

int da_indexul_la_care_se_afla_ssid(String ssid){
  for (int kjl = 0 ; kjl < get_number_of_list_elements()-1; kjl++){
    if (ssid == lista_wifi[kjl]){
      return kjl;
    }
  }
  return -1;
}

void verifica_daca_exista_in_fisier(){
  bool este_in_fisier = false;
  int l=0;

  for(l;l<get_number_of_list_elements();l+=2){
    if(cred_name == lista_wifi[l]){
      este_in_fisier = true;
      // Serial.println("Este in fisier");
      break;
    }
    else{
      este_in_fisier = false;
      // Serial.println("Nu este in fisier");
    }
  }

  if(este_in_fisier == false){
    wififile = LittleFS.open("/credentiale.txt", FILE_APPEND);
      
    if (!wififile) {
      // Serial.println("Failed to open wififile for append");
    }
    wififile.printf("%s\n%s\n", cred_name.c_str(), cred_pass.c_str());
    wififile.close();
    // Serial.println("Am adaugat la fisier");
  }
  if(este_in_fisier == true){
    // Serial.println("Este deja in fisier");
  }
}

void read_wifi_list_elements(){
  wififile = LittleFS.open("/credentiale.txt", FILE_READ);
    
  if (!wififile) {
    // Serial.println("Failed to open wififile for reading");
  }

  int k=0;

  while(true){
    String linename = wififile.readStringUntil('\n');
    if (linename.length() == 0){
      wififile.close();
      break;
    }
    String linepass = wififile.readStringUntil('\n');
    if (linepass.length() == 0){
      wififile.close();
      break;
    }
    Serial.print("line: "); Serial.print(linename);
    Serial.print("line 1 : "); Serial.println(linepass);
    lista_wifi[k]=linename;
    lista_wifi[k+1]=linepass;
    k+=2;
  }
  wififile.close();
}

//------------------------------------------------//
//           Functie setup pulse sensor           //
//------------------------------------------------//

void setpulsesensor(){
  byte ledBrightness = 85; //Options: 0=Off to 255=50mA// orig 77 
  byte sampleAverage = 16; //Options: 1, 2, 4, 8, 16, 32 orig 8
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 1600; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200 orig 1000
  int pulseWidth = 118; //Options: 69, 118, 215, 411 orig 69 
  int adcRange = 8192; //Options: 2048, 4096, 8192, 16384 // orig 8192
  
  if (!particleSensor.begin(senzorii2c, I2C_SPEED_FAST)) {
    // Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //configurare senzor
  particleSensor.shutDown();
}

//------------------------------------------------//
//                     Diverse                    //
//------------------------------------------------//

int get_number_of_list_elements(){
  int number_of_el=0;
  int nm;
  for (nm=0; nm<200; nm++){
    if (lista_wifi[nm].length()>0){
      number_of_el++;
    }
    else{
      break;
    }
  }
  return number_of_el;
}


/**
 * Sunday = 0 ... Saturday = 6 https://stackoverflow.com/questions/64225464/is-there-an-arduino-library-that-can-take-in-a-dd-mm-yyyy-date-and-tell-me-what
 */

int ISO_day_of_week(int day, int month, int year)
{
    static const int offset[] = {6, 2, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3};

    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + offset[month - 1] + day) % 7 + 1;
}

unsigned long getTime() { //https://randomnerdtutorials.com/epoch-unix-time-esp32-arduino/
  time_t now1;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now1);
  return now1;
}


int32_t movingAverage(int32_t newSample) {
  
  sum -= window[windowIndex];
  
  sum += newSample;
  window[windowIndex] = newSample;
  
  windowIndex = (windowIndex + 1) % WINDOW_SIZE;
  
  return sum / WINDOW_SIZE;
}

void set_time(){
  unsigned long epoch = 0;
  epoch = getTime() + 10800;
  uUnixDate dateE = uUnixDate(epoch);
  uint16_t set_an = dateE.year();
  uint8_t set_luna = dateE.month();
  uint8_t set_zi = dateE.day();
  uint8_t set_ora = dateE.hour();
  uint8_t set_minute = dateE.minute();
  uint8_t set_secunde = dateE.second();
  ceas.set(set_secunde, set_minute, set_ora, set_zi, set_luna, set_an);
}
