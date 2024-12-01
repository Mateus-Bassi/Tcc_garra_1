#include <ESP32Servo.h> // Biblioteca dos Servos

//------- definindo pontos -------
const int led_Coluna1 = 15; // led D15 - Coluna
const int led_Coluna2 = 4; // led D4 - Coluna

const int led_linha1 = 13; // led D13 - Linha
const int led_linha2 = 14; // led D14 - Linha

const int btn_coluna = 19; //botao coluna D19
const int btn_linha = 21; //botao coluna D21

const int btn_movi = 35;

int coluna =1; //controle colunas
int linha =1; //controle linhas
int maxlimit = 2;
int status = 0; // Controle de 'Carga'

//------ iniciando servos --------
Servo servoBase;
Servo servo1;
Servo servo2;
Servo servoGarra;


void setup() {
  pinMode(led_Coluna1, OUTPUT);
  pinMode(led_Coluna2, OUTPUT);
  pinMode(led_linha1, OUTPUT);
  pinMode(led_linha2, OUTPUT);
  pinMode(btn_coluna,INPUT);
  pinMode(btn_linha,INPUT);
  pinMode(btn_movi,INPUT);
  servoBase.attach(32);  
  servo1.attach(33); 
  servo2.attach(25); 
  servoGarra.attach(26); 

  //apenas quando inicia
  servoGarra.write(0);
  
  //inicio garra para posicao padrao
  garraP();

  //iniciando os led's padrao
  digitalWrite(led_Coluna1, HIGH); // Liga os LED
  digitalWrite(led_linha1, HIGH); 
}


void loop() {
  if(digitalRead(btn_coluna) == HIGH){
    coluna = btn_press(coluna,maxlimit);
    if(coluna == 1){
      digitalWrite(led_Coluna1, HIGH);
      digitalWrite(led_Coluna2, LOW);
    }else{
      digitalWrite(led_Coluna1, LOW);
      digitalWrite(led_Coluna2, HIGH);
    }
  }
  if(digitalRead(btn_linha) == HIGH){
    linha = btn_press(linha,maxlimit);
    if(linha == 1){
      digitalWrite(led_linha1, HIGH);
      digitalWrite(led_linha2, LOW);
    }else{
      digitalWrite(led_linha1, LOW);
      digitalWrite(led_linha2, HIGH);
    }
  }
  if (digitalRead(btn_movi) ==HIGH){
	  status=movi_garra(coluna,linha,status);
  }
}

// Funcao de inverter o valor do botao 
int btn_press(int x, int maxlimit){ 
  if(x<maxlimit){
    x += 1;
    delay(250);
  }else{
    x=1;
    delay(250);
  }
return x;
}

//Movimento da Garra recebendo paramentros
int movi_garra(int coluna,int linha, int status){ //(coluna,linha,status) adicionar depois
  delay(250);
  switch (coluna) { // aqui vamos abrir a garra
    case 1:
      for(int i =90;i>=60;i--){ 
      servoBase.write(i);
      delay(15);
      }
      if (status == 0){ //Abre 
        for(int i =180;i>=60;i--){ 
        servoGarra.write(i);
        delay(15);
        }
      }else{//Abre no final
        //Nao faz nada pois esta com um objeto ja 
      }
      break;

    case 2:
      for(int i =90;i<=120;i++){ //Abre 
      servoBase.write(i);
      delay(15);
      }
      if (status == 0){ //Abre 
        for(int i =180;i>=60;i--){ 
        servoGarra.write(i);
        delay(15);
        }
      }else{//Abre no final
        //Nao faz nada pois esta com um objeto ja 
      }
      break;
  }

  switch (linha) { //No final devemos fechar a garra
    case 1:
      for(int i =90;i<=180;i++){ //altura
      servo1.write(i);
      delay(15);
      }
      for(int i =70;i<=180;i++){ //avanco
      servo2.write(i);
      delay(15);
      }
      if (status == 0){ //Fechar 
        for(int i =60;i<=180;i++){ 
        servoGarra.write(i);
        delay(15);
        status =1;
        }
      }else{//Abre se estiver com um objeto
        for(int i =180;i>=60;i--){ 
        servoGarra.write(i);
        delay(15);
        status = 0;
        }
      }
      break; //saindo
      
    case 2:
      for(int i =90;i>=0;i--){ //altura 
      servo1.write(i);
      delay(15);
      }
      for(int i =90;i<=120;i++){ //Avanco 
      servo2.write(i);
      delay(15);
      }
      if (status == 0){ //Fechar 
        for(int i =180;i>0;i++){ 
        servoGarra.write(i);
        delay(15);
        status =1;
        }
      }else{//Abre se estiver com um objeto
        for(int i =0;i<=180;i++){ 
        servoGarra.write(i);
        delay(15);
        status = 0;
        }
      }
      break;//Saindo
  }
  
  garraP();
  return status;
}

//Volta a Garra na posição inicial
void garraP(){ 
  servo2.write(70); 
  servo1.write(90);  
  servoBase.write(90);  
}
