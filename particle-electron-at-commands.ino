//uncomment the section below and enter the correct APN credentials if you are using a third-party SIM card
/*
String apn = "";
String username = "";
String password = "";

STARTUP(cellular_credentials_set(apn, username, password, NULL));
*/

const int AT_TIMEOUT = 5*60*1000;

void setup() {
	Serial.begin(9600);
	Serial.println("Starting cellular, waiting 10s.");
	Cellular.on();
	delay(10000);
	Serial.println("Cellular started. Ready to receive AT commands.");
}

void loop() {

	if (Serial.available() > 0) {
			
		String input = Serial.readString();
		
		Serial.println("Received input: "+input);
		
		Serial.println("--BEGIN RESPONSE--");
		
		int point;
		
		Cellular.command(parseResponse, &point, AT_TIMEOUT, input+"\r\n");
		
		Serial.println("--END RESPONSE--");	
	}
}

int parseResponse(int type, const char* buf, int len, int* point)
{

	char line[1024+64];
	strncpy(line, buf, len);
	line[len] = '\0';
	String line_as_string = String(line);
	Serial.println(line_as_string.trim());
	
	if (type == TYPE_ABORTED) {
		return RESP_ABORTED;
	}
	else if (type == TYPE_PROMPT) {
		return RESP_PROMPT;
	}
	else if (type == TYPE_ERROR) {
		return RESP_ERROR;
	}
	else if (type == TYPE_OK) {
		return RESP_OK;
	}
	else {
		return WAIT;
	}
}