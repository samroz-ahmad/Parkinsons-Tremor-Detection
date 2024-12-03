// Group 7
// Members: Samroz Ahmad (ss14256), Luca Villegas (gv2114), Daniel Yang (ty2184)

#include <Adafruit_CircuitPlayground.h> 
#include "arduinoFFT.h" // Include the ArduinoFFT library for performing Fast Fourier Transform.
#include <Arduino.h> 

// Define constants for FFT setup.
const uint16_t samples = 128; // Number of samples in the FFT.
const double samplingFrequency = 50; // Sampling frequency in Hz.
double vReal[samples]; // Array to store real components of the input signal.
double vImag[samples]; // Array to store imaginary components (zero-initialized).
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency); // Instantiate FFT object.

// Tremor detection parameters.
const double minTremorFrequency = 3.0; // Minimum frequency to detect tremor, in Hz.
const double maxTremorFrequency = 6.0; // Maximum frequency for tremor detection, in Hz.
const unsigned long tremorDurationThreshold = 100; // Duration threshold for tremor in terms of samples collected.
unsigned long tremorStartTime = 0; // Timestamp when tremor starts.
int consecutiveTremorSamples = 0; // Counter for consecutive samples where tremor is detected.
bool tremorDetected = false; // Flag to indicate tremor detection.

// Function prototypes for accelerometer data collection and analysis.
void collectAccelerometerData();
double calculateTremorIntensity();
void displayTremorIntensity(double intensity);
bool isTremorInRange(double intensity);

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate.
  CircuitPlayground.begin(); // Initialize the Circuit Playground board.
  while (!Serial); // Wait for serial connection to establish.
  Serial.println("Ready to detect tremors using accelerometer"); // Print ready message.
}

void loop() {
  collectAccelerometerData(); // Collect data from the accelerometer.
  Serial.print(consecutiveTremorSamples); // Debug output of tremor sample count.
  if (consecutiveTremorSamples >= tremorDurationThreshold / 10) { // Check if enough samples have been collected.

    if (tremorDetected) {
      Serial.println("Tremor detected for the majority of the time!");
      CircuitPlayground.playTone(880, 1000); // Play a tone if tremor is detected.
    } else {
      Serial.println("No significant tremor detected.");
    }
    consecutiveTremorSamples = 0; // Reset tremor sample counter.
    tremorDetected = false; // Reset tremor detection flag.
  }
}

void collectAccelerometerData() {
  for (int i = 0; i < samples; i++) {
    // Read accelerometer data from X, Y, Z axes.
    double x = CircuitPlayground.motionX();
    double y = CircuitPlayground.motionY();
    double z = CircuitPlayground.motionZ();
   
    // Compute magnitude of the acceleration vector and store it in the real part.
    vReal[i] = sqrt(x * x + y * y + z * z);
    vImag[i] = 0; // Imaginary part remains zero as we are dealing with real numbers only.
   
    delay(10); // Delay to match the sampling frequency.
  }
 
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward); // Apply a Hamming window to the sampled data.
  FFT.compute(FFTDirection::Forward); // Perform the FFT on the windowed data.
  FFT.complexToMagnitude(); // Convert the complex FFT output to magnitude for analysis.
 
  double tremorIntensity = calculateTremorIntensity(); // Calculate tremor intensity based on FFT results.
  displayTremorIntensity(tremorIntensity); // Display or process the tremor intensity.
  if (isTremorInRange(tremorIntensity)) { // Check if the detected tremor is within the desired range.
    if (consecutiveTremorSamples == 0) {
      tremorStartTime = millis(); // Record the start time of the tremor if this is the first detection.
    }
    consecutiveTremorSamples++; // Increment the tremor sample counter.
    tremorDetected = true; // Set the tremor detection flag.
  }
}

double calculateTremorIntensity() {
  double intensity = 0.0;
  uint16_t minIndex = floor(minTremorFrequency * samples / samplingFrequency); // Calculate the minimum index in the FFT result array.
  uint16_t maxIndex = ceil(maxTremorFrequency * samples / samplingFrequency); // Calculate the maximum index in the FFT result array.
 
  // Sum magnitudes within the target frequency range.
  for (uint16_t i = minIndex; i <= maxIndex; i++) {
    intensity += vReal[i];
  }
 
  return intensity; // Return the calculated intensity.
}

void displayTremorIntensity(double intensity) {
  static unsigned long lastColorUpdateTime = 0; // Timestamp for the last color update.
  const unsigned long colorUpdateInterval = 10000; // Interval for updating the color (10 seconds).
  double intensityAtMaxFreq = 1000;
  // Map the intensity to a color scale from green to red.
  int targetColor = map(intensity, 0, intensityAtMaxFreq, 0, 255);

  // Update the color display if the update interval has passed.
  if (millis() - lastColorUpdateTime >= colorUpdateInterval) {
    lastColorUpdateTime = millis();

    // Update LED colors based on the tremor intensity.
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, targetColor, 255 - targetColor, 0);
    }
  }

  // Output tremor intensity to the serial monitor.
  Serial.print("Tremor Intensity: ");
  Serial.println(intensity);
}

bool isTremorInRange(double intensity) {
  double intensityAtMinFreq = 200;
  double intensityAtMaxFreq = 10000;
  // Check if intensity is within the specified range and adjust sample counter accordingly.
  if(intensity >= intensityAtMinFreq && intensity <= intensityAtMaxFreq){
    return true; // Return true if the tremor intensity is within the range.
  }
  else{
    consecutiveTremorSamples = 0; // Reset counter if out of range.
    return false; // Return false if out of range.
  }
}
