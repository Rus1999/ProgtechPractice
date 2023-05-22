void setup() {
    pinMode(R0_1, OUTPUT); 
}   
void loop() { 
    digitalWrite(R0_1,HIGH); // Opens the relay switch
    delay(500);             // Wait 500ms
    digitalWrite(R0_1,LOW);  // Closes the relay switch
    delay(500);
}
