/***************************************************
 *Obter dados do sensor DHT
 **************************************************/
void getDhtData(void)
{
  float tempIni = airTemp;
  float humIni = airHum;
  airTemp = dht.readTemperature();
  airHum = dht.readHumidity();
  if (isnan(airHum) || isnan(airTemp))   // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    airTemp = tempIni;
    airHum = humIni;
    return;
  }
}

/***************************************************
 * Obtem os dados do sensor de umidade do solo.
 **************************************************/
void getSoilMoisterData(void)
{
  soilMoister = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;                                                                            // leia o sensor 3 vezes.
  for(int i = 0; i < N; i++)                                                            // leia o sensor "N" vezes e obtenha a média.
  {
    soilMoister += analogRead(soilMoisterPin);   
    delay(150);
  }
  digitalWrite (soilMoisterVcc, LOW);
  soilMoister = soilMoister/N; 
  soilMoister = map(soilMoister, 1300, 0, 0, 100);                                      //Ajuste do sensor de umidade do solo, configurar o intervalo em porcentagem.
}                                                                                       //(umidade, 1023, 0, 0, 100) valor 1023 correspondente a entrada analogica e 100 valor em porcentagem correspondente.

/***************************************************
 * Obtem os dados do sensor SoilTemp
 **************************************************/
void getSoilTempData()
{
   ds.requestTemperatures(); 
   soilTemp = ds.getTempCByIndex(0);

  int newData = ((soilTemp + 0.05) * 10);                                              //Corrige o valor do soilTemp para uma casa decimal.
  soilTemp = (newData / 10.0);
}
