#include <ArduinoJson.h>
#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "skac7z59prpsw";
const char* host1 = "maker.ifttt.com"; //IFTTT server網址
const char* event1 = "Angry";  //IFTTT事件名稱
const char* event2 = "diet";  //IFTTT事件名稱
const char* apiKey = "cD6vkUnQ9LReE0JjnmvawE";  //IFTTT Applet key

String value1;
double value2;
double value3;
int i;

void open(){
  Serial.println("111" );
   Serial.println(digitalRead(32));
      digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(200);                       // wait for a second
       digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
       delay(200);                       // wait for a second
       digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(200);                       // wait for a second
       digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
       delay(200);                       // wait for a second
      Sendtoline1(String(value1),String(value2),String (value3));  //Client傳送資料
      Serial.print("***");
      Serial.println("***");
      Serial.println("--------------------"); 
      delay(3000); // the OWM free plan API does NOT allow more then 60 calls per minute
      i=0;
}
void close(){
  
  for( i=0;i<7;i++){
    if(digitalRead(32)==LOW)open();
       Serial.println(i);
      // WiFi.reconnect();
       digitalWrite(14, LOW);
       delay(5000);
       }
  if(i%7==0){
    Sendtoline2(String(value1),String(value2),String (value3));  //Client傳送資料
  
    Serial.print("***");
    Serial.println("***");
    Serial.println("--------------------"); 
    
    delay(5000); // the OWM free plan API does NOT allow more then 60 calls per minute
   }
 }

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  pinMode(14, OUTPUT);
  pinMode(32, INPUT);
}

void loop() {
     if(digitalRead(32)==LOW){
       open();
   }
   else if(digitalRead(32)==HIGH){
      close();
    }
   
}

void Sendtoline1(String value1, String value2,String value3) {
  WiFiClient client;  //建立Client物件
  const int httpPort = 80;  //預設通訊阜80
//  String url="maker.ifttt.com/trigger/{event}/with/key/cD6vkUnQ9LReE0JjnmvawE";
  String JsonString = "";  //此範例不會用到

  //Client連結Server
  if (client.connect(host1, httpPort)) {

//    Webhook API
    String url = "/trigger/Weather/with/key/cD6vkUnQ9LReE0JjnmvawE";
//    Query String
     url += "?value1=" + value1 + "&value2=" + value2+ "&value3=" + value3;
    Serial.println(url);
    //Client傳送
    client.println(String("POST ") + url + " HTTP/1.1");
    client.println(String("Host: ") + host1);
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(JsonString.length());
    client.println();
    client.println(JsonString);

    //等待5秒，每0.1秒偵測一次是否有接收到response資料
    int timeout = 0;
    while (!client.available() && (timeout++ <= 50)) {
      delay(100);
    }

    //如果無回應
    if (!client.available()) {
      Serial.println("No response...");
    }
    //用while迴圈一字一字讀取Response
    while (client.available()) {
      Serial.write(client.read());
    }

    //停止Client
    client.stop();
  }
}


void Sendtoline2(String value1, String value2,String value3) {
  WiFiClient client;  //建立Client物件
  const int httpPort = 80;  //預設通訊阜80
//  String url="maker.ifttt.com/trigger/{event}/with/key/cD6vkUnQ9LReE0JjnmvawE";
  String JsonString = "";  //此範例不會用到

  //Client連結Server
  if (client.connect(host1, httpPort)) {

//    Webhook API
    String url = "/trigger/diet/with/key/cD6vkUnQ9LReE0JjnmvawE";
//    Query String
     url += "?value1=" + value1 + "&value2=" + value2+ "&value3=" + value3;
    Serial.println(url);
    //Client傳送
    client.println(String("POST ") + url + " HTTP/1.1");
    client.println(String("Host: ") + host1);
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(JsonString.length());
    client.println();
    client.println(JsonString);

    //等待5秒，每0.1秒偵測一次是否有接收到response資料
    int timeout = 0;
    while (!client.available() && (timeout++ <= 50)) {
      delay(100);
    }

    //如果無回應
    if (!client.available()) {
      Serial.println("No response...");
    }
    //用while迴圈一字一字讀取Response
    while (client.available()) {
      Serial.write(client.read());
    }

    //停止Client
    client.stop();
  }
}
