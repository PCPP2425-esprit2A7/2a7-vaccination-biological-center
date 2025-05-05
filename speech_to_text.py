import speech_recognition as sr
import sys
import time

def recognize_speech():
    try:
        recognizer = sr.Recognizer()
        microphone = sr.Microphone()
        
        print("Ready to listen...", flush=True)
        
        with microphone as source:
            print("Adjusting for ambient noise...", flush=True)
            recognizer.adjust_for_ambient_noise(source)
            
            print("Listening...", flush=True)
            try:
                # Wait a bit for the user to start speaking
                audio = recognizer.listen(source, timeout=15, phrase_time_limit=60)
                
                print("Processing...", flush=True)
                text = recognizer.recognize_google(audio)
                print(f"{text}", flush=True)
                return 0
            except sr.WaitTimeoutError:
                print("No speech detected. Please try again.", flush=True)
                return 1
            except sr.UnknownValueError:
                print("Sorry, I could not understand the audio.", flush=True)
                return 1
            except sr.RequestError as e:
                print(f"Could not request results; {e}", flush=True)
                return 1
    except Exception as e:
        print(f"Error: {str(e)}", flush=True)
        return 1

if __name__ == "__main__":
    try:
        sys.exit(recognize_speech())
    except Exception as e:
        print(f"Fatal error: {str(e)}", flush=True)
        sys.exit(1)
