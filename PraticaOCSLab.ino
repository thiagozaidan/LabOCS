 #include <WiFi.h>
 #include <WiFiClientSecure.h>

 WiFiClientSecure cl;//Cria um cliente seguro (para ter acesso ao HTTPS)
 String textFix = "GET /v4/spreadsheets/1I0szAoaguoeRl7jTEoQBCJuqvECI4tPte-DMl2pQFjY/values/";
 String key = "?key=AIzaSyCV5HW0Gr4I7hv2Wz4e4ahoYUu_22s1rpc";//Chave de API
 //Essas Strings serao auxiliares, para nao precisar ficar re−escrevendo toda hora


 void setup()
 {
 Serial.begin(115200);//Inicia a comunicacao serial
 WiFi.mode(WIFI_STA);//Habilita o modo esta[U+FFFD]ao
 WiFi.begin("BoomBox", "curucucu2019");//Conecta na sua rede
 delay(3000);//Espera um tempo para se conectar no WiFi
 while (WiFi.status() != WL_CONNECTED)
 {
  Serial.print(".");
 delay(500);
 }

 //Se chegou aqui est[U+FFFD] conectado
 Serial.println();
 Serial.println("Connected");

 }

 void loop()
 {
 if (cl.connect("sheets.googleapis.com", 443) == true)//Tenta se conectar ao servidor do Google APIs na porta 443 (HTTPS)
 {
 String toSend = textFix; //Atribuimos a String auxiliar na nova String que sera enviada

 toSend += "C2:C5";//Os valores que queremos ler da planilha. Para uma [U+FFFD]nica c[U+FFFD]lula, use algo como "A2"; para ler varios, use algo  como "A1:C4".
 toSend += key;//Adicionamos a chave na String
 toSend += " HTTP/1.1";//Completamos o metodo GET para nosso formulario.

 cl.println(toSend);//Enviamos o GET ao servidor−
 cl.println("Host: sheets.googleapis.com");//−
 cl.println();//−


 Serial.println("Dado recebido:\n");
 //Serial.print(cl.readString()); //Mostra no Serial Monitor todo o pacote recebido.
 String dados_rec = cl.readString(); // A partir daqui pegaremos apenas os valores contidos nas celulas.
 String string_local = "values"; // Define a string a ser localizada no pacote para realizar a contagem a partir dela.
 int indice_valor = dados_rec.indexOf(string_local); // Procura o indice do pacote em que esta localizada a string.
 dados_rec.replace("'",""); // Retira−se os caracteres indesejados dos valores
dados_rec.replace("[","");
 dados_rec.replace("]","");
 dados_rec.replace(",","");
 dados_rec.replace("}","");
 dados_rec.replace("{","");
 dados_rec.replace("\n"," ");
 dados_rec.replace("''"," ");

 Serial.print(dados_rec.substring(indice_valor+8)); // Mostra no Serial apenas os valores apos "values".

 cl.stop();//Encerramos a conexao com o servidor.
 }
 else
 {
 Serial.println("Erro ao se conectar");
 }
 delay(10000); // Aguarda 60 segundos para ler novamente.

 }
