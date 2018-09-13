#include "setup_serializer.h"
#include <EEPROM.h>

SetupSeializer* serializer;
bool readSetup = false;


void setup()
{
	Serial.begin(9600);
	serializer = new SetupSeializer();
}

void loop()
{
	if (Serial.available() > 0)
	{
		Serial.println("Writing in stream to EEPROM");
		String fromSerial = Serial.readString();

		serializer->WriteString(fromSerial);

		readSetup = true;
		Serial.println("Done");
		delay(1000);
	}


	if (readSetup)
	{
		Serial.println("Reading setup from EEPROM");
		serializer->Open();

		Serial.println(serializer->GetInMemSetup());

		int midiChannel;
		if (serializer->ValueOfField("MidiCh", &midiChannel))
		{
			Serial.print("Midi Channel: ");
			Serial.println(midiChannel);
		}

		String Owner;
		if (serializer->ValueOfField("Owner", &Owner))
		{
			Serial.print("Owner: ");
			Serial.println(Owner);
		}

		serializer->Close();
		readSetup = false;
	}




}
