#define echo 3        // echo
#define declencheur 8 //trig
//ajout ok

// Contrôle PWM simple
int E1 = 5; //moteur gauche
int E2 = 6; //moteur droit
int M1 = 4; 
int M2 = 7;

int distanceMaximum = 500;
int distanceMinimum = 2;
long distance; 
long temps; 

void setup() 
{
  int i; 
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);
  
  pinMode(declencheur, OUTPUT);
  pinMode(echo, INPUT);


  Serial.begin(19200); //vitesse d'exécution où l'on perd moins la communication
  Serial.println("Exécution du contrôle par clavier"); //verifier que le programme soit lancé
  

}

void stop(void)
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW); 
}

void back(char a,char b) 
{
  Serial.println("Avance !!");
  analogWrite (E1,a); 
  digitalWrite(M1,HIGH); 
  analogWrite (E2,b); 
  digitalWrite(M2,HIGH);
}

// ajout au code de base-----------


void advance(char a,char b) 
{
  analogWrite (E1,a); 
  digitalWrite(M1,LOW); 
  analogWrite (E2,b); 
  digitalWrite(M2,LOW);
}

void left(char a,char b) //pb avance
{
  analogWrite (E1,a); 
  digitalWrite(M1,LOW); 
  analogWrite (E2,b); 
  digitalWrite(M2,HIGH);
}

void right(char a,char b) 
{
  analogWrite (E1,a); 
  digitalWrite(M1,HIGH); 
  analogWrite (E2,b); 
  digitalWrite(M2,LOW);
}
// validation des 4 méthodes le 12/07-----

long ralentirDevantUnObstacle(char a, char b)
{
  digitalWrite(declencheur, HIGH);
  delayMicroseconds(10); 
  digitalWrite(declencheur, LOW);

 temps = pulseIn(echo, HIGH);
 Serial.println("temps: ");
 Serial.println(temps);

 //distance = 288;
  
 distance = temps/58.2;
 Serial.println("distance: ");
 Serial.println(distance);

 if (distance >= distanceMaximum || distance <= distanceMinimum)
 {
      Serial.println("Distance en dehors de la plage de mesure");
      Serial.println("-----------------------------------");

      return -1;
 }  
  
 else
 {
      Serial.print("La distance est de :");
      Serial.print(distance);
      Serial.println("cm");
      Serial.println("-----------------------------------");

      if (distance >= 200)
      {
        Serial.println("200 cm avant impact"); advance(250,235); 
      }
      else if (distance >= 150)
        {
        Serial.println("150 cm avant impact");  advance(200,185);
        }
        else if (distance >= 100)
          {
          Serial.println("100 cm avant impact");  advance(175,150);
          }
          else if (distance >= 10)
            {
            Serial.println("10 cm avant impact");  advance(150,135);
            }
            else
              {
              Serial.println("impact imminent "); stop(); 
              }
              return distance;
  }
}

void loop() 
{
  //advance(150,150);

  ralentirDevantUnObstacle(250,250);

  delay(10);
}