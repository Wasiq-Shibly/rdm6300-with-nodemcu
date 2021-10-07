#include <SoftwareSerial.h>
SoftwareSerial RFID(D3, D4); // RX and TX
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

String Teks;
String NoKartu  ;  //No kartu RFID

void setup()
{
  Serial.begin(9600);
  RFID.begin(9600);
  lcd.begin();

  pinMode (D5, OUTPUT);
  digitalWrite (D5, 0);

  Serial.println("Dekatkan kartu RFID anda …");
  lcd.print("Tap Kartunya !!");
  lcd.setCursor(0, 1);
  lcd.print("Harga : 2000");

  NoKartu = "5500A7ADB6"; // Masukkan nomor kartu untuk akses (dalam hexa)
}
boolean state = false;
char c;

void loop()
{
  while (RFID.available() > 0) {

    delay(5);
    c = RFID.read();
    Teks += c;
  }
  if (Teks.length() > 20) Cek();
  Teks = "";
}

void Cek()
{

  Teks = Teks.substring(1, 11);
  Serial.println("ID Kartu anda : " + Teks);
  Serial.println("ID Akses : " + NoKartu);

  if (NoKartu.indexOf(Teks) >= 0) {
    Serial.println("Akses diterima, pintu terbuka otomatis …");
    lcd.clear();
    lcd.print("Berhasil....");
    lcd.setCursor(0, 1);
    lcd.print ("Sisa Saldo:10000");
  }
  else {
    Serial.println("Akses ditolak…");
    lcd.clear();
    lcd.print("Tidak Terdaftar");
    lcd.setCursor(0, 1);
    lcd.print("Silahkan Daftar !!!");
  }
  delay(2000);

  Serial.println(" ");

  Serial.println("Dekatkan kartu RFID anda …");
  lcd.clear();
  lcd.print("Tap Kartunya !!");
  lcd.setCursor(0, 1);
  lcd.print("Harga : 2000");

}
