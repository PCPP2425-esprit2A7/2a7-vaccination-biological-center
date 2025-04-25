import whisper
import pyttsx3
import re
import json
import dateparser
import sounddevice as sd
import scipy.io.wavfile as wav
from datetime import datetime

MODEL_NAME = "base"
LANGUAGE = "fr"
DURATION = 6  # seconds
SAMPLE_RATE = 16000
AUDIO_FILE = "input.wav"

def speak(text):
    engine = pyttsx3.init()
    engine.setProperty("rate", 140)
    engine.setProperty("volume", 1.0)
    engine.say(text)
    engine.runAndWait()

def record_audio(filename, duration=DURATION, fs=SAMPLE_RATE):
    print("🎙️ Recording... Speak now.")
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype='int16')
    sd.wait()
    wav.write(filename, fs, audio)
    print("✅ Recording complete.")

def extract_date(text):
    date = dateparser.parse(text, languages=["fr"])
    if date:
        return date.strftime("%Y-%m-%d")
    return ""

def extract_hour(text):
    match = re.search(r"(\d{1,2}) ?(?:heures|h)", text)
    if match:
        hour = int(match.group(1))
        if 0 <= hour <= 23:
            return hour
    return None

def extract_patient_id(text):
    match = re.search(r"patient(?: ID)?(?: numéro)? (\d+)", text, re.IGNORECASE)
    if match:
        return int(match.group(1))
    return 0

def extract_employe_id(text):
    match = re.search(r"(employé|docteur|personnel) (\d+)", text, re.IGNORECASE)
    if match:
        return int(match.group(2))
    return 0

def extract_status(text):
    if "programmé" in text.lower():
        return "Programmé"
    elif "confirmé" in text.lower():
        return "Confirmé"
    elif "annulé" in text.lower():
        return "Annulé"
    return "Non spécifié"

def process_voice():
    record_audio(AUDIO_FILE)
    model = whisper.load_model(MODEL_NAME)
    result = model.transcribe(AUDIO_FILE, language=LANGUAGE)
    text = result["text"].strip()

    date = extract_date(text)
    hour = extract_hour(text)
    patient_id = extract_patient_id(text)
    employe_id = extract_employe_id(text)
    status = extract_status(text)

    summary = f"Vous avez demandé un rendez-vous le {date} à {hour} heures avec le patient {patient_id}. Souhaitez-vous confirmer ce rendez-vous ?"
    speak(summary)

    confirmation = True  # always yes for now

    response = {
        "ok": True,
        "texte": text,
        "date": date,
        "heure": hour,
        "id_patient": patient_id,
        "id_employe": employe_id,
        "status": status,
        "confirmation": confirmation
    }

    print(json.dumps(response, ensure_ascii=False, indent=4))

if __name__ == "__main__":
    process_voice()
