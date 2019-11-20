 #include <WiFi.h>
 #include <WiFiClientSecure.h>
 #include "DHT.h"

 #define DHTPIN 2 // Conectar o pino de dados do DHT11 no pino 2 da placa ESP32

 // Definir o tipo de DHT. No caso, DHT11
// #define DHTTYPE DHT11 // DHT 11
 //#define DHTTYPE DHT22 // DHT 22 (AM2302)
 #define DHTTYPE DHT21 // DHT 21 (AM2301)

 // Inicializar o DHT11
 DHT dht(DHTPIN, DHTTYPE);


 WiFiClientSecure client;//Cria um cliente seguro (para ter acesso ao HTTPS)
 String textFix = "GET /forms/d/1EDkJKGgSyQhBRU5ub9ppHqcpZXxsDV0ibyC-chwwZiE/formResponse?ifq&entry.1137005404=";
 //Essa String sera uma auxiliar contendo o link utilizado pelo GET, para nao precisar ficar


 void setup()
 {
 Serial.begin(115200);//Inicia a comunicacao serial
 WiFi.mode(WIFI_STA);//Habilita o modo estacao
 WiFi.begin("BoomBox", "curucucu2019");//Conecta na rede
 Serial.println("DHT21 test!");
 dht.begin();
 delay(2000);//Espera um tempo para se conectar no WiFi


 }


 void loop()
 {
 if (client.connect("docs.google.com", 443) == 1)//Tenta se conectar ao servidor do Google docs na porta 443 (HTTPS)
 {
 //Faz a leitura da temperatura e da umidade do sensor
 float umid = dht.readHumidity();
 float temp = dht.readTemperature();

 if (isnan(umid) || isnan(temp)) {
 Serial.println("Failed to read from DHT sensor!");
 return;
 }
 String toSend = textFix;//Atribuimos a String auxiliar na nova String que sera enviada
 toSend += temp;//Adiciona−se o valor da temperatura
 toSend += "&submit=Submit HTTP/1.1";//Completamos o metodo GET para nosso formulario.

 client.println(toSend);//Enviamos o GET ao servidor−
 client.println("Host: docs.google.com");//−
 client.println();//−
client.stop();//Encerramos a conexao com o servidor
 Serial.println("Dados enviados.");//Mostra no monitor que foi enviado
 }
 else
 {
 Serial.println("Erro ao se conectar");//Se nao for possivel conectar no servidor, ira avisar no monitor.
 }

 delay(60000); // Aguarda 60 segundos para realizar nova medicao.
 }
