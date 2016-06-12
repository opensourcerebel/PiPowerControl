
String str;
String strlast;
int started;

int pushButton = 3;
int led = 9;
int rpiPowerControl = 7;
int manualStartedButton = 8;
boolean stringComplete = false;
void setup() {
  Serial.begin(57600);
  pinMode(manualStartedButton, INPUT);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(rpiPowerControl, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(rpiPowerControl, HIGH);
  started = 0;
  str.reserve(200);
  strlast.reserve(200);
}

void loop()
{
  if (Serial.available() > 0)
  {
    strlast = str;
    str = Serial.readStringUntil('\n');

    if (started)
    {
      if (str.endsWith(" reboot: Power down\r"))
      {
        digitalWrite(led, LOW);
        digitalWrite(rpiPowerControl, HIGH);
        started = 0;
      }
    }
    else
    {
      if (str == "raspberrypi login: ")
      {
        digitalWrite(led, HIGH);
        started = 1;
      }
    }
  }

  int buttonState = digitalRead(pushButton);
  if (buttonState == 0)
  {
    if (started == 1)
    {
      //      Serial.println("1[" + strlast + "]");
      //      Serial.println("2[" + str + "]");
      //      delay(1000);
      Serial.print("pi\n");
      delay(1000);
      Serial.print("raspberry\n");
      delay(1000);
      Serial.print("sudo shutdown -h now\n");
      //when started
      //<raspberrypi login: >
      //when stopped
      //<[  390.039293] reboot: Power down>
    }
    else
    {
      digitalWrite(rpiPowerControl, LOW);
      delay(1000);
    }
  }

}
